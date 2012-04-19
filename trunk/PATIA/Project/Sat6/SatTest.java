import java.io.File;

import java.util.Scanner;
import java.util.Random;

public class SatTest {

    public static void main(String [] args) {
        Scanner scanner = new Scanner(System.in);

        int nvarMin = new Integer(args[0]).intValue();
        int nvarMax = new Integer(args[1]).intValue();

        int nclMin = new Integer(args[2]).intValue();
        int nclMax = new Integer(args[3]).intValue();

        for (int nvar = nvarMin; nvar <= nvarMax; nvar += 5) {
            for (int ncl = nclMin; ncl <= nclMax; ncl += 20) {
                Random rand = new Random();
                double instances = 0, conflicts = 0, heightMax = 0, learntClauses = 0;
                for (int smooth = 0; smooth < 10; smooth++) {
                    Problem problem = new Problem(nvar, ncl);
                    
                    Solver solver = new Solver();
                    boolean sat = solver.solve(problem);

                    instances += solver.getInstances();
                    conflicts += solver.getConflicts();
                    heightMax += solver.getHeigthMax();
                    learntClauses += solver.getLearntClauses();
                }
                
                System.out.println(nvar + " " + ncl + " "
                                   + (instances / 5) + " "
                                   + (conflicts / 5) + " "
                                   + (heightMax / 5) + " "
                                   + (learntClauses / 5));

                
            }
            System.out.println("");
        }
    }
}