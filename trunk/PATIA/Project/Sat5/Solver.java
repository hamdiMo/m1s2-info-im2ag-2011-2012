import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class Solver {

    /** Attributs */
    private Clause[] m_clauses;
    private Variable[] m_variables;
    private int m_instances, m_conflicts, m_backtrack, m_height, m_heightMax, m_iteration;
   
    /** Constructeurs */
    public Solver() {
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

        return solve(variablesFree, clausesUnsolved);
    }
    

    public boolean solve(int variablesFreeCall, int clausesUnsolvedCall) {
        if (clausesUnsolvedCall == 0) return true;

        int variablesFree = variablesFreeCall, clausesUnsolved = clausesUnsolvedCall;
        int index = bestVariableIndex(variablesFree); 
        if (index == -1) return false;

        Variable variable = m_variables[index];

        variablesFree--;
        m_variables[index] = m_variables[variablesFree];
        m_variables[variablesFree] = variable;

        // System.out.println("Choix variable = " + variable);
        
        boolean valuePos = variable.getHeuristicPos() > variable.getHeuristicNeg();
        variable.propagate(valuePos);

        index = 0;
        while (index < clausesUnsolved) {
            if (m_clauses[index].isSat()) {
                clausesUnsolved--;
                Clause clause = m_clauses[index];
                m_clauses[index] = m_clauses[clausesUnsolved];
                m_clauses[clausesUnsolved] = clause;
            }
            else index++;
        }

        if (solve(variablesFree, clausesUnsolved)) return true;
        
        while (clausesUnsolved < clausesUnsolvedCall) {
            m_clauses[clausesUnsolved].restoreUntil(variable);
            clausesUnsolved++;
        }
        
        variable.propagate(!valuePos);

        index = 0;
        while (index < clausesUnsolved) {
            if (m_clauses[index].isSat()) {
                clausesUnsolved--;
                Clause clause = m_clauses[index];
                m_clauses[index] = m_clauses[clausesUnsolved];
                m_clauses[clausesUnsolved] = clause;
            }
            else index++;
        }

        return solve(variablesFree, clausesUnsolved);
    }
    
    public int bestVariableIndex(int variablesFree) {
        int index = -1, heuristicMax = 0, heuristicMin = 0;
        for (int i = 0; i < variablesFree; i++) {
            int heuristicPos = m_variables[i].getHeuristicPos();
            int heuristicNeg = m_variables[i].getHeuristicNeg();
            if (heuristicPos > heuristicMax || heuristicPos == heuristicMax && heuristicNeg > heuristicMin) {
                index = i;
                heuristicMax = heuristicPos;
                heuristicMin = heuristicNeg;
            }
            else if (heuristicNeg > heuristicMax || heuristicNeg == heuristicMax && heuristicPos > heuristicMin) {
                index = i;
                heuristicMax = heuristicNeg;
                heuristicMin = heuristicPos;
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
