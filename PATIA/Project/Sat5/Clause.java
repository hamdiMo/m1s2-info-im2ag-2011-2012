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
    private boolean[] m_maskPos;


    /** Constructeurs */
    public Clause(int weight, Scanner scanner, Problem problem) {
        m_weight = weight;
        m_problem = problem;
        m_sat = false;
        m_unsat = false;

        Vector<Integer> exprInit = new Vector<Integer>();
        int var = scanner.nextInt();
        while (var != 0 && scanner.hasNext()) {
            exprInit.add(new Integer(var));
            var = scanner.nextInt();
        }

        m_sizeInit = exprInit.size();
        m_size = m_sizeInit;
	
        m_maskPos = new boolean[m_sizeInit];
        m_variables = new Variable[m_sizeInit];
        for (int i = 0; i < m_sizeInit; i++) {
            Integer literal = exprInit.get(i);
            m_maskPos[i] = literal.intValue() > 0;
            m_variables[i] = m_problem.getVariableFromLiteral(literal);
            m_variables[i].addClause(this, m_maskPos[i]);
        }
    }


    /** Predicats */
    public boolean isSat() { return m_sat; }

    public boolean isUnsat() { return m_unsat; }
    

    /** Accesseurs */
    public int getSize() { return m_size; }


    /** Methodes */
    public void valid(Variable variable) {
        m_sat = true;
        for (int i = 0; i < m_size; i++)
            if (m_variables[i] != variable)
                m_variables[i].notifyValid(this, m_maskPos[i]);
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

        for (int i = 0; i < m_size; i++)
            if (m_variables[i] != variable)
                m_variables[i].notifyReduce(this, m_maskPos[i]);
    }

    public void restoreUntil(Variable variable) {
        while (m_variables[m_size] != variable) m_size++;
	
        for (int i = 0; i < m_size; i++)
            if (m_variables[i] != variable)
                m_variables[i].notifyRestore(this, m_maskPos[i]);
    }


    /** Affichage */
    public String toString() {
        String res = "{ w" + m_weight;
        for (int i = 0; i < m_sizeInit; i++) {
            res += ", ";
            if (!m_maskPos[i]) res += "not";
            res += m_variables[i];
        }
        res += "}";
        return res;
    }

}
