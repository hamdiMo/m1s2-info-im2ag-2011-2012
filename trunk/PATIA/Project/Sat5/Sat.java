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
        System.out.println(problem);

        Solver solver = new Solver(problem);
        if (solver.solve()) {
            System.out.println("SAT");
            System.out.println(solver);
        }
        else System.out.println("UNSAT");
 
        System.out.println("Statistics : ");
        System.out.println("Instances = " + solver.getInstances());
        System.out.println("Conflicts = " + solver.getConflicts());
        System.out.println("Backtrack = " + solver.getBacktrack());
        System.out.println("Heightmax = " + solver.getHeigthMax());
        System.out.println("Iteration = " + solver.getIteration());
    }
}