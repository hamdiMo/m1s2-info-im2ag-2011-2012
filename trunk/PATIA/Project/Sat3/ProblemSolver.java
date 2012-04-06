import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

class ProblemSolver {

    /** Types internes */
    public enum Format { CNF , WCNF }

    /** Attributs */
    private Format m_format;
    private int m_nvar, m_ncl, m_thresh;
    private Vector<Variable> m_variables;
    private Vector<Clause> m_clauses;

    /** Constructeurs */
    public ProblemSolver(Scanner scanner) {
        List<String> head = null;
        while (head == null && scanner.hasNextLine()) head = getHead(scanner.nextLine());
        if (head.get(0).equals("cnf")) m_format = Format.CNF;
        else if (head.get(0).equals("wcnf")) m_format = Format.WCNF;
        else throw new RuntimeException();
        m_nvar = new Integer(head.get(1)).intValue();
        m_ncl = new Integer(head.get(2)).intValue();
        m_thresh = 0;
        if (head.size() > 3) m_thresh = new Integer(head.get(3)).intValue();

        m_variables = new Vector<Variable>(m_nvar);
        for (int i = 0; i < m_nvar; i++) m_variables.add(i, new Variable(i+1));
        
        m_clauses = new Vector<Clause>(m_ncl);
        for (int i = 0; i < m_ncl; i++) {
            Clause clause = null;
            switch (m_format) {
            case CNF :
                clause = new Clause(1, scanner, this);
                break;
            case WCNF :
                int weight = scanner.nextInt();
                clause = new Clause(weight, scanner, this);
                break;
            }
            m_clauses.add(i, clause);
        }
    }

    /** Accesseurs */
    public Value getValue(Integer expr) {
        int exprInt = expr.intValue();
        if (exprInt > 0) {
            switch (m_variables.get(1-exprInt).getValue()) {
            case TRUE : return Value.FALSE;
            case FALSE : return Value.TRUE;
            case UNDEFINE: return Value.UNDEFINE;
            }
        }
        return m_variables.get(exprInt-1).getValue();
    }

    public Variable getVariable(Integer expr) { return m_variables.get(Math.abs(expr.intValue())-1); }

    public Vector<Variable> getVariables() { return m_variables; }
    
    public Vector<Clause> getClauses() { return m_clauses; }

    /** Methodes */
    public boolean solve() {
        m_clauses = m_problem.getClauses();
        m_variables = m_problem.getVariables();
        return solve(0);
    }

    public boolean solve(int lvIndex, int pcIndex) {
        boolean unsat = false;
        int nlvIndex = lvIndex, npcIndex = pcIndex, iteration = 0;

        do {
            int bmcIndex = chooseBestMinimalClause(pcIndex);
            int bvIndex = m_clauses.get(bmcIndex).linkedBestVariable(0);
            permuteClause(npcIndex, bmcIndex); npcIndex++;
            permuteVariable(nlvIndex, bvIndex); nlvIndex++;
            
            do {
                bmcIndex = npcIndex-1;
                for (int i = npcIndex; i < m_ncl; i++) {
                    m_clauses.get(i).propagate(m_variables.get(nlvIndex-1));
                    if (m_clauses.get(i).getValue() == Value.FALSE) unsat = true;
                    if (bmcIndex == npcIndex-1 && m_clauses.get(i).getSize() == 1) bmcIndex = i;
                }
                if (bmcIndex != npcIndex-1) {
                    bvIndex = m_clauses.get(bmcIndex).linkedBestVariable(0);
                    permuteClause(npcIndex, bmcIndex); npcIndex++;
                    permuteVariable(nlvIndex, bvIndex); nlvIndex++;
                }
            } while (bmcIndex != npcIndex-2 && !unsat);
            
            if (!unsat) unsat = solve(nlvIndex, npcIndex);

            if (unsat) {
                // restore version lvIndex, pcIndex
                iteration++;
            } 
        } while (unsat && iteration < m_clauses.get(pcIndex).getSize());
        if (unsat) {
            return false;
        }
        return true;
    }
    
    public int chooseBestMinimalClause(int k) {
        int bmcIndex = k;
        double bmcValue = m_clauses.get(k).getHeuristic(); 
        for (int i = k+1; i < m_ncl; i++) {
            if (m_clauses.get(i).getSize() < m_clauses.get(bmcIndex).getSize()) {
                bmcIndex = i;
                bmcValue = m_clauses.get(i).getHeuristic();
            }
            else if (m_clauses.get(i).getSize() == m_clauses.get(bmcIndex).getSize()) {
                double value = m_clauses.get(i).getHeuristic();
                if (value > bmcValue) {
                    bmcIndex = i;
                    bmcValue = value;
                }
            }
        }
        return bmcIndex;
    }

    public void permuteClause(int index1, int index2) {
        Clause c1 = m_clauses.get(index1);
        Clause c2 = m_clauses.get(index2);
        m_clauses.set(index1, c2);
        m_clauses.set(index2, c1);
    }

    public void permuteVariable(int index1, int index2) {
        Variable v1 = m_variables.get(index1);
        Variable v2 = m_variables.get(index2);
        m_variables.set(index1, v2);
        m_variables.set(index2, v1);
    }

    public String toString() {
        String res = "Variables = {\n";
        for (int i = 0; i < m_nvar; i++) res += "\t" + m_variables.get(i) + "\n";
        res += "}\nClauses = {\n";
        for (int i = 0; i < m_ncl; i++) res += "\t" + m_clauses.get(i) + "\n";
        res += "}";
        return res;
    }

    /** Methodes internes */
    private List<String> getHead(String line) {
        if (line != null && line.length() > 0 && line.charAt(0) == 'p') return cleanLine(line, 1);
        return null;
    }
    
    private LinkedList<String> cleanLine(String line, int index) {
        LinkedList<String> result;
        int indexF = index;
        while (index < line.length() && (line.charAt(index) == ' ' || line.charAt(index) == '\t')) indexF = ++index;
        while (indexF < line.length() && line.charAt(indexF) != ' ' && line.charAt(indexF) != '\t') indexF++;
        if (indexF < line.length()) result = cleanLine(line, indexF);
        else result = new LinkedList<String>();
        if (indexF > index) result.addFirst(line.substring(index, indexF));
        return result; 
    }
}
