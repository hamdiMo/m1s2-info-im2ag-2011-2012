import java.util.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.Point;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.awt.Graphics;
import java.awt.Color;

abstract class SubdivisionAlgo {

    protected boolean m_ouvert;

    public SubdivisionAlgo(boolean ouvert) {
	m_ouvert = ouvert;
    }

    public abstract Point calcul_2i_0(int i, Point[] pts);
    public abstract Point calcul_2i_1(int i, Point[] pts);
    public abstract boolean peutCalculer(int i, Point[] pts);

    public Point[] iteration(int n, Point[] pts) {
	if (n > 0) {
	    Point[] tmp = iteration(n-1, pts);
	    Point[] result = new Point[tmp.length * 2];
	    for (int i = 0; i < tmp.length; i++) {
		if (peutCalculer(i, tmp)) {
		    result[2*i] = calcul_2i_0(i, tmp);
		    result[2*i+1] = calcul_2i_1(i, tmp);
		}
		else result[2*i] = result[2*i+1] = null;
	    }
	    return result;
	}
	return pts;
    }
    
    public Point combBar(Point p0, Point p1, double coef) {
        return new Point((int)(p0.getX() * coef + p1.getX() * (1. - coef)), 
                         (int)(p0.getY() * coef + p1.getY() * (1. - coef)));
    }
}

class CornerCutting extends SubdivisionAlgo {

    private double m_a, m_b;

    public CornerCutting(boolean ouvert) {
	super(ouvert);
	Scanner m_scanner = new Scanner(System.in);
        System.out.print("alpha ? "); 
	m_a = m_scanner.nextDouble();
        System.out.print("beta ? "); 
	m_b = m_scanner.nextDouble();
    }

    public CornerCutting(boolean ouvert, double a, double b) {
	super(ouvert);
	m_a = a;
	m_b = b;
    }

    public boolean peutCalculer(int i, Point[] pts) {
	return (!m_ouvert || (i+1 < pts.length)); 
    }

    public Point calcul_2i_0(int i, Point[] pts) {
	return combBar(pts[(i+1)%pts.length], pts[i], m_a);
    }

    public Point calcul_2i_1(int i, Point[] pts) {
	return combBar(pts[(i+1)%pts.length], pts[i], m_b);
    }
}

class Chaikin extends CornerCutting {
    
    public Chaikin(boolean ouvert) { super(ouvert, 1./4., 3./4. ); }

}

class FourPointScheme extends SubdivisionAlgo {

    private double m_eps;

    public FourPointScheme(boolean ouvert) {
	super(ouvert);
	Scanner m_scanner = new Scanner(System.in);
        System.out.print("epsilon ? "); 
	m_eps = m_scanner.nextDouble();
    }

    public FourPointScheme(boolean ouvert, double eps) {
	super(ouvert);
	m_eps = eps;
    }

    public boolean peutCalculer(int i, Point[] pts) {
	return (!m_ouvert) || ((i-1 >= 0) && (i+2 < pts.length)); 
    }

    public Point calcul_2i_0(int i, Point[] pts) {
	return pts[i];
    }

    public Point calcul_2i_1(int i, Point[] pts) {
	Point pA = combBar(pts[(i-1+pts.length)%pts.length], pts[(i+2)%pts.length], 0.5);
	Point pB = combBar(pts[i], pts[(i+1)%pts.length], 0.5);
	return combBar(pA, pB, -m_eps);
    }

}

class Subdivision extends JFrame {

    /** Attributs */
    private int m_nbPoints, m_pointCourant, m_iteration;
    private SubdivisionAlgo m_algo;
    private boolean m_ouvert;
    private Point[] m_points;
    private Graphics m_graphics;

    public Subdivision() {
        super("Subdivision");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JPanel panel = new JPanel();
        panel.setPreferredSize(new Dimension(512, 512));
        getContentPane().add(panel, BorderLayout.CENTER);
        
        Scanner m_scanner = new Scanner(System.in);
	int rep = 0;
        System.out.print("Nombre de point du polygone ? "); m_nbPoints = m_scanner.nextInt();

	System.out.print("Polygone ouvert ? [1 = Non ; 2 = Oui]"); rep = m_scanner.nextInt();
	if (rep == 1) m_ouvert = false;
	else if (rep == 2) m_ouvert = true;
	else System.out.println("Choix Inexistant");

	System.out.print("Methode ? [1 = Chaikin ; 2 = CornerCutting ; 3 = FourPointScheme]");
	rep = m_scanner.nextInt();
	if (rep == 1) m_algo = new Chaikin(m_ouvert);
	else if (rep == 2) m_algo = new CornerCutting(m_ouvert);
	else if (rep == 3) m_algo = new FourPointScheme(m_ouvert);
	else System.out.println("Algo Inexistant");

	m_iteration = 0;
	m_pointCourant = 0;
	m_points = new Point[m_nbPoints];
        	
        panel.addMouseListener(new MouseAdapter() { public void mouseClicked(MouseEvent e) { click(e.getPoint()); } });
        pack();
        setVisible(true);
        m_graphics = panel.getGraphics();
    }

    public void click(Point p) {
	if (m_pointCourant < m_nbPoints) {
            m_points[m_pointCourant] = p;
            m_pointCourant++;
            afficherPoints(p);
        }
	else {
	    m_iteration++;
	    tracerPolygone();
	}
    }
    
    public void tracerPolygone() {
	Point[] polygone = m_algo.iteration(m_iteration, m_points);
	for (int pts = 0; pts < polygone.length; pts++)
	    if (m_ouvert && pts+1 < polygone.length && polygone[pts] != null && polygone[pts+1] != null)
		drawLine(polygone[pts], polygone[pts+1], new Color(255,0,0));
	    else
		drawLine(polygone[pts], polygone[(pts+1)%polygone.length], new Color(255,0,0));
    }
	
    private void afficherPoints(Point p) {
        drawCircle(p, 10);
        if (m_pointCourant > 1) drawLine(m_points[m_pointCourant-2], p, new Color(0,0,0));
        if (!m_ouvert && m_pointCourant == m_nbPoints) drawLine(p, m_points[0], new Color(0,0,0));
    }

    private void drawLine(Point p0, Point p1, Color c) {
        m_graphics.setColor(c);
        m_graphics.drawLine((int)p0.getX(), (int)p0.getY(), (int)p1.getX(), (int)p1.getY());
        m_graphics.setColor(new Color(0,0,0));
    }
    
    private void drawCircle(Point center, int radius) {
        m_graphics.drawOval((int)center.getX() - radius/2,
                            (int)center.getY() - radius/2,
                            radius,
                            radius);
    }

    /** Point d'entrée de l'application */
    public static void main (String [] args) {
        Subdivision app = new Subdivision();
    }

}
