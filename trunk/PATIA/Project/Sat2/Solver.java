import java.util.Vector;

public class Solver {
    
    /** Attributs */
    private int m_proved;
    private Problem m_problem;
    private Vector<Variable> m_linkVars, m_freeVars;
    private Vector<Clause> m_todo, m_done;

    /** Constructeurs */
    public Solver(Problem problem) {
        m_proved = 0;
        m_problem = problem;
    }

    /** Methodes */
    public void run() {
        m_freeVars = m_problem.getVariables();
        m_todo = m_problem.getClauses();
        m_linkVars = new Vector<Variable>();
        m_done = new Vector<Clause>();
    }

}
