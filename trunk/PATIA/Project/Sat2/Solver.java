import java.util.Vector;

public class Solver {
    
    /** Attributs */
    private Problem m_problem;
    private Vector<Clause> m_clauses;
    private Vector<Variable> m_variables;
    
    /** Constructeurs */
    public Solver(Problem problem) {
        m_proved = 0;
        m_problem = problem;
    }

    /** Methodes */
    public void run() { solve(); }

    public boolean solve() {
        m_clauses = m_problem.getClauses();
        m_variables = m_problem.getVariables();
        return solve(0);
    }

    public boolean solve(int i) {
        int j = i;
        sortClauseByBestMinimal();
        if (clause.isUnitary()) {
            Variable variable = clause.computeValidClauseFrom(0);
            Iterator<Clause> iter = m_unprovedClauses.listIterator();
            while (iter.hasNext()) {
                Clause clause = iter.next();
                clause.computePropagation(variable, j);
            }
            j++;
        }
    }
    
    public void sortClauseByBestMinimal() {
        throw new RuntimeException();
    }


}
