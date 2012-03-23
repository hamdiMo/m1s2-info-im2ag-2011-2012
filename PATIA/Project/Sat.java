
import java.util.Scanner;
import java.util.ArrayList;




public class Sat {

    /** Attributs */
    private int m_nbVars, m_nbClauses;
    private ArrayList<int> m_vars;
    private ArrayList<ArrayList<int>> m_clauses;

    /** Constructeurs */
    public Sat(Scanner scanner) {
	parseHead(scanner.nextLine());
    	while (scanner.hasNextLine())
	    parseClause(scanner.nextLine());
    }

    /** Methodes de parsage */
    public ArrayList<String> parseDeleteSpace(String line) {
	ArrayList<String> result = new ArrayList<String>();
	int indexD = 0;
	while (indexD < line.length()) {
	    while (indexD < line.length() && line.charAt(indexD) == ' ') indexD++;
	    int indexF = indexD+1;
	    while (indexF < line.length() && line.charAt(indexF) != ' ') indexF++;
	    if (indexD < line.length()) result.add(line.substring(indexD, indexF));
	}
	return result;
    }

    public void parseHead(ArrayList<String> line) {
	if (line.length() >= 3 && line.get(0) == "cnf") {
	    m_nbVars = new Integer(line.get(1)).intValue();
	    m_nbClauses = new Integer(line.get(2)).intValue();
	}
    }

    public void parseClause(ArrayList<String> line) {
	ArrayList<int> clause = new ArrayList<int>();
	for (int i = 0; i < line.length(); i++) {
	    clause.add(new Integer(line.get(i).intValue())
	}
	m_clauses.add(clause);
    }
    

    /** Point d'entree du programme */
    public static void main(String [] args) {
	Scanner scanner;
	if (args.length < 1) scanner = new Scanner(System.in);
	else scanner = new Scanner(new File(args[0]));
	Sat sat = new Sat(scanner);
	sat.resolve();
    }




c simple_v3_c2.cnf
cp
cnf 3 2
1 -3 0
2 3 -1 0

}