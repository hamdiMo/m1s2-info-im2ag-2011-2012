import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class Problem {

    /** Types internes */
    public enum Format { CNF , WCNF }

    /** Attributs */
    private Format m_format;
    private int m_nvar, m_ncl, m_thresh;
    private Vector<Variable> m_variables;
    private Vector<Clause> m_clauses;

    /** Constructeurs */
    public Problem(Scanner scanner) {
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
    public int getVariableDimension() { return m_nvar; }
    public Variable getVariable(int index) { return m_variables.get(index); }

    public int getClauseDimension() { return m_ncl; }
    public Clause getClause(int index) { return m_clauses.get(index); }

    public Variable getVariableFromLiteral(Integer literal) {
        return getVariable(Math.abs(literal.intValue())-1); 
    }

    /** Methodes */
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
