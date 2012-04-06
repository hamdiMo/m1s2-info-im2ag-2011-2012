import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;

public class Clause {

    /** Attributs */
    private int m_weight;
    private List<Integer> m_expr, m_delete;
    private Value m_value;
    
    /** Constructeurs */
    public Clause(int weight, Scanner scanner) {
        m_weight = weight;
	m_delete = new LinkedList<Integer>();
	m_expr = new LinkedList<Integer>();
        
	int var = scanner.nextInt();
        while (var != 0 && scanner.hasNext()) {
            Integer expr = new Integer(var);
            m_expr.add(expr);
	    var = scanner.nextInt();
        }
    }
    
    /** Predicats */
    public boolean isUnsat() { return getSize() == 0; }

    /** Accesseurs */
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

    /** Methodes */
    public boolean propagate(Variable variable) {
	Iterator<Integer> iter = m_expr.listIterator();
        while (iter.hasNext()) {
	    Integer exprVar = iter.next();
            int expr = exprVar.intValue();
	    if (variable.getId() == expr) {
		if (variable.getValue() == Value.TRUE) { return true; }
		else if (variable.getValue() == Value.FALSE) {
		    m_expr.remove(exprVar);
		    m_delete.add(exprVar);
		}
	    }
	    else if (variable.getId() == -expr)
		if (variable.getValue() == Value.FALSE) { return true; }
		else if (variable.getValue() == Value.TRUE) {
		    m_expr.remove(exprVar);
		    m_delete.add(exprVar);
		}
	}
	return false;
    }
    
    public void reset(Variable variable) {
	Iterator<Integer> iter = m_delete.listIterator();
        while (iter.hasNext()) {
	    Integer exprVar = iter.next();
	    int expr = exprVar.intValue();
	    if (variable.getId() == expr || variable.getId() == -expr) {
		m_expr.add(exprVar);
		m_delete.remove(exprVar);
	    }
	}
    }

    public String toString(Vector<Variable> variables) {
        String res = "";
        Iterator<Integer> iter = m_expr.listIterator();
        while (iter.hasNext()) {
            int id = iter.next().intValue();
            if (id < 0) res += "not";
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
