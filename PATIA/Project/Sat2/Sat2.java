import java.io.File;

import java.util.Scanner;


public class Sat2 {

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
        solver.run();

        System.out.println(problem);
    }
}