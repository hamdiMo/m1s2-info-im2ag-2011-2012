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
        
        ProblemSolver problemSolver = new ProblemSolver(scanner);
        System.out.println(problemSolver);
        problemSolver.solve();
        System.out.println(problemSolver);
    }
}