import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;

public class Variable {

    /** Attributs */
    private int m_id;
    private Value m_value;
    private int m_heuristicPos, m_heuristicNeg;
    
    /** Constructeurs */
    public Variable(int id) {
        m_id = id;
        m_value = Value.UNDEFINE;
        m_heuristicPos = 0;
        m_heuristicNeg = 0;
    }

    /** Accesseurs */
    public int getId() { return m_id; }

    public Value getValue() { return m_value; }
 
    public int getHeuristicPos() { return m_heuristicPos; }

    public int getHeuristicNeg() { return m_heuristicNeg; }
    
    // public int getHeuristic(Value value) {
    //     switch (value) {
    //     case TRUE:  
    //         return m_heuristicPos;
    //     case FALSE:
    //         return m_heuristicNeg;
    //     case UNDEFINE:
    //         return (m_heuristicPos + m_heuristicNeg) / 2;
    //     }
    //     return 0;
    // }
    
    /** Mutateurs */
    public void setValue(Value value) { m_value = value; }

    public void setHeuristicPos(int heuristicPos) { m_heuristicPos = heuristicPos; }

    public void setHeuristicNeg(int heuristicNeg) { m_heuristicNeg = heuristicNeg; }

    /** Methodes */
    public String toString() {
        return new String("(" + m_id  
                          + ", +" + m_heuristicPos
                          + ", -" + m_heuristicNeg 
                          + ", " + m_value + ")"); 
    }
    
}