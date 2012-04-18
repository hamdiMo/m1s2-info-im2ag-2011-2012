

public class Heuristics {
    
    Solver m_solver;
    Problem m_problem;
    Clause[] m_clause;
    Variable[] m_variables;

    public Heuristics(Problem problem, Solver solver) {
        m_problem = problem;
        m_solver = solver;
        m_clause = m_solver.getClauses();
        m_variables = m_solver.getVariables();
    }

    static public void updateHeuristics(Variable[] variables, Clause[] clauses, int var, int cl) {
        for (int i = var; i < variables.length; i++) {
            variables[i].setHeuristicPos(0);
            variables[i].setHeuristicNeg(0);
        }

        for (int i = cl; i < clauses.length; i++) {
            Clause clause = clauses[i];
            for (int j = 0; j < clause.getSize(); j++) {
                Integer literal = clause.getLiteral(j);
                if (literal.intValue() < 0)
                    m_problem.getVariableFromLiteral(literal).addNegative(clause);
                else m_problem.getVariableFromLiteral(literal).addPositive(clause);
            }
        }
    } 
    
    static public double computeHeuristic(Clause clause) {
        int heuristic = 0;
        for (int i = 0; i < m_size; i++) {
            Integer literal = m_expr[i];
            int exprVar = literal.intValue();
            int heurTmp = 0;
            if (exprVar > 0) heurTmp = m_problem.getVariableFromLiteral(literal).getHeuristicPos();
            else heurTmp = m_problem.getVariableFromLiteral(literal).getHeuristicNeg();
            if (heurTmp < heuristic) heuristic = heurTmp;
        }
        return (double)heuristic; // / (double)m_size;
    }

    static public int computeHeuristic(Variable variable) {
    }

}