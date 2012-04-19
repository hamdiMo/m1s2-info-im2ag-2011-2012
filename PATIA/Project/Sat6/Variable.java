import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;

public class Variable {


    /** Attributs */
    private int m_id;
    private boolean m_value, m_linked;
    private int m_heuristicPos, m_heuristicNeg;
    private boolean m_heuristicPosSafe, m_heuristicNegSafe;
    private List<Clause> m_positives, m_negatives;

    
    /** Constructeurs */
    public Variable(int id){
        m_id = id;
        m_value = false;
        m_linked = false;
        m_heuristicPos = 0;
        m_heuristicNeg = 0;
        m_heuristicPosSafe = false;
        m_heuristicNegSafe = false;
        m_positives = new LinkedList<Clause>();
        m_negatives = new LinkedList<Clause>();
    }


    /** Predicats */
    public boolean isValue(boolean value) { return m_linked && (m_value == value); }

    public boolean isFree() { return !m_linked; }
    
    public boolean isHeuristicSafe(boolean value) {
        if (value) return isHeuristicPosSafe();
        else return isHeuristicNegSafe();
    }

    public boolean isHeuristicPosSafe() { return m_heuristicPosSafe || (m_heuristicPos > 0 && m_heuristicNeg == 0); }

    public boolean isHeuristicNegSafe() { return m_heuristicNegSafe || (m_heuristicNeg > 0 && m_heuristicPos == 0); }


    /** Accesseurs */
    public int getId() { return m_id; }

    public int getHeuristicPos() { return m_heuristicPos; }

    public int getHeuristicNeg() { return m_heuristicNeg; }

    public boolean getValue() { return m_value; }

    public List<Clause> getClauses(boolean valuePos) { 
        if (valuePos) return m_positives;
        else return m_negatives;
    }


    /** Mutateurs */
    public void setValue(boolean value) { m_value = value; }

    public void setSafe(boolean posValue) {
        if (posValue) m_heuristicPosSafe = true;
        else m_heuristicNegSafe = true;
    }

    public void setUnsafe(boolean posValue) {
        if (posValue) m_heuristicPosSafe = false;
        else m_heuristicNegSafe = false;
    }


    /** Methodes */
    public void propagate() {
        m_linked = true;

        Iterator<Clause> iter = m_positives.listIterator();
        while (iter.hasNext()) {
            if (m_value) iter.next().valid(this);
            else iter.next().reduce(this);
        }
        
        iter = m_negatives.listIterator();
        while (iter.hasNext()) {
            if (m_value) iter.next().reduce(this);
            else iter.next().valid(this);
        }
    }
    
    public void unpropagate() {
        m_linked = false;

        Iterator<Clause> iter = m_positives.listIterator();
        while (iter.hasNext()) {
            if (m_value) iter.next().unvalid(this);
            else iter.next().restore(this);
        }

        iter = m_negatives.listIterator();
        while (iter.hasNext()) {
            if (m_value) iter.next().restore(this);
            else iter.next().unvalid(this);
        }
    }


    /** Notification par les clauses */
    public void notifyValid(Clause clause, boolean literalPos) {
        if (literalPos) removePositive(clause);
        else removeNegative(clause);
    }

    public void notifyUnvalid(Clause clause, boolean literalPos) {
        if (literalPos) addPositive(clause);
        else addNegative(clause);
    }


    /** Liaison avec les clauses */
    public void addClause(Clause clause, boolean literalPos) {
        if (literalPos) addPositive(clause);
        else addNegative(clause);
    }
    
    public void addPositive(Clause clause) { 
        m_heuristicPos += 1;
        m_positives.add(clause); 
    }
    
    public void addNegative(Clause clause) {
        m_heuristicNeg += 1;
        m_negatives.add(clause); 
    }
    
    public void removePositive(Clause clause) { 
        m_heuristicPos -= 1;
        m_positives.remove(clause); 
    }

    public void removeNegative(Clause clause) {
        m_heuristicNeg -= 1;
        m_negatives.remove(clause); 
    }


    /** Methode d'affichage */
    public String toString(){
        String res = "(" + m_id + ", +" + m_heuristicPos + ", -" + m_heuristicNeg;
        if (m_linked) res += ", " + m_value;
        res += ")"; 
        return res;
    }
    
}