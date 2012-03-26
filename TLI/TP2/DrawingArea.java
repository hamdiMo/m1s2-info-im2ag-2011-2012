import javax.swing.*;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Dimension;
import java.awt.Point;

import java.awt.event.*;

import java.util.Vector;
import java.awt.geom.Path2D;
import java.awt.geom.PathIterator;


public class DrawingArea extends JPanel implements MouseListener, MouseMotionListener {

    /** Type interne */
    private enum State { NEW_LINE, ADD, MOVE };

    /** Attributs */
    private State m_state;
    private Path2D m_curPath;
    private Vector<Path2D> m_path;
    private Point m_p0, m_p1, m_p2, m_p3;

    /** Constructeurs */
    public DrawingArea() {
	setPreferredSize(new Dimension(512, 512));
	m_state = State.NEW_LINE;
	m_curPath = null;
	m_path = new Vector<Path2D>();
	
	addKeyListener(new KeyAdapter() {
		public void keyPressed(KeyEvent e) {
		    newLine();
		}
	    });

	addMouseListener(this);
	addMouseMotionListener(this);
    }

    /** Methodes */
    public void clear() {
	m_path.clear();
	repaint();
    }

    public void newLine() {
	m_p0 = m_p1 = m_p2 = m_p3 = null;
	m_state = State.NEW_LINE;
    }

    public void addPoint(Point p) {
	if (m_p0 == null) m_curPath.moveTo(p.getX(), p.getY());
	else if (m_p1 == null) m_curPath.lineTo(p.getX(), p.getY());
	else m_curPath.quadTo(m_p1.getX(), m_p1.getY(), p.getX(), p.getY());
	m_p0 = p;
	m_p1 = null;
	repaint();
    }
    
    public void addPoint(Point p, Point t) {
	if (m_p0 == null) m_curPath.moveTo(p.getX(), p.getY());
	else if (m_p1 == null) m_curPath.quadTo(m_p1.getX(), m_p1.getY(), p.getX(), p.getY());
	else m_curPath.curveTo(m_p1.getX(), m_p1.getY(), p.getX(), p.getY(), t.getX(), t.getY());
	m_p0 = p;
	m_p1 = t;
	repaint();
    }

    public void paintComponent(Graphics g) {
	int size2 = 5;
	Graphics2D g2d = (Graphics2D)g;
	for (int i = 0; i < m_path.size(); i++) {
	    if (i == m_path.size() - 1) g.setColor(new Color(255,0,0));
	    Path2D path = m_path.get(i);
	    PathIterator pathIter = path.getPathIterator(null);
	    while (!pathIter.isDone()) {
		double[] dots = new double[6];
		switch (pathIter.currentSegment(dots)) {
		case PathIterator.SEG_MOVETO:
		    g.drawRect((int)dots[0] - size2, (int)dots[1] - size2, 2 * size2, 2 * size2);
		    break;
		case PathIterator.SEG_LINETO:
		    g.drawRect((int)dots[0] - size2, (int)dots[1] - size2, 2 * size2, 2 * size2);
		    break;
		case PathIterator.SEG_CUBICTO:
		    g.drawRect((int)dots[2] - size2, (int)dots[3] - size2, 2 * size2, 2 * size2);
		    break;
		case PathIterator.SEG_QUADTO:
		    g.drawRect((int)dots[4] - size2, (int)dots[5] - size2, 2 * size2, 2 * size2);
		    break;
		}
		pathIter.next();
	    }
	    g2d.draw(path);
	    g.setColor(new Color(0,0,0));
	}
    }
    
    public void mouseClicked(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
    
    public void mousePressed(MouseEvent e) { 
	m_p3 = e.getPoint();
    }

    public void mouseReleased(MouseEvent e) {
	if (m_p3 != null) {
	    Point pTmp = e.getPoint();
	    switch (m_state) {
	    case NEW_LINE:
		m_curPath = new Path2D.Double();
		m_path.add(m_curPath);
		if (pTmp.equals(m_p3)) addPoint(m_p3);
		else addPoint(m_p3, pTmp);
		m_state = State.ADD;
		break;
	    case ADD:
		if (pTmp.equals(m_p3)) addPoint(m_p3);
		else addPoint(m_p3, pTmp);
		break;
	    case MOVE:
		throw new RuntimeException();
	    }
	}
    }
    
    public void mouseDragged(MouseEvent e) {}
    public void mouseMoved(MouseEvent e) {}
}