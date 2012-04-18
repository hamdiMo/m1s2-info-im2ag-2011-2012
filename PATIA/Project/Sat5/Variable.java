import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;

public class Variable {

    /** Attributs */
    private int m_id;
    private boolean m_value, m_linked;
    private int m_heuristicPos, m_heuristicNeg;
    private int m_heuristicSafePos, m_heuristicSafeNeg;
    private List<Clause> m_positives, m_negatives, m_propagate;
    
    /** Constructeurs */
    public Variable(int id){
        m_id = id;
        m_value = false;
        m_linked = false;
        m_heuristicPos = 0;
        m_heuristicNeg = 0;
        m_heuristicSafePos = -1;
        m_heuristicSafeNeg = -1;
        m_positives = new LinkedList<Clause>();
        m_negatives = new LinkedList<Clause>();
    }


    /** Accesseurs */
    public int getId() { return m_id; }

    public int getHeuristicPos() { return m_heuristicPos; }

    public int getHeuristicNeg() { return m_heuristicNeg; }
    

    /** Mutateurs */
    public void propagate(boolean value) {
        m_linked = true;
        m_value = value;
        if (value) propagateTrue();
        else propagateFalse();
    }
    
    public void propagateTrue() {
        Iterator<Clause> iter = m_positives.listIterator();
        while (iter.hasNext()) iter.next().valid(this);
	
        iter = m_negatives.listIterator();
        while (iter.hasNext()) iter.next().reduce(this);
    }

    public void propagateFalse() {
        Iterator<Clause> iter = m_negatives.listIterator();
        while (iter.hasNext()) iter.next().valid(this);
	
        iter = m_positives.listIterator();
        while (iter.hasNext()) iter.next().reduce(this);
    }

    /** Methodes */
    public void computeHeuristic() {
        computeHeuristicPos();
        computeHeuristicNeg();
    }

    public void computeHeuristicPos() {
        m_heuristicPos = 0;
        Iterator<Clause> iter = m_positives.listIterator();
        while (iter.hasNext()) {
            Clause cl = iter.next();
            if (!cl.isSat()) m_heuristicPos++; 
        }
    }

    public void computeHeuristicNeg() {
        m_heuristicNeg = 0;
        Iterator<Clause> iter = m_negatives.listIterator();
        while (iter.hasNext()) {
            Clause cl = iter.next();
            if (!cl.isSat()) m_heuristicNeg++; 
        }
    }

    /** Notification par les clauses */
    public void notifyReduce(Clause clause, boolean literalPos) { /** Do nothing */ }
    
    public void notifyValid(Clause clause, boolean literalPos) {
        if (literalPos) removePositive(clause);
        else removeNegative(clause);
    }

    public void notifyRestore(Clause clause, boolean literalPos) {
        if (literalPos) addPositive(clause);
        else addNegative(clause);
    }


    /** Liaison avec les clauses */
    public void addClause(Clause clause, boolean pos) {
        if (pos) addPositive(clause);
        else addNegative(clause);
    }
    
    public void addPositive(Clause clause) { 
        m_heuristicPos += 1;
        m_positives.add(clause); 
        if (m_heuristicSafePos == -1 || m_heuristicSafePos > clause.getSize()) 
            m_heuristicSafePos = clause.getSize();
    }
    
    public void addNegative(Clause clause) {
        m_heuristicNeg += 1;
        m_negatives.add(clause); 
        if (m_heuristicSafeNeg == -1 || m_heuristicSafeNeg > clause.getSize()) 
            m_heuristicSafeNeg = clause.getSize();
    }
    
    public void removePositive(Clause clause) { 
        m_heuristicPos -= 1;
        m_positives.remove(clause); 
        // Penser a recalculer m_heuristicSafePos
    }

    public void removeNegative(Clause clause) {
        m_heuristicNeg -= 1;
        m_negatives.remove(clause); 
        // Penser a recalculer m_heuristicSafeNeg
    }


    /** Methode d'affichage */
    public String toString(){
        String res = "(" + m_id + ", +" + m_heuristicPos + ", -" + m_heuristicNeg;
        if (m_linked) res += ", " + m_value;
        res += ")"; 
        return res;
    }
    
}