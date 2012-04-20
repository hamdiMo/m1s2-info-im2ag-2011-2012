import java.util.Scanner;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Vector;
import java.util.Random;

public class Clause {

    /** Attributs */
    private int m_weight;
    private boolean m_tautology, m_sat;

    private int m_size, m_sizeInit;
    private Variable[] m_variables;
    private boolean[] m_maskPos;


    /** Constructeurs */
    public Clause(int weight, Scanner scanner, Problem problem) {
        m_weight = weight;
        m_tautology = false;
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
            m_variables[i] = problem.getVariableFromLiteral(literal);
        }

        for (int i = 0; i < m_sizeInit; i++) {
            for (int j = i+1; j < m_sizeInit; j++) {
                if (m_variables[i] == m_variables[j]) {
                    if (m_maskPos[i] == m_maskPos[j]) {
                        m_sizeInit--;
                        m_variables[j] = m_variables[m_sizeInit];
                        m_maskPos[j] = m_maskPos[m_sizeInit];
                        if (j < m_size) m_size--;
                        j--;
                    }
                    else m_tautology = true;
                } 
            }
        }
	
        if (!m_tautology) {
            for (int i = 0; i < m_sizeInit; i++) m_variables[i].addClause(this, m_maskPos[i]);
            if (m_size == 1) m_variables[0].setSafe(m_maskPos[0]);
        }
    }

    public Clause(int size, Problem problem) {
        m_weight = 1;
        m_tautology = false;
        m_sat = false;

        m_sizeInit = size;
        m_size = size;

        m_variables = new Variable[m_sizeInit];
        m_maskPos = new boolean[m_sizeInit];

        Random rand = new Random();
        for (int j = 0; j < m_sizeInit; j++) {
            m_maskPos[j] = (rand.nextInt()%2 == 0);
            m_variables[j] = problem.getVariable(rand.nextInt(problem.getVariableDimension()));
        }

        for (int i = 0; i < m_sizeInit; i++) {
            for (int j = i+1; j < m_sizeInit; j++) {
                if (m_variables[i] == m_variables[j]) {
                    if (m_maskPos[i] == m_maskPos[j]) {
                        m_sizeInit--;
                        m_variables[j] = m_variables[m_sizeInit];
                        m_maskPos[j] = m_maskPos[m_sizeInit];
                        if (j < m_size) m_size--;
                        j--;
                    }
                    else m_tautology = true;
                } 
            }
        }

        if (!m_tautology) {
            for (int i = 0; i < m_sizeInit; i++) m_variables[i].addClause(this, m_maskPos[i]);
            if (m_size == 1) m_variables[0].setSafe(m_maskPos[0]);
        }
    }

    public Clause(Clause clause1, Clause clause2, Variable variable) {
        if (clause1.m_weight > 0 && clause2.m_weight > 0) m_weight = -1;
        else if (clause1.m_weight > 0) m_weight = clause2.m_weight - 1;
        else if (clause2.m_weight > 0) m_weight = clause1.m_weight - 1;
        else m_weight = clause1.m_weight + clause2.m_weight - 1;
        m_tautology = false;
        m_sat = false;
        m_sizeInit = 0;
        m_size = 0;

        m_maskPos = new boolean[clause1.m_sizeInit + clause2.m_sizeInit - 2];
        m_variables = new Variable[clause1.m_sizeInit + clause2.m_sizeInit - 2];
        for (int i = 0; i < clause1.m_sizeInit; i++) {
            if (variable != clause1.m_variables[i]) {
                if (m_sizeInit > m_size) {
                    m_variables[m_sizeInit] = m_variables[m_size];
                    m_maskPos[m_sizeInit] = m_maskPos[m_size];
                }
                m_sizeInit++;
                m_variables[m_size] = clause1.m_variables[i];
                m_maskPos[m_size] = clause1.m_maskPos[i];
                if (m_variables[m_size].isFree()) m_size++;
                else if (m_variables[m_size].isValue(m_maskPos[m_size])) m_sat = true;
            }
        }

        for (int i = 0; i < clause2.m_sizeInit; i++) {
            if (variable != clause2.m_variables[i]) {
                if (m_sizeInit > m_size) {
                    m_variables[m_sizeInit] = m_variables[m_size];
                    m_maskPos[m_sizeInit] = m_maskPos[m_size];
                }
                m_sizeInit++;
                m_variables[m_size] = clause2.m_variables[i];
                m_maskPos[m_size] = clause2.m_maskPos[i];
                if (m_variables[m_size].isFree()) m_size++;
                else if (m_variables[m_size].isValue(m_maskPos[m_size])) m_sat = true;
            }
        }

        for (int i = 0; i < m_sizeInit; i++) {
            for (int j = i+1; j < m_sizeInit; j++) {
                if (m_variables[i] == m_variables[j]) {
                    if (m_maskPos[i] == m_maskPos[j]) {
                        m_sizeInit--;
                        m_variables[j] = m_variables[m_sizeInit];
                        m_maskPos[j] = m_maskPos[m_sizeInit];
                        if (j < m_size) m_size--;
                        j--;
                    }
                    else m_tautology = true;
                } 
            }
        }

        if (!m_tautology && !m_sat) {
            for (int i = 0; i < m_sizeInit; i++) m_variables[i].addClause(this, m_maskPos[i]);
            if (m_size == 1) m_variables[0].setSafe(m_maskPos[0]);
        }

        // if (!m_sat) {
        //     System.out.println("Conflit sur " + variable);
        //     System.out.println("\t" + clause1);
        //     System.out.println("\t" + clause2);
        //     System.out.println("Resolution = " + this + "\n");
        // }
    }


    /** Predicats */
    public boolean isTautology() { return m_tautology; }

    public boolean isSat() { return m_sat; }

    public boolean isUnsat() { return m_size == 0; }
    

    /** Accesseurs */
    public int getSize() { return m_size; }

    public int getWeight() { return m_weight; }


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
        m_size--;

        int index = 0;
        while (m_variables[index] != variable) index++;

        m_variables[index] = m_variables[m_size];
        m_variables[m_size] = variable;

        boolean maskPosTmp = m_maskPos[index];
        m_maskPos[index] = m_maskPos[m_size];
        m_maskPos[m_size] = maskPosTmp;

        if (m_size == 1) m_variables[0].setSafe(m_maskPos[0]);
    }

    public void restore(Variable variable) {
	if (m_size == 1) m_variables[0].setUnsafe(m_maskPos[0]); 

        int index = m_size;
        while (m_variables[index] != variable) index++;

        m_variables[index] = m_variables[m_size];
        m_variables[m_size] = variable;
        
        boolean maskPos = m_maskPos[index];
        m_maskPos[index] = m_maskPos[m_size];
        m_maskPos[m_size] = maskPos;
        
        m_size++;
    }
    
    
    /** Affichage */
    public String toString() {
        String res = "";
        for (int i = 0; i < m_sizeInit; i++) {
            if (!m_maskPos[i]) res += "-";
            res += m_variables[i].getId();
            res += " ";
        }
        return res;
    }
}
