import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class Clause {

    /** Attributs */
    private int m_weight;
    private Problem m_problem;
    private boolean m_sat, m_unsat;

    private int m_size, m_sizeInit;
    private Variable[] m_variables;
    private boolean [] m_maskPos;


    /** Constructeurs */
    public Clause(int weight, Scanner scanner, Problem problem) {
        m_weight = weight;
        m_problem = problem;
	m_sat = false;
	m_unsat = false;

	Vector<Integer> exprInit = new Vector<Integer>();
        int literal = scanner.nextInt();
        while (literal != 0 && scanner.hasNext()) {
            exprInit.add(new Integer(literal));
            literal = scanner.nextInt();
        }

        m_sizeInit = exprInit.size();
	m_size = m_sizeInit;
	
        m_maskPos = new boolean[m_sizeInit];
        m_variables = new Variables[m_sizeInit];
        for (int i = 0; i < m_sizeInit; i++) {
	    Integer literal = exprInit.get(i);
	    m_maskPos[i] = literal.intValue() > 0;
	    m_variables[i] = m_problem.getVariableFromLiteral(literal);
	    m_variables[i].addClause(this, m_mask[i]);
	}
    }

    /** Predicats */
    public boolean isSat() { return m_sat; }

    public boolean isUnsat() { return m_unsat; }
    
    
    

    /** Accesseurs */
    public int getSize() { return m_size; }

    public Integer getLiteral(int index) { return m_expr[index]; }


    /** Methodes */
    public void valid(Variable variable) {
	m_sat = true;
	for (int i = 0; i < m_size; i++) m_variables[i].notifyValid(this, m_maskPos[i]);
    }

    public void reduce(Variable variable) {
	int index = 0;
	while (m_variables[index] != variable) index++;
	
	m_variables[index] = m_variables[m_size-1];
	m_variables[m_size-1] = variable;

	boolean maskPosTmp = m_maskPos[index];
	m_maskPos[index] = m_maskPos[m_size-1];
	m_maskPos[m_size-1] = maskPosTmp;
	
	m_size--;

	for (int i = 0; i < m_size; i++) m_variables[i].notifyReduce(this, m_maskPos[i]);
    }

    public void restoreUntil(Variable variable) {
	while (m_variables[m_size] != variable) m_size++;
	
	for (int i = 0; i < m_size; i++) m_variables[i].notifyRestore(this, m_maskPos[i]);
    }

    public double computeHeuristic() {
        int heuristic = 0;
        for (int i = 0; i < m_size; i++) {
            Integer literal = m_expr[i];
            int exprVar = literal.intValue();
            int heurTmp = 0;
            if (exprVar > 0) heurTmp = m_problem.getVariableFromLiteral(literal).getHeuristicPos();
            else heurTmp = m_problem.getVariableFromLiteral(literal).getHeuristicNeg();
            if (heurTmp < heuristic) heuristic = heurTmp;
        }
        return (double)heuristic; // / (double)m_size;
    }

    public Value propagate(Variable variable) {
        Value result = Value.FALSE;
        for (int i = 0; i < m_size; i++) {
            Integer literal = m_expr[i];
            int expr = literal.intValue();
            if (variable.getId() == expr) {
                if (variable.getValue() == Value.TRUE) return Value.TRUE; 
                else if (variable.getValue() == Value.FALSE) {
                    deleteLiteral(i);
                    i--;
                }
            }
            else if (variable.getId() == -expr) {
                if (variable.getValue() == Value.FALSE) return Value.TRUE;
                else if (variable.getValue() == Value.TRUE) {
                    deleteLiteral(i);
                    i--;
                }
            }
            else result = Value.UNDEFINE; 
        }
        return result;
    }
    
   

    public void resetLiteral(int index) {
        Integer literal = m_expr[index];
        m_expr[index] = m_expr[m_size];
        m_expr[m_size] = literal;
        m_size++;
    }

    public void reset(Variable variable) {
        for (int i = m_size; i < m_expr.length; i++) {
            Integer literal = m_expr[i];
            int expr = literal.intValue();
            if (variable.getId() == expr || variable.getId() == -expr) resetLiteral(i);
        }
    }

    public String toString() {
        String res = "{ w" + m_weight;
        Iterator<Integer> iter = m_exprInit.listIterator();
        while (iter.hasNext()) {
            Integer literal = iter.next();
            int id = literal.intValue();
            res += ", ";
            if (id < 0) res += "not";
            res += m_problem.getVariableFromLiteral(literal);
        }
        res += ", h" + computeHeuristic() + "}";
        return res;
    }

}
