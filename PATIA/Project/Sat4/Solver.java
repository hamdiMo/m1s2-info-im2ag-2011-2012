import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class Solver {

    /** Attributs */
    private Problem m_problem;
    private Heuristics m_heuristics;
    private Clause[] m_clauseSolved;
    private Variable[] m_variablesLinked;
    private int m_variablesLinkedNb, m_clauseSolvedNb;
    private int m_instances, m_conflicts, m_backtrack, m_height, m_heightMax, m_iteration;
   
    /** Constructeurs */
    public Solver(Problem problem) {
        m_problem = problem;
    }
    
    /** Accesseurs */
    public int getInstances() { return m_instances; }

    public int getConflicts() { return m_conflicts; }

    public int getBacktrack() { return m_backtrack; }

    public int getHeigthMax() { return m_heightMax; }

    public int getIteration() { return m_iteration; }

    /** Methodes */
    public boolean solve() {
        m_instances = 0;
        m_conflicts = 0;
        m_backtrack = 0;
        m_height = 0;
        m_heightMax = 0;
        
        m_variablesLinked = new Variable[m_problem.getVariableDimension()];
        for (int i = 0; i < m_variablesLinked.length; i++)
            m_variablesLinked[i] = m_problem.getVariable(i);

        m_clauseSolved = new Clause[m_problem.getClauseDimension()];
        for (int i = 0; i < m_clauseSolved.length; i++)
            m_clauseSolved[i] = m_problem.getClause(i);
        
        m_clauseSolvedNb = 0;
        m_variablesLinkedNb = 0;

        return solve(m_variablesLinkedNb, m_clauseSolvedNb);
    }
    
    public boolean solve(int lvIndex, int pcIndex) {
        m_height++;
        m_iteration++;
        if (m_height > m_heightMax) m_heightMax = m_height;

        if (!(pcIndex < m_clauseSolved.length)) {
            m_height--;
            return true;
        }
        
        //        System.out.println("Hauteur = " + m_height);
        
        updateHeuristics();
        Clause clause = solveClause(selectBestClause());
        Integer[] literals = selectLiteralsFrom(clause);
        
        boolean sat = false;
        int curVariable = 0;
        while (!sat && curVariable < clause.getSize()) {
            Variable variable = satisfyLiteral(literals[curVariable]);
            m_instances++;

            sat = true;
            for (int i = pcIndex+1; i < m_clauseSolved.length; i++) {
                switch (m_clauseSolved[i].propagate(variable)) {
                case TRUE:
                    solveClause(i);
                    break;
                case FALSE:
                    m_conflicts++;
                    sat = false;
                    break;
                case UNDEFINE:
                    break;
                }
            }
            if (sat) sat = solve(m_variablesLinkedNb, m_clauseSolvedNb);
            if (!sat) {
                m_backtrack++;
                variable.setValue(Value.UNDEFINE);
                m_clauseSolvedNb = pcIndex+1;
                for (int i = pcIndex+1; i < m_clauseSolved.length; i++)
                    m_clauseSolved[i].reset(variable);
            }
            curVariable++;
        }
        m_height--;
        return sat;
    }

    public void updateHeuristics() {
        for (int i = m_variablesLinkedNb; i < m_variablesLinked.length; i++)
            m_variablesLinked[i].clearHeuristics();
        for (int i = m_clauseSolvedNb; i < m_clauseSolved.length; i++) {
            Clause clause = m_clauseSolved[i];
            for (int j = 0; j < clause.getSize(); j++) {
                Integer literal = clause.getLiteral(j);
                if (literal.intValue() < 0) m_problem.getVariableFromLiteral(literal).addNegative(clause);
                else m_problem.getVariableFromLiteral(literal).addPositive(clause);
            }
        }
    } 
        
    public Integer[] selectLiteralsFrom(Clause clause) {
        Integer[] literals = new Integer[clause.getSize()];
        double[] heuristics = new double[clause.getSize()];
        for (int i = 0; i < literals.length; i++) {
            Integer literal = clause.getLiteral(i);
            int j = i-1; double heuristic = 0;
            if (literal.intValue() < 0) heuristic = m_problem.getVariableFromLiteral(literal).getHeuristicNeg();
            else heuristic = m_problem.getVariableFromLiteral(literal).getHeuristicPos();
            while (j >= 0 && heuristics[j] < heuristic) {
                literals[j+1] = literals[j];
                heuristics[j+1] = heuristics[j];
                j--;
            }
            literals[j+1] = literal;
            heuristics[j+1] = heuristic;
        }
        return literals;
    }
        
    public int selectBestClause() {
        int bmcIndex = m_clauseSolvedNb;
        double bmcValue = m_clauseSolved[bmcIndex].computeHeuristic(); 
        for (int i = bmcIndex+1; i < m_clauseSolved.length; i++) {
            if (m_clauseSolved[i].getSize() < m_clauseSolved[bmcIndex].getSize()) {
                bmcIndex = i;
                bmcValue = m_clauseSolved[i].computeHeuristic();
            }
            else if (m_clauseSolved[i].getSize() == m_clauseSolved[bmcIndex].getSize()) {
                double value = m_clauseSolved[i].computeHeuristic();
                if (value > bmcValue) {
                    bmcIndex = i;
                    bmcValue = value;
                }
            }
        }
        return bmcIndex;
    }

    public Clause solveClause(int index) {
        Clause clause = m_clauseSolved[index];
        m_clauseSolved[index] = m_clauseSolved[m_clauseSolvedNb];
        m_clauseSolved[m_clauseSolvedNb] = clause;
        m_clauseSolvedNb++;
        return clause;
    }

    public Variable satisfyLiteral(Integer literal) {
        Variable variable = m_problem.getVariableFromLiteral(literal);
        if (literal.intValue() > 0) variable.setValue(Value.TRUE);
        else variable.setValue(Value.FALSE);
	return variable;
    }

    public String toString() {
        String res = "Variables = {\n";
        for (int i = m_variablesLinkedNb; i < m_variablesLinked.length; i++) 
            res += "\t" + m_variablesLinked[i] + "\n";
        res += "}\nClauses = {\n";
        for (int i = m_clauseSolvedNb; i < m_clauseSolved.length; i++) 
            res += "\t" + m_clauseSolved[i] + "\n";
        res += "}";
        return res;
    }

}
