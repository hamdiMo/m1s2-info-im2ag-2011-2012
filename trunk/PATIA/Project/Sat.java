import java.util.Scanner;
import java.util.Vector;
import java.util.ArrayList;
import java.io.File;



public class Sat {

    /** Attributs */
    private int m_nbVariables, m_nbClauses, m_nbProved;
    private Vector<Variable> m_vars;
    private Vector<Vector<Integer>> m_clauses;

    /** Constructeurs */
    public Sat(Scanner scanner) {
        while (scanner.hasNextLine() && !parseHead(parseClean(scanner.nextLine())));
        m_vars = new Vector<Variable>(m_nbVariables);
        for (int i = 0; i < m_nbVariables; i++) m_vars.add(i, new Variable(i+1));
        m_clauses = new Vector<Vector<Integer>>(m_nbClauses);
        int index = 0;
    	while (index < m_nbClauses && scanner.hasNextLine())
            if (parseClause(index, parseClean(scanner.nextLine()))) index++;
    }

    /** Methodes de resolution */
    public void resolve() {
        m_nbProved = 0;

        init();
        System.out.println(toString());

        // trie des clauses par leur taille (nombre de variables non instanciees)
        for (int i = m_nbProved; i < m_clauses.size()-1; i++) {
            int min = i, minSize = sizeClause(m_clauses.get(i));
            for (int j = i+1; j < m_clauses.size(); j++) {
                int size = sizeClause(m_clauses.get(j));
                if (size < minSize) { minSize = size; min = j; }
            }
            if (i != min) {
                Vector<Integer> clauseTmp = m_clauses.get(i);
                m_clauses.set(i, m_clauses.get(min));
                m_clauses.set(min, clauseTmp);
            }
        }

        // choix de la premiere clause
        heuristic(getCleanClause(m_nbProved));
        int idMax = 0, max = m_vars.get(0).m_heur;
        for (int i = 0; i < m_vars.size(); i++) {
            if (max < m_vars.get(i).m_heur) {
                max = m_vars.get(i).m_heur;
                idMax = i;
            } else if (max == m_vars.get(i).m_heur) {
                int s1 = m_vars.get(idMax).m_nbPos + m_vars.get(idMax).m_nbNeg;
                int s2 = m_vars.get(i).m_nbPos + m_vars.get(i).m_nbNeg;
                if (s1 < s2) {
                    max = m_vars.get(i).m_heur;
                    idMax = i;
                }
            }
        }

        // dans le cas ou une variable possede la meme  heuristique pour 2 valeurs,
        // il faut compter la somme du nombre de variables dans chacunes des clauses
        // puis prendre la valeur pour laquelle la somme est la plus grande

        // propagation de la contrainte
        m_vars.get(idMax).m_val = m_vars.get(idMax).m_heurVal;
        for (int i = m_nbProved; i < m_clauses.size()-1; i++) {}
        
        System.out.println(toString());
        System.out.println("Choix : " + m_vars.get(idMax) + " val = " +  m_vars.get(idMax).m_heurVal);
    }

    public void init() {
        for (int i = 0; i < m_nbVariables; i++) m_vars.get(i).init();
        for (int i = m_nbProved; i < m_nbClauses; i++) {
            Vector<Integer> clause = getCleanClause(i);
            for (int j = 0; j < clause.size(); j++) {
                int idVariable = clause.get(j).intValue();
                if (idVariable < 0) {
                    idVariable = -idVariable;
                    m_vars.get(idVariable-1).m_nbNeg++;
                }
                else m_vars.get(idVariable-1).m_nbPos++;
            }
        }
    }

    public void heuristic(Vector<Integer> clause) {
        for (int i = 0; i < clause.size(); i++) {	
            int id = clause.get(i).intValue(), heur = 0, val = 0;
            Variable var = getVariable(id);
            if (id > 0 && var.m_heur < var.m_nbPos) { var.m_heurVal = 1; var.m_heur = var.m_nbPos; }
            else if (id < 0 && var.m_heur < var.m_nbNeg) { var.m_heurVal = -1; var.m_heur = var.m_nbNeg; }
        }
    }

    public Variable getVariable(int id) {
        if (id < 0) id = -id;
        return m_vars.get(id-1);
    }

