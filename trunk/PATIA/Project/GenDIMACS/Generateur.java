//dependance sirculaire
import java.util.Scanner;
import java.util.Random;
import java.io.*;
public class Generateur {
 



    public static void main(String [] args) {
	Scanner scanner = new Scanner(System.in);
	// System.out.println("nbVar?");

	// System.out.println("nbClauses?");

	// System.out.println("nbtailleClauseMin?");

	// System.out.println("nbtailleClauseMaxVar?");

	// System.out.println("nbPourcentageVraiParClausesbVar?");

	// System.out.println("sat ou unsat?");
	int m_nbVar;
	int m_nbClauses;
	int m_tailleClauseMin = 1;
	int m_tailleClauseMax = 15;
	int m_PourcentageVraiParClauses = 100;
	boolean m_Sat;
       
	m_nbVar = 80;
	m_nbClauses = 300;
	int tailleClause;
	m_tailleClauseMin = 7;
	m_tailleClauseMax = 30;
	m_PourcentageVraiParClauses = 20;
	int clause[];
	String s = new String();
	Random r = new Random();
	Random r2 = new Random();
	Random r3 = new Random();

	s+="p cnf "+m_nbVar+" "+m_nbClauses+"\n";
	//génération de la solution
	boolean solution[] = new boolean[m_nbVar];
	for(int j = 0; j < m_nbVar; j++) solution[j] = r.nextBoolean();
	//for(int j = 0; j < m_nbVar; j++) System.out.print("("+(j+1)+","+solution[j]+")");
	r = new Random();
	for(int i = 0; i < m_nbClauses; i++){
	    tailleClause = m_tailleClauseMin + r.nextInt(m_tailleClauseMax - m_tailleClauseMin);
	    clause = new int[tailleClause];
	    for(int j = 0; j<clause.length; j++){
		int neg = r.nextInt();
		if((neg%2) == 0) clause[j] = r2.nextInt(m_nbVar)+1;
		else clause[j] = -(r2.nextInt(m_nbVar)+1);
	    }
	    int nbVarVraie = 1;
	    for(int m = 0;m < nbVarVraie;m++){
		int solAlea = r.nextInt(m_nbVar);
		int tmp = r.nextInt(tailleClause);
		if(solution[solAlea]) clause[tmp] = solAlea+1;
		else clause[tmp] = -(solAlea+1);
	    }
	    for(int j = 0; j<clause.length; j++){
		s += clause[j] + " ";
	    }
	    s += "0 \n";
	}
	//	System.out.println(s);

	PrintWriter ecri;
	try {
	    ecri = new PrintWriter(new FileWriter(new File("test2.txt")));
			ecri.print(s);
			ecri.flush();
			ecri.close();
	} catch (IOException exception) {
	    exception.printStackTrace();
	}   	       		 	
    }

}