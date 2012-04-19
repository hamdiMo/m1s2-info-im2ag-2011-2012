//dependance sirculaire
import java.util.Scanner;
import java.util.Random;
import java.io.File;

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
       
	m_nbVar = 8;
	m_nbClauses = 20;
	int tailleClause;
	m_tailleClauseMin = 1;
	m_tailleClauseMax = 7;
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

	r = new Random();
	for(int i = 0; i < m_nbClauses; i++){	
	    for(int j = 0; j < 20; j++) System.out.print(" " + (r.nextInt(m_tailleClauseMax+1)+m_tailleClauseMin) % m_tailleClauseMax);
	    tailleClause = (r.nextInt(m_tailleClauseMax+1)+m_tailleClauseMin) % m_tailleClauseMax;
	    
	    clause = new int[tailleClause];
	    for(int j = 0; j<clause.length; j++){
		clause[j] = r2.nextInt(m_nbVar);
	    }
	    int nbVarVraie = 1;
	    for(int m = 0;m < nbVarVraie;m++){
		int solAlea = r.nextInt(m_nbVar);
		int tmp = r.nextInt(tailleClause);
		System.out.println(clause.length + " " + tmp);
		if(solution[solAlea]) clause[tmp] = solAlea;
		else clause[tmp] = -solAlea;
	    }
	    System.out.println("LOOOOOOOOOOOOOL");
	    for(int j = 0; j<clause.length; j++){
		s += clause[j] + " ";
	    }
	    s += "\n";
	}
	System.out.println(s);
    }
}