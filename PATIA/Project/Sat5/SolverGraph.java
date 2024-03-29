import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class SolverGraph {

    /** Attributs */
    private Clause[] m_clauses;
    private Variable[] m_variables;
    private int m_instances, m_conflicts, m_backtrack, m_height, m_heightMax, m_iteration, m_node;
   
    /** Constructeurs */
    public SolverGraph() {
        m_height = 0;
        m_instances = 0;
        m_conflicts = 0;
        m_backtrack = 0;
        m_heightMax = 0;
    }
    

    /** Accesseurs */
    public int getInstances() { return m_instances; }
    public int getConflicts() { return m_conflicts; }
    public int getBacktrack() { return m_backtrack; }
    public int getHeigthMax() { return m_heightMax; }
    public int getIteration() { return m_iteration; }
    

    /** Methodes */
    public boolean solve(Problem problem) {
        int variablesFree = problem.getVariableDimension();
        m_variables = new Variable[variablesFree];
        for (int i = 0; i < variablesFree; i++) m_variables[i] = problem.getVariable(i);

        int clausesUnsolved = problem.getClauseDimension();
        m_clauses = new Clause[clausesUnsolved];
        for (int i = 0; i < clausesUnsolved; i++) m_clauses[i] = problem.getClause(i);


        System.out.println("digraph MTuring {" + "\n"
                           + "\t" + "rankdir=LR;" + "\n"
                           + "\t" + "edge [len = 1.5];" + "\n"
                           + "\t" + "node [shape = box]; start;" + "\n"
                           + "\t" + "node [shape = circle];" + "\n"
                           + "\t" + "start -> 0");

        m_node = 0;
        boolean res = solve(variablesFree, clausesUnsolved);
        System.out.println("}");
        return res;
    }
    
    public boolean solve(int variablesFreeCall, int clausesUnsolvedCall) {
        m_height++;
        if (m_height > m_heightMax) m_heightMax = m_height;
        int node = m_node;

        if (clausesUnsolvedCall == 0) return true;

        int variablesFree = variablesFreeCall, clausesUnsolved = clausesUnsolvedCall;
        int index = bestVariableIndex(variablesFree); 
        if (index == -1) {
            m_conflicts++;
            m_height--;
            return false;
        }

        Variable variable = m_variables[index];
        boolean valueIni = variable.getValue();
        
        variablesFree--;
        m_variables[index] = m_variables[variablesFree];
        m_variables[variablesFree] = variable;
        
        boolean unsat = true;
        do {
            index = 0;
            unsat = false;

            m_node++;
            System.out.print("\t" + node + " -> " + m_node + " [label = \"");
            if (!variable.getValue()) System.out.print("-");
            System.out.println("" + variable.getId() + "\"];");

            variable.propagate();
            m_instances++;

            while (!unsat && index < clausesUnsolved) {
                if (m_clauses[index].isSat()) {
                    clausesUnsolved--;
                    Clause clause = m_clauses[index];
                    m_clauses[index] = m_clauses[clausesUnsolved];
                    m_clauses[clausesUnsolved] = clause;
                }
                else {
                    if (m_clauses[index].isUnsat()) {
                        unsat = true; 
                        m_conflicts++;
                    }
                    index++;
                }
            }
            if (!unsat) unsat = !solve(variablesFree, clausesUnsolved);
            if (unsat) {
                clausesUnsolved = clausesUnsolvedCall;
                variable.unpropagate();
                variable.setValue(!variable.getValue());
                m_backtrack++;
            }
        } while (unsat && !variable.isHeuristicSafe(valueIni) && variable.getValue() != valueIni);

        m_height--;
        return !unsat;
    }
    
    public int bestVariableIndex(int variablesFree) {
        int index = -1, heuristicMax = 0, heuristicMin = 0;
        for (int i = 0; i < variablesFree; i++) {
            int heuristicPos = m_variables[i].getHeuristicPos();
            int heuristicNeg = m_variables[i].getHeuristicNeg();
            if (m_variables[i].isHeuristicPosSafe()) heuristicPos += variablesFree;
            if (m_variables[i].isHeuristicNegSafe()) heuristicNeg += variablesFree;
            if (heuristicPos > heuristicMax || heuristicPos == heuristicMax && heuristicNeg > heuristicMin) {
                index = i;
                heuristicMax = heuristicPos;
                heuristicMin = heuristicNeg;
                m_variables[i].setValue(true);
            }
            else if (heuristicNeg > heuristicMax || heuristicNeg == heuristicMax && heuristicPos > heuristicMin) {
                index = i;
                heuristicMax = heuristicNeg;
                heuristicMin = heuristicPos;
                m_variables[i].setValue(false);
            }
        }
        return index;
    }
    

    /** Affichage */
    public String toString() {
        return new String("Statistics = {" + "\n"
                          + "\t" + "Instances = " + getInstances() + "\n"
                          + "\t" + "Conflicts = " + getConflicts() + "\n"
                          + "\t" + "Backtrack = " + getBacktrack() + "\n"
                          + "\t" + "Heightmax = " + getHeigthMax() + "\n"
                          + "\t" + "Iteration = " + getIteration() + "\n"
                          + "}");
    }

}
