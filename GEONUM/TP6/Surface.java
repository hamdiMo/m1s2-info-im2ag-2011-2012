import java.io.File;
import java.util.Scanner;

abstract class Algorithm {
    public Algorithm() {}
}

class Vector3d {
    public double m_x, m_y, m_z;
    public Vector3d(double x, double y, double z) {
	m_x = x;
	m_y = y;
	m_z = z;
    }
    public Vector3d(Scanner scanner) {
	m_x = scanner.nextDouble();
	m_y = scanner.nextDouble();
	m_z = scanner.nextDouble();
    }
    public String toString() {
	return new String("" + m_x + " " + m_y + " " + m_z);
    }
    public Vector3d combBar(Vector3d vector, double coef) {
	return new Vector3d(m_x * coef + vector.m_x * (1. - coef),
			    m_y * coef + vector.m_y * (1. - coef),
			    m_z * coef + vector.m_z * (1. - coef));
    } 
}

class Surface {

    /** Attributs */
    private int m_sizeX, m_sizeY;
    private Vector3d[][] m_map;
    private boolean m_closeX, m_closeY;

    /** Constructeurs */
    public Surface(Scanner scanner) {
	m_sizeX = scanner.nextInt();
	m_sizeY = scanner.nextInt();

	m_closeX = scanner.nextBoolean();
	m_closeY = scanner.nextBoolean();

	m_map = new Vector3d[m_sizeX][m_sizeY];
	for (int i = 0; i < m_sizeX; i++)
	    for (int j = 0; j < m_sizeY; j++)
		m_map[i][j] = new Vector3d(scanner);
    }

    public void transposer() {
	Vector3d[][] copie = new Vector3d[m_sizeY][m_sizeX];
	for (int i = 0; i < m_sizeX; i++)
	    for (int j = 0; j < m_sizeY; j++)
		copie[j][i] = m_map[i][j];
	int newX = m_sizeY, newY = m_sizeX;
	m_map = copie;
	m_sizeX = newX;
	m_sizeY = newY;
    }

    public Vector3d bezierLigne(Vector3d[] line, double coef) {
	if (line.length > 1) {
	    Vector3d[] lineBis = new Vector3d[line.length-1];
	    for (int i = 0; i < lineBis.length; i++)
		lineBis[i] = line[i].combBar(line[i+1], coef);
	    return bezierLigne(lineBis, coef);
	}
	return line[0];
    }

    public Vector3d bezierLigneFerme(Vector3d[] line, double coef) {
	Vector3d[] closeLine = new Vector3d[line.length+1];
	for (int i = 0; i < line.length; i++) closeLine[i] = line[i];
	closeLine[line.length] = line[0];
	return bezierLigne(closeLine, coef);
    }

    public void algoBezier(int newSizeX, int newSizeY) {
	Vector3d[][] surfaceBezier = new Vector3d[m_sizeX][newSizeY];
	for (int i = 0; i < newSizeY; i ++) {
	    double t = (double)i / (double)(newSizeY-1);
	    for (int j = 0; j < m_sizeX; j++)
		if (m_closeX) surfaceBezier[j][i] = bezierLigneFerme(m_map[j], t);
		else surfaceBezier[j][i] = bezierLigne(m_map[j], t);
	}
	m_map = surfaceBezier;
	m_sizeY = newSizeY;

	transposer();

	surfaceBezier = new Vector3d[m_sizeX][newSizeX];
	for (int i = 0; i < newSizeX; i ++) {
	    double t = (double)i / (double)(newSizeX-1);
	    for (int j = 0; j < m_sizeX; j++)
		if (m_closeY) surfaceBezier[j][i] = bezierLigneFerme(m_map[j], t);
		else surfaceBezier[j][i] = bezierLigne(m_map[j], t);
	}
	m_map = surfaceBezier;
	m_sizeY = newSizeX;

	transposer();
    }

    public String toString() {
	String res = "";
	for (int i = 0; i < m_sizeX; i++) {
	    for (int j = 0; j < m_sizeY; j++)
		res += m_map[i][j] + "\n";
	    res += "\n";
	}
	return res;
    }

    /** Point d'entrée de l'application */
    public static void main (String [] args) {
	Scanner scanner = null;
	if (args.length > 0) {
	    try { scanner = new Scanner(new File(args[0])); } 
	    catch (java.io.FileNotFoundException e) {
		System.out.println("Error : File not exist !"); 
	    }
	}
	Surface surface = new Surface(scanner);
	int precisionX = scanner.nextInt();
	int precisionY = scanner.nextInt();
	surface.algoBezier(precisionX, precisionY);
	System.out.println(surface);
    }

}
