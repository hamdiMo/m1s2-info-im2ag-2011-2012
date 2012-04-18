import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;

public class Variable {

    /** Attributs */
    private int m_id;
    private Value m_value;
    private int m_heuristicPos, m_heuristicNeg;
    // private List<Clause> m_positives, m_negatives;
    
    /** Constructeurs */
    public Variable(int id) {
        m_id = id;
        m_value = Value.UNDEFINE;
        m_heuristicPos = 0;
        m_heuristicNeg = 0;
        // m_positives = new LinkedList<Clause>();
        // m_negatives = new LinkedList<Clause>();
    }

    /** Accesseurs */
    public int getId() { return m_id; }

    public Value getValue() { return m_value; }
 
    public int getHeuristicPos() { return m_heuristicPos; }

    public int getHeuristicNeg() { return m_heuristicNeg; }
    
    public int getHeuristic(Value value) {
        switch (value) {
        case TRUE:  
            return m_heuristicPos;
        case FALSE:
            return m_heuristicNeg;
        case UNDEFINE:
            return (m_heuristicPos + m_heuristicNeg) / 2;
        }
        return 0;
    }
    
    /** Mutateurs */
    public void setValue(Value value) { m_value = value; }

    public void setHeuristicPos(int heuristicPos) { m_heuristicPos = heuristicPos; }

    public void setHeuristicNeg(int heuristicNeg) { m_heuristicNeg = heuristicNeg; }

    /** Methodes */
    // public void clearHeuristics() {
    //     m_heuristicPos = m_heuristicNeg = 0;
    //     m_positives.clear();
    //     m_negatives.clear();
    // }
    
    // public void addPositive(Clause clause) { 
    //     m_heuristicPos += 1;
    //     m_heuristicNeg += 0;
    //     m_positives.add(clause); 
    // }

    // public void removePositive(Clause clause) { 
    //     m_heuristicPos -= 1;
    //     m_heuristicNeg -= 0;
    //     m_positives.remove(clause); 
    // }

    // public void addNegative(Clause clause) {
    //     m_heuristicPos += 0;
    //     m_heuristicNeg += 1;
    //     m_negatives.add(clause); 
    // }

    // public void removeNegative(Clause clause) {
    //     m_heuristicPos -= 0;
    //     m_heuristicNeg -= 1;
    //     m_negatives.remove(clause); 
    // }
    
    // public void computeHeuristic() {
    //     Iterator<Clause> iter = null;
    //     m_heuristicNeg = m_heuristicPos = 0;
    //     iter = m_positives.listIterator();
    //     while (iter.hasNext()) {
    //         Clause clause = iter.next();
    //         m_heuristicPos += 1;
    //         m_heuristicNeg += 0;
    //     }
    //     iter = m_negatives.listIterator();
    //     while (iter.hasNext()) {
    //         Clause clause = iter.next();
    //         m_heuristicPos += 0;
    //         m_heuristicNeg += 1;
    //     }
    // }

    public String toString(){
        return new String("(" + m_id  
                          + ", +" + m_heuristicPos
                          + ", -" + m_heuristicNeg 
                          + ", " + m_value + ")"); 
    }
    
}