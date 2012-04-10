import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class Clause {

    /** Attributs */
    private Problem m_problem;
    private int m_weight, m_size;
    private Integer[] m_expr;
    private Vector<Integer> m_exprInit;
    
    /** Constructeurs */
    public Clause(int weight, Scanner scanner, Problem problem) {
        m_weight = weight;
        m_problem = problem;

        m_exprInit = new Vector<Integer>();
        int literal = scanner.nextInt();
        while (literal != 0 && scanner.hasNext()) {
            m_exprInit.add(new Integer(literal));
            literal = scanner.nextInt();
        }

        m_size = m_exprInit.size();
        m_expr = new Integer[m_size];
        for (int i = 0; i < m_size; i++) m_expr[i] = m_exprInit.get(i);
    }

    
    /** Accesseurs */
    public int getSize() { return m_size; }

    public Integer getLiteral(int index) { return m_expr[index]; }


    /** Methodes */
    public double computeHeuristic() {
        int heuristic = 0;
        for (int i = 0; i < m_size; i++) {
            Integer literal = m_expr[i];
            int exprVar = literal.intValue();
            if (exprVar > 0) heuristic += m_problem.getVariableFromLiteral(literal).getHeuristicPos();
            else heuristic += m_problem.getVariableFromLiteral(literal).getHeuristicNeg();
        }
        return (double)heuristic / (double)m_size;
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
    
    public void deleteLiteral(int index) {
        Integer literal = m_expr[index];
        m_expr[index] = m_expr[m_size-1];
        m_expr[m_size-1] = literal;
        m_size--;
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
