import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class Clause {

    /** Attributs */
    private int m_weight;
    private Problem m_problem;
    private List<Integer> m_expr, m_initExpr;
    private Value m_value;

    /** Constructeurs */
    public Clause(int weight, Scanner scanner, Problem problem) {
        m_weight = weight;
        m_problem = problem;
        m_initExpr = new LinkedList<Integer>();
        m_expr = new LinkedList<Integer>();
        int var = scanner.nextInt();
        while (var != 0 && scanner.hasNext()) {
            Integer expr = new Integer(var);
            m_expr.add(expr);
            m_initExpr.add(expr);
            var = scanner.nextInt();
        }
    }

    /** Accesseurs */
    public Value getValue() { return m_value; }

    public int getSize() { return m_expr.size(); }

    public double getHeuristic() { 
        int heuristic = 0;
        Iterator<Integer> iter = m_expr.listIterator();
        while (iter.hasNext()) {
            Integer exprVarInt = iter.next();
            int exprVar = exprVarInt.intValue();
            if (exprVar > 0) heuristic += m_problem.getVariables(exprVarInt).getHeuristicPos();
            else heuristic += m_problem.getVariables(exprVarInt).getHeuristicNeg();
        }
        return (double)heuristic / m_expr.size();
    }

    /** Mutateurs */
    
    /** Methodes */
    public Value computeValue() {
        m_value = Value.FALSE;
        Iterator<Integer> iter = m_expr.listIterator();
        while (m_value != Value.TRUE && iter.hasNext()) {
            switch (getValueFrom(iter.next())) {
            case TRUE:
                m_value = Value.TRUE;
                break;
            case FALSE:
                break;
            case UNDEFINE:
                m_value = Value.UNDEFINE;
                break;
            }
        }
        return m_value;
    }

    public Value computePropagation(Variable variable, int iteration) {
        Iterator<Integer> iter = m_expr.listIterator();
        while (iter.hasNext()) {
            Integer expr = iter.next();
            if (variable == problem.getVariables(expr)) {
                /** TO DO */
            }
        }
    }

    public void reduce() {
        List<Integer> m_trueExpr = new LinkedList<Integer>();
        List<Integer> m_newExpr = new LinkedList<Integer>();
        Iterator<Integer> iter = m_expr.listIterator();
        while (m_trueExpr.isEmpty() && iter.hasNext()) {
            int id = iter.next().intValue();
            if (id > 0) {
                if (m_variables.get(id-1).getValue() == Value.TRUE) 
                    m_trueExpr.add(new Integer(id));
                else if (m_variables.get(id-1).getValue() == Value.UNDEFINE) 
                    m_newExpr.add(new Integer(id));
            } else if (id < 0) {
                if (m_variables.get(1-id).getValue() == Value.FALSE)
                    m_trueExpr.add(new Integer(id));
                else if (m_variables.get(1-id).getValue() == Value.UNDEFINE)
                    m_newExpr.add(new Integer(id));
            }
        }
        if (m_trueExpr.isEmpty()) m_expr = m_newExpr;
        else m_expr = m_trueExpr;
    }

    public String toString() {
        String res = "";
        Iterator<Integer> iter = m_expr.listIterator();
        while (iter.hasNext()) {
            int id = iter.next().intValue();
            if (id > 0) res += m_variables.get(id-1);
            else res += "not" + m_variables.get(1-id);
            res += " ";
        }
        return res;
    }

    /** Methodes interne */
    private Value getValueFrom(Integer integer) {
        Variable var = getVarFrom(integer);
        int id = integer.intValue();
        switch (var.getValue()) {
        case TRUE:
            if (id > 0) return Value.TRUE;
            else return Value.FALSE;
        case FALSE:
            if (id > 0) return Value.FALSE;
            else return Value.TRUE;
        case UNDEFINE :
            return Value.UNDEFINE;
        }
        return Value.UNDEFINE;
    }

    private Variable getVarFrom(Integer integer) {
        int id = integer.intValue();
        if (id < 0) id = 1-id;
        else if (id > 0) id = id-1;
        return m_variables.get(id);
    }


}
