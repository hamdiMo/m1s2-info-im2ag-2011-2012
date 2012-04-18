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
        Variable variable = m_variables[index];

        variablesFree--;
        m_variables[index] = m_variables[variablesFree];
        m_variables[variablesFree] = variable;

        System.out.println("Choix variable = " + variable);
        
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
    

    // public boolean solve(int lvIndex, int pcIndex) {
    //     m_height++;
    //     m_iteration++;
    //     if (m_height > m_heightMax) m_heightMax = m_height;

    //     if (!(pcIndex < m_clauseSolved.length)) {
    //         m_height--;
    //         return true;
    //     }
        
    //     //        System.out.println("Hauteur = " + m_height);
        
    //     computeHeuristics();
    //     Clause clause = solveClause(selectBestClause());
    //     Integer[] literals = selectLiteralsFrom(clause);
        
    //     boolean sat = false;
    //     int curVariable = 0;
    //     while (!sat && curVariable < clause.getSize()) {
    //         Variable variable = satisfyLiteral(literals[curVariable]);
    //         m_instances++;

    //         sat = true;
    //         for (int i = pcIndex+1; i < m_clauseSolved.length; i++) {
    //             switch (m_clauseSolved[i].propagate(variable)) {
    //             case TRUE:
    //                 solveClause(i);
    //                 break;
    //             case FALSE:
    //                 m_conflicts++;
    //                 sat = false;
    //                 break;
    //             case UNDEFINE:
    //                 break;
    //             }
    //         }
    //         if (sat) sat = solve(m_variablesLinkedNb, m_clauseSolvedNb);
    //         if (!sat) {
    //             m_backtrack++;
    //             variable.setValue(Value.UNDEFINE);
    //             m_clauseSolvedNb = pcIndex+1;
    //             for (int i = pcIndex+1; i < m_clauseSolved.length; i++)
    //                 m_clauseSolved[i].reset(variable);
    //         }
    //         curVariable++;
    //     }
    //     m_height--;
    //     return sat;
    // }

    // public void computeHeuristics() {
    //     for (int i = m_variablesLinkedNb; i < m_variablesLinked.length; i++)
    //         m_variablesLinked[i].clearHeuristics();
    //     for (int i = m_clauseSolvedNb; i < m_clauseSolved.length; i++) {
    //         Clause clause = m_clauseSolved[i];
    //         for (int j = 0; j < clause.getSize(); j++) {
    //             Integer literal = clause.getLiteral(j);
    //             if (literal.intValue() < 0) m_problem.getVariableFromLiteral(literal).addNegative(clause);
    //             else m_problem.getVariableFromLiteral(literal).addPositive(clause);
    //         }
    //     }
    // } 
        
    // public Integer[] selectLiteralsFrom(Clause clause) {
    //     Integer[] literals = new Integer[clause.getSize()];
    //     double[] heuristics = new double[clause.getSize()];
    //     for (int i = 0; i < literals.length; i++) {
    //         Integer literal = clause.getLiteral(i);
    //         int j = i-1; double heuristic = 0;
    //         if (literal.intValue() < 0) heuristic = m_problem.getVariableFromLiteral(literal).getHeuristicNeg();
    //         else heuristic = m_problem.getVariableFromLiteral(literal).getHeuristicPos();
    //         while (j >= 0 && heuristics[j] < heuristic) {
    //             literals[j+1] = literals[j];
    //             heuristics[j+1] = heuristics[j];
    //             j--;
    //         }
    //         literals[j+1] = literal;
    //         heuristics[j+1] = heuristic;
    //     }
    //     return literals;
    // }
        
    // public int selectBestClause() {
    //     int bmcIndex = m_clauseSolvedNb;
    //     double bmcValue = m_clauseSolved[bmcIndex].computeHeuristic(); 
    //     for (int i = bmcIndex+1; i < m_clauseSolved.length; i++) {
    //         if (m_clauseSolved[i].getSize() < m_clauseSolved[bmcIndex].getSize()) {
    //             bmcIndex = i;
    //             bmcValue = m_clauseSolved[i].computeHeuristic();
    //         }
    //         else if (m_clauseSolved[i].getSize() == m_clauseSolved[bmcIndex].getSize()) {
    //             double value = m_clauseSolved[i].computeHeuristic();
    //             if (value > bmcValue) {
    //                 bmcIndex = i;
    //                 bmcValue = value;
    //             }
    //         }
    //     }
    //     return bmcIndex;
    // }

    // public Clause solveClause(int index) {
    //     Clause clause = m_clauseSolved[index];
    //     m_clauseSolved[index] = m_clauseSolved[m_clauseSolvedNb];
    //     m_clauseSolved[m_clauseSolvedNb] = clause;
    //     m_clauseSolvedNb++;
    //     return clause;
    // }

    // public Variable satisfyLiteral(Integer literal) {
    //     Variable variable = m_problem.getVariableFromLiteral(literal);
    //     if (literal.intValue() > 0) variable.setValue(Value.TRUE);
    //     else variable.setValue(Value.FALSE);
    //     return variable;
    // }


    /** Affichage */
    public String toString() {
        return new String("Solver : " + "\n"
                          + "\t" + "Instances = " + getInstances() + "\n"
                          + "\t" + "Conflicts = " + getConflicts() + "\n"
                          + "\t" + "Backtrack = " + getBacktrack() + "\n"
                          + "\t" + "Heightmax = " + getHeigthMax() + "\n"
                          + "\t" + "Iteration = " + getIteration());
    }

}
