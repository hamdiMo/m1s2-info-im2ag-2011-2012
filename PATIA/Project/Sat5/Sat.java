import java.io.File;

import java.util.Scanner;


public class Sat {

    public static void main(String [] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length >= 1)
            try {
                scanner = new Scanner(new File(args[0]));
            } catch (java.io.FileNotFoundException e) {
                System.out.println("Error : File " + args[0] + " does not exist");
                throw new RuntimeException();
            }
        
        Problem problem = new Problem(scanner);
        System.out.println(problem + "\n");

        Solver solver = new Solver();
        boolean sat = solver.solve(problem);

        System.out.println(problem + "\n");        
        System.out.println("\n" + solver);

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