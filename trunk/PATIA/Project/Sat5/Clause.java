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
            Variable variable = m_problem.getVariableFromLiteral(literal); 
            m_variables[i] = variable;
            variable.addClause(this, m_maskPos[i]);
        }

        if (m_size == 1) m_variables[0].setSafe(m_maskPos[0]);
    }

    /** Predicats */
    public boolean isSat() { return m_sat; }

    public boolean isUnsat() { return m_size == 0; }
    

    /** Accesseurs */
    public int getSize() { return m_size; }


    /** Methodes */
    public void valid(Variable variable) {
        m_sat = true;
        for (int i = 0; i < m_size; i++)
            if (m_variables[i] != variable)
                m_variables[i].notifyValid(this, m_maskPos[i]);
    }

    public void unvalid(Variable variable) {
        m_sat = false;
        for (int i = 0; i < m_size; i++)
            if (m_variables[i] != variable)
                m_variables[i].notifyUnvalid(this, m_maskPos[i]);
    }

    public void reduce(Variable variable) {
        int index = 0;
        while (m_variables[index] != variable) index++;

        m_size--;

        m_variables[index] = m_variables[m_size];
        m_variables[m_size] = variable;

        boolean maskPosTmp = m_maskPos[index];
        m_maskPos[index] = m_maskPos[m_size];
        m_maskPos[m_size] = maskPosTmp;

        if (m_size == 1) m_variables[0].setSafe(m_maskPos[0]);
    }

    public void restore(Variable variable) {
        int index = m_size;
        while (m_variables[index] != variable) index++;
        
        m_variables[index] = m_variables[m_size];
        m_variables[m_size] = variable;
        
        boolean maskPos = m_maskPos[index];
        m_maskPos[index] = m_maskPos[m_size];
        m_maskPos[m_size] = maskPos;
        
        m_size++;

        if (m_size-1 == 1) m_variables[0].setUnsafe(m_maskPos[0]); 
    }
    
    
    /** Affichage */
    public String toString() {
        String res = "{ w" + m_weight;
        for (int i = 0; i < m_size; i++) {
            res += ", ";
            if (!m_maskPos[i]) res += "not";
            res += m_variables[i];
        }
        res += " }";
        return res;
    }

}