    public Vector<Integer> getClause(int index) { return m_clauses.get(index); }

    public Vector<Integer> getCleanClause(int index) {
        int j = 0;
        Vector<Integer> clauseRef = getClause(index);
        Vector<Integer> clause = new Vector<Integer>();
        for (int i = 0; i < clauseRef.size(); i++) {
            Variable v = getVariable(clauseRef.get(i).intValue());
            if (v.m_val == 0) {
                clause.add(j, clauseRef.get(i));
                j++;
            }
        }
        return clause;
    }

    public int sizeClause(Vector<Integer> clause) {
        int size = 0;
        for (int i = 0; i < clause.size(); i++)
            if (getVariable(clause.get(i).intValue()).m_val == 0) size++;
        return size;
    }

    /** Methodes de parsage */
    public ArrayList<String> parseClean(String line) {
        ArrayList<String> result = new ArrayList<String>();
        int indexD = 0;
        while (indexD < line.length()) {
            while (indexD < line.length() && (line.charAt(indexD) == ' ' || line.charAt(indexD) == '\t')) indexD++;
            if (indexD < line.length()) {
                if (!(line.charAt(indexD) == 'c' && (indexD+1 >= line.length() || line.charAt(indexD+1) == ' ' || line.charAt(indexD+1) == '\t'))) {
                    int indexF = indexD+1;
                    while (indexF < line.length() && (line.charAt(indexF) != ' ' && line.charAt(indexD) != '\t')) indexF++;
                    result.add(line.substring(indexD, indexF));
                    indexD = indexF;
                }
                else indexD = line.length();
            }
        }
        return result;
    }

    public boolean parseHead(ArrayList<String> line) {
        if (line.size() >= 3 && line.get(0).equals("cnf")) {
            m_nbVariables = new Integer(line.get(1)).intValue();
            m_nbClauses = new Integer(line.get(2)).intValue();
            return true;
        }
        return false;
    }

    public boolean parseClause(int index, ArrayList<String> line) {
        Vector<Integer> clause = new Vector<Integer>();
        for (int i = 0; i < line.size(); i++) {
            if (i == line.size()-1 && line.get(i).equals("0")) m_clauses.add(index, clause);
            else clause.add(i, new Integer(line.get(i)));
        }
        return true;
    }

    /** Methodes de sortie */
    public String toString() {
        String res = "Variables = {\n";
        for (int i = 0; i < m_nbVariables; i++) res += "\t" + m_vars.get(i).toString() + "\n";
        res += "}\nClauses = {\n";
        for (int i = 0; i < m_nbClauses; i++) {
            res += "\t";
            Vector<Integer> clause = m_clauses.get(i);
            for (int j = 0; j < clause.size(); j++) {
                int idVariable = clause.get(j).intValue();
                if (idVariable < 0) { idVariable = -idVariable; res += "not"; }
                res += m_vars.get(idVariable-1) + " ";
            }
            res += "\n";
        }
        res += "}";
        return res;
    }
    
    /** Point d'entree du programme */
    public static void main(String [] args) {
        Scanner scanner;
        if (args.length < 1) scanner = new Scanner(System.in);
        else {
            try {
                scanner = new Scanner(new File(args[0]));
            } catch (java.io.FileNotFoundException e) {
                System.out.println("Le fichier n'existe pas !");
                scanner = new Scanner(System.in);
            }
        }
        Sat sat = new Sat(scanner);
        sat.resolve();
    }
}

class Clause {
    public int m_id, m_sizeIni, m_size, m_value;
    public Vector<Integer> m_exprIni, m_expr;
    public Clause() {}
}

class Variable {
    public int m_id, m_val;
    public int m_nbPos, m_nbNeg; 
    public int m_heur, m_heurVal;
    
    public Variable(int id){
        m_id = id;
        init();
    }
    
    public String toString(){
        return new String("(" + m_id + ", " + m_val + ", +" + m_nbPos + ", -" + m_nbNeg + ", h" + m_heur + ")"); 
    }
    
    public void init() {
        m_nbPos = 0;
        m_nbNeg = 0;
        m_val = 0;
        m_heurVal = 0;
        m_heur = 0;
    }
}
