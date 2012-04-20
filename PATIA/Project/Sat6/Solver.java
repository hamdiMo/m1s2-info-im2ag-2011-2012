import java.io.File;
import java.io.PrintStream;
import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class Solver {

    /** Attributs */
    private Clause[] m_clauses;
    private Variable[] m_variables;
    private List<Clause> m_learntClauses;
    private int m_unsolvedClauses, m_freeVariables;
    private int m_instances, m_conflicts, m_heightMax, m_node;
    private PrintStream m_graphFile;
   

    /** Constructeurs */
    public Solver() {
        m_instances = 0;
        m_conflicts = 0;
        m_heightMax = 0;
        m_node = 0;
        m_graphFile = null;
    }

    public Solver(File graphFile) {
        this();
        try { m_graphFile = new PrintStream(graphFile); }
        catch(java.io.FileNotFoundException e) {
            m_graphFile = null;
        }
    }
    

    /** Accesseurs */
    public int getInstances() { return m_instances; }
    public int getConflicts() { return m_conflicts; }
    public int getHeigthMax() { return m_heightMax; }
    public int getLearntClauses() { return m_learntClauses.size(); }


    /** Methodes */
    public boolean solve(Problem problem) {
        m_freeVariables = problem.getVariableDimension();
        m_variables = new Variable[m_freeVariables];
        for (int i = 0; i < m_freeVariables; i++) m_variables[i] = problem.getVariable(i);

        m_unsolvedClauses = problem.getClauseDimension();
        m_clauses = new Clause[m_unsolvedClauses];
        for (int i = 0; i < m_unsolvedClauses; i++) m_clauses[i] = problem.getClause(i);

        for (int i = 0; i < m_unsolvedClauses; i++) {
            if (m_clauses[i].isTautology()) {
                permuteClause(i); 
                i--;
            }
            else if (m_clauses[i].isUnsat()) return false;
        }

        m_learntClauses = new LinkedList<Clause>();
        
        if (m_graphFile != null) startGraph();

        boolean res = solve(m_freeVariables, m_unsolvedClauses);

        if (m_graphFile != null) endGraph();
        return res;
    }
    
    public boolean solve(int freeVariables, int unsolvedClauses) {
        if (unsolvedClauses == 0) {
            if (m_graphFile != null) {
                m_graphFile.println("\t" + "node [shape = box];");
                m_graphFile.println("\t" + m_node + " -> success;");
                m_graphFile.println("\t" + "node [shape = circle];");
            }
            return true;
        }
        if (m_variables.length - freeVariables > m_heightMax) m_heightMax = m_variables.length - freeVariables;
        int node = m_node;
        
        Variable variable = permuteVariable(bestVariableIndex(freeVariables));
        boolean valueIni = variable.getValue();
        
        boolean unsat = true;
        do {
            int index = 0;
            unsat = false;

            if (m_graphFile != null) {
                m_node++;
                m_graphFile.print("\t" + node + " -> " + m_node + " [label = \"");
                if (!variable.getValue()) m_graphFile.print("-");
                m_graphFile.println("" + variable.getId() + "\"];");
            }

            variable.propagate();
            m_instances++;
            
            while (!unsat && index < m_unsolvedClauses) {
                if (m_clauses[index].isSat()) permuteClause(index);
                else if (m_clauses[index].isUnsat()) {
                    unsat = true;
                    if (m_graphFile != null) {
                        m_graphFile.println("\t" + "node [shape = box];");
                        m_graphFile.println("\t" + m_node + " -> \"conflict " + m_conflicts + "\";");
                        m_graphFile.println("\t" + "node [shape = circle];");
                    }
                    // analysisConflict(index);
                    m_conflicts++;
                }
                else index++;
            }
            if (!unsat) unsat = !solve(m_freeVariables, m_unsolvedClauses);
            if (unsat) {
                variable.unpropagate();
                m_unsolvedClauses = unsolvedClauses;
                variable.setValue(!variable.getValue());
            }
        } while (unsat && !variable.isHeuristicSafe(valueIni) && variable.getValue() != valueIni);

        m_freeVariables++;
        return !unsat;
    }
    
    public int bestVariableIndex(int variablesFree) {
        int index = -1, heuristicMax = 0, heuristicMin = 0;
        for (int i = 0; i < variablesFree; i++) {
            int heuristicPos = m_variables[i].getHeuristicPos();
            int heuristicNeg = m_variables[i].getHeuristicNeg();
            if (m_variables[i].isHeuristicPosSafe()) heuristicPos += m_unsolvedClauses;
            if (m_variables[i].isHeuristicNegSafe()) heuristicNeg += m_unsolvedClauses;
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
    
    public void analysisConflict(int index) {
        Variable variable = m_variables[m_freeVariables];
        List<Clause> clauses = variable.getClauses(variable.getValue());
        Iterator<Clause> iter = clauses.listIterator();
        while (iter.hasNext()) {
            Clause clause = iter.next();
            if (clause.getSize() == 1 && clause.getWeight() > 0) {
                Clause resolution = new Clause(m_clauses[index], clause, variable);
                if (!resolution.isTautology()) {
                    if (m_graphFile != null) {
                        m_graphFile.println("\t" + "node [shape = box];");
                        m_graphFile.println("\t" + "\"conflict " + m_conflicts + "\" -> \"resolution " + resolution + "\";");
                        m_graphFile.println("\t" + "node [shape = circle];");
                    }
                    m_learntClauses.add(resolution);
                }
            }
        }
    }

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
                          + "\t" + "Learning = "  + getLearntClauses() + "\n"
                          + "\t" + "Heightmax = " + getHeigthMax() + "\n"
                          + "}");
    }

    public void startGraph() {
        m_graphFile.println("digraph MTuring {" + "\n"
                            + "\t" + "rankdir=LR;" + "\n"
                            + "\t" + "edge [len = 1.5];" + "\n"
                            + "\t" + "node [shape = circle];" + "\n");
    }

    public void endGraph() { m_graphFile.println("}"); }

}
