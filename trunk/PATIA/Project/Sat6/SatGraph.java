import java.io.File;

public class SatGraph {

    public static void main(String [] args) {
        int nvar = new Integer(args[0]).intValue();
        int ncl = new Integer(args[1]).intValue();
        File output = new File(args[2]);

        Problem problem = new Problem(nvar, ncl);
        System.out.println(problem);
        
        Solver solver = new Solver(output);
        boolean sat = solver.solve(problem);
        
        System.out.println(solver);
                
        if (sat) {
            System.out.print("SAT");
            for (int i = 0; i < problem.getVariableDimension(); i++) {
                Variable variable = problem.getVariable(i);
                if (variable.isValue(true)) System.out.print(" " + variable.getId());
                else if (variable.isValue(false)) System.out.print(" -" + variable.getId());
            }
            System.out.println("");
        }
        else System.out.println("UNSAT");
        
    }
}