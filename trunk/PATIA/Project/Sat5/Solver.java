import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class Solver {

    /** Attributs */
    private Clause[] m_clauses;
    private Variable[] m_variables;
    private LinkedList<Clause> m_learnt;
    private int m_unsolvedClauses, m_freeVariables;
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
        m_freeVariables = problem.getVariableDimension();
        m_variables = new Variable[m_freeVariables];
        for (int i = 0; i < m_freeVariables; i++) m_variables[i] = problem.getVariable(i);

        m_unsolvedClauses = problem.getClauseDimension();
        m_clauses = new Clause[m_unsolvedClauses];
        for (int i = 0; i < m_unsolvedClauses; i++) m_clauses[i] = problem.getClause(i);

        // m_learntClauses = new LinkedList<Clause>();

        return solve(m_freeVariables, m_unsolvedClauses);
    }
    
    public boolean solve(int variablesFree, int clausesUnsolved) {
        m_height++;
        if (m_height > m_heightMax) m_heightMax = m_height;

        if (clausesUnsolved == 0) return true;

        int index = bestVariableIndex(variablesFree); 
        if (index == -1) {
            analysisConflict();
            m_conflicts++;
            m_freeVariables++;
            m_height--;
            return false;
        }

        Variable variable = permuteVariable(index);
        boolean valueIni = variable.getValue();
        
        boolean unsat = true;
        do {
            index = 0;
            unsat = false;
            variable.propagate();
            m_instances++;
            
            while (!unsat && index < m_unsolvedClauses) {
                if (m_clauses[index].isSat()) permuteClause(index);
                else if (m_clauses[index].isUnsat()) {
                    unsat = true; 
                    m_conflicts++;
                }
                else index++;
            }
            if (!unsat) unsat = !solve(m_freeVariables, m_unsolvedClauses);
            if (unsat) {
                m_unsolvedClauses = clausesUnsolved;
                variable.unpropagate();
                variable.setValue(!variable.getValue());
                m_backtrack++;
            }
        } while (unsat && !variable.isHeuristicSafe(valueIni) && variable.getValue() != valueIni);

        m_height--;
        m_freeVariables++;
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
    
    public void analysisConflict() {}

    public Clause permuteClause(int index) {
        m_unsolvedClauses--;
        Clause clause = m_clauses[index];
        m_clauses[index] = m_clauses[m_unsolvedClauses];
        m_clauses[m_unsolvedClauses] = clause;
        return clause;
    }

    public Variable permuteVariable(int index) {
        m_freeVariables--;
        Variable variable = m_variables[index];
        m_variables[index] = m_variables[m_freeVariables];
        m_variables[m_freeVariables] = variable;
        return variable;
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
