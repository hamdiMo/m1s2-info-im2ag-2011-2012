import javax.swing.*;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Dimension;
import java.awt.Point;

import java.awt.event.*;

import java.util.Vector;
import java.awt.geom.Path2D;
import java.awt.geom.QuadCurve2D;
import java.awt.geom.CubicCurve2D;
import java.awt.geom.PathIterator;


public class DrawingArea extends JPanel implements MouseListener, MouseMotionListener {

    /** Type interne */
    private enum State {
	INIT {
	    public State mousePressed(MouseEvent e) {
		m_p0 = m_drawingArea.getPointFromClick(e.getPoint());
		if (m_p0 == null) {
		    m_p0 = e.getPoint();
		    m_drawingArea.setPivot(m_p0);
		    m_drawingArea.setTan(m_p0);
		    return ADD;
		} 
		else {
		    if (!m_drawingArea.isTan(m_p0)) m_drawingArea.select(m_p0);
		}
		return SELECT;
	    }
	}, ADD {
	    public State mouseReleased(MouseEvent e) {
		m_drawingArea.addPoint(m_p0);
		return INIT;
	    }
	    public State mouseDragged(MouseEvent e) {
		m_p1 = e.getPoint();
		m_drawingArea.setTan(m_p1);
		return ADD_TAN;
	    }
	}, ADD_TAN {
	    public State mouseReleased(MouseEvent e) {
		m_drawingArea.addPoint(m_p0, m_p1);
		return INIT;
	    }
	    public State mouseDragged(MouseEvent e) {
		m_p1 = e.getPoint();
		m_drawingArea.setTan(m_p1);
		return ADD_TAN;
	    }
	}, SELECT {
	    public State mouseReleased(MouseEvent e) {
		return INIT;
	    }
	    public State mouseDragged(MouseEvent e) {
		m_p1 = e.getPoint();
		m_drawingArea.move(m_p0, m_p1);
		m_p0 = m_p1;
		if (!m_drawingArea.isTan(m_p0)) m_drawingArea.select(m_p0);
		return SELECT;
	    }
	};
	// , MOVE {
	//     public State mouseReleased(MouseEvent e) {
	// 	m_drawingArea.move(m_p0, m_p1);
	// 	if (!m_drawingArea.isTan(m_p1)) m_drawingArea.select(m_p1);
	// 	return INIT;
	//     }
	//     public State mouseDragged(MouseEvent e) {
	// 	m_p1 = e.getPoint();
	// 	return MOVE;
	//     }
	// };
	static public State InitState(DrawingArea drawingArea) {
	    m_drawingArea = drawingArea;
	    return INIT;
	}
	public State mousePressed(MouseEvent e) { throw new RuntimeException(); }
	public State mouseReleased(MouseEvent e) { throw new RuntimeException(); }
	public State mouseDragged(MouseEvent e) { throw new RuntimeException(); }

	static DrawingArea m_drawingArea;
	static Point m_p0, m_p1;
    };

    /** Attributs */
    private State m_state;
    private Path2D m_curPath;
    private Vector<Path2D> m_path;
    private Point m_p0, m_p1, m_p2, m_p3, m_p4, m_curPoint;
    private int m_size2;

    /** Constructeurs */
    public DrawingArea() {
        setPreferredSize(new Dimension(512, 512));
        m_curPath = null;
        m_path = new Vector<Path2D>();
	m_state = State.InitState(this);

        newLine();

	m_size2 = 10;

        addMouseListener(this);
        addMouseMotionListener(this);
    }
    
    /** Predicats */
    public boolean isTan(Point p) { return false; }

    public boolean isSelected(Point p) { return isSelected(p.getX(), p.getY()); }

    public boolean isSelected(double x, double y) {
	return m_curPoint != null && m_curPoint.getX() == x && m_curPoint.getY() == y;
    }
    
    public boolean isClick(Point p, Point cur) {
	return isClick(p.getX(), p.getY(), cur);
    }

    public boolean isClick(double x, double y, Point cur) {
	return x - m_size2 <= cur.getX() && cur.getX() <= x + m_size2 && y - m_size2 <= cur.getY() && cur.getY() <= y + m_size2;
    }

    /** Mutateurs */
    public void setPivot(Point p) {
	m_p3 = p; 
	repaint();
    }
    
    public void setTan(Point p) {
	m_p4 = p; 
	repaint();
    }

    /** Methodes */
    public Point getPointFromClick(Point p) {
	Point res = null;
	PathIterator pathIter = m_curPath.getPathIterator(null);
        while (res == null && !pathIter.isDone()) {
            double[] dots = new double[6];
            switch (pathIter.currentSegment(dots)) {
            case PathIterator.SEG_MOVETO:
                if (isClick(dots[0], dots[1], p)) res = new Point((int)dots[0], (int)dots[1]);
		pathIter.next();
                break;
            case PathIterator.SEG_LINETO:
		if (isClick(dots[0], dots[1], p)) res = new Point((int)dots[0], (int)dots[1]);
		pathIter.next();
		break;
            case PathIterator.SEG_QUADTO:
		if (isClick(dots[2], dots[3], p)) res = new Point((int)dots[2], (int)dots[3]);
		if (isSelected(dots[2], dots[3])) {
		    if (isClick(dots[0], dots[1], p)) res = new Point((int)dots[0], (int)dots[1]);
		    pathIter.next();
		    if (!pathIter.isDone()) {
			switch (pathIter.currentSegment(dots)) {
			case PathIterator.SEG_QUADTO:
			    if (isClick(dots[0], dots[1], p)) res = new Point((int)dots[0], (int)dots[1]);
			    break;
			case PathIterator.SEG_CUBICTO:
			    if (isClick(dots[0], dots[1], p)) res = new Point((int)dots[0], (int)dots[1]);
			    break;
			default:
			}
		    }
		}
		else pathIter.next();
                break;
            case PathIterator.SEG_CUBICTO:
                if (isClick(dots[4], dots[5], p)) res = new Point((int)dots[4], (int)dots[5]);
		if (isSelected(dots[4], dots[5])) {
		    if (isClick(dots[2], dots[3], p)) res = new Point((int)dots[0], (int)dots[1]);
		    pathIter.next();
		    if (!pathIter.isDone()) {
			switch (pathIter.currentSegment(dots)) {
			case PathIterator.SEG_QUADTO:
			    if (isClick(dots[0], dots[1], p)) res = new Point((int)dots[0], (int)dots[1]);
			    break;
			case PathIterator.SEG_CUBICTO:
			    if (isClick(dots[0], dots[1], p)) res = new Point((int)dots[0], (int)dots[1]);
			    break;
			default:
			}
		    }
		}
		else pathIter.next();
                break;
            default:
                break;
            }
        }
	return res;
    }
    
    public void move(Point p0, Point p1) {
	Path2D copy = new Path2D.Double();
	PathIterator pathIter = m_curPath.getPathIterator(null);
        while (!pathIter.isDone()) {
            double[] dots = new double[6];
            switch (pathIter.currentSegment(dots)) {
            case PathIterator.SEG_MOVETO:
                if (p0.equals(new Point((int)dots[0], (int)dots[1]))) {
		    dots[0] = p1.getX();
		    dots[1] = p1.getY();
		}
		copy.moveTo(dots[0], dots[1]);
                break;
            case PathIterator.SEG_LINETO:
                if (p0.equals(new Point((int)dots[0], (int)dots[1]))) {
		    dots[0] = p1.getX();
		    dots[1] = p1.getY();
		}
		copy.lineTo(dots[0], dots[1]);
		break;
            case PathIterator.SEG_QUADTO:
                if (p0.equals(new Point((int)dots[0], (int)dots[1]))) {
		    dots[0] = p1.getX();
		    dots[1] = p1.getY();
		}
                else if (p0.equals(new Point((int)dots[2], (int)dots[3]))) {
		    dots[2] = p1.getX();
		    dots[3] = p1.getY();
		}
		copy.quadTo(dots[0], dots[1], dots[2], dots[3]);
                break;
            case PathIterator.SEG_CUBICTO:
                if (p0.equals(new Point((int)dots[0], (int)dots[1]))) {
		    dots[0] = p1.getX();
		    dots[1] = p1.getY();
		}
                else if (p0.equals(new Point((int)dots[2], (int)dots[3]))) {
		    dots[2] = p1.getX();
		    dots[3] = p1.getY();
		}
                else if (p0.equals(new Point((int)dots[4], (int)dots[5]))) {
		    dots[4] = p1.getX();
		    dots[5] = p1.getY();
		}
		copy.curveTo(dots[0], dots[1], dots[2], dots[3], dots[4], dots[5]);
                break;
            default:
                break;
            }
	    pathIter.next();
        }
	m_curPath = copy;
	m_path.set(m_path.size()-1, copy); // bemol
	repaint();
    }

    public void select(Point point) {
	m_curPoint = point;
	repaint();
    }

    public void clear() {
        m_path.clear();
	newLine();
        repaint();
    }

    public void newLine() {
        m_p0 = m_p1 = m_p2 = m_p3 = m_p4 = null;
        m_curPath = new Path2D.Double();
        m_path.add(m_curPath);
	repaint();
    }

    public void addPoint(Point p) {
        if (m_p0 == null) m_curPath.moveTo(p.getX(), p.getY());
        else if (m_p1 == null) m_curPath.lineTo(p.getX(), p.getY());
        else m_curPath.quadTo(m_p1.getX(), m_p1.getY(), p.getX(), p.getY());
        m_p0 = p;
        m_p1 = null;
	m_p3 = null;
	m_p4 = null;
	select(p);
        repaint();
    }
    
    public void addPoint(Point p, Point t) {
        if (m_p0 == null) m_curPath.moveTo(p.getX(), p.getY());
        else if (m_p1 == null) m_curPath.quadTo(2*p.getX() - t.getX(), 2*p.getY() - t.getY(),
                                                p.getX(), p.getY());
        else m_curPath.curveTo(m_p1.getX(), m_p1.getY(),
                               2*p.getX() - t.getX(), 2*p.getY() - t.getY(),
                               p.getX(), p.getY());
        m_p0 = p;
        m_p1 = t;
	m_p3 = null;
	m_p4 = null;
	select(p);
        repaint();
    }

    public void paintComponent(Graphics g) {
	Graphics2D g2d = (Graphics2D)g;

        g.setColor(new Color(255,255,255));
        g.fillRect(0, 0, getWidth(), getHeight());
        g.setColor(new Color(0, 0, 0));

        for (int i = 0; i < m_path.size(); i++) {
            if (i == m_path.size() - 1) g.setColor(new Color(255,0,0));
            Path2D path = m_path.get(i);
            PathIterator pathIter = path.getPathIterator(null);
            while (!pathIter.isDone()) {
                double[] dots = new double[6];
                switch (pathIter.currentSegment(dots)) {
                case PathIterator.SEG_MOVETO:
		    if (isSelected(dots[0], dots[1])) {
			g.fillRect((int)dots[0] - m_size2, (int)dots[1] - m_size2, 2 * m_size2, 2 * m_size2);
			pathIter.next();
			if (!pathIter.isDone()) {
			    switch (pathIter.currentSegment(dots)) {
			    case PathIterator.SEG_QUADTO:
				break;
			    case PathIterator.SEG_CUBICTO:
				break;
			    default:
			    }
			}
		    }
		    else {
			g.drawRect((int)dots[0] - m_size2, (int)dots[1] - m_size2, 2 * m_size2, 2 * m_size2);
			pathIter.next();
		    }
		    break;
                case PathIterator.SEG_LINETO:
		    if (isSelected(dots[0], dots[1])) {
			g.fillRect((int)dots[0] - m_size2, (int)dots[1] - m_size2, 2 * m_size2, 2 * m_size2);
			pathIter.next();
		    }
		    else {
			g.drawRect((int)dots[0] - m_size2, (int)dots[1] - m_size2, 2 * m_size2, 2 * m_size2);
			pathIter.next();
		    }
                    break;
                case PathIterator.SEG_QUADTO:
		    if (isSelected(dots[2], dots[3])) {
			g.fillRect((int)dots[2] - m_size2, (int)dots[3] - m_size2, 2 * m_size2, 2 * m_size2);
			Point p0 = new Point((int)dots[0], (int)dots[1]), p1 = null;
			pathIter.next();
			if (!pathIter.isDone()) {
			    switch (pathIter.currentSegment(dots)) {
			    case PathIterator.SEG_QUADTO:
				p1 = new Point((int)dots[0], (int)dots[1]);
				break;
			    case PathIterator.SEG_CUBICTO:
				p1 = new Point((int)dots[0], (int)dots[1]);
				break;
			    default:
			    }
			}
			g.drawRect((int)p0.getX() - m_size2, (int)p0.getY() - m_size2, 2 * m_size2, 2 * m_size2);
			if (p1 != null) g.drawRect((int)p1.getX() - m_size2, (int)p1.getY() - m_size2, 2 * m_size2, 2 * m_size2);
		    }
		    else {
			g.drawRect((int)dots[2] - m_size2, (int)dots[3] - m_size2, 2 * m_size2, 2 * m_size2);
			pathIter.next();
		    }
		    break;
                case PathIterator.SEG_CUBICTO:
		    if (isSelected(dots[4], dots[5])) {
			g.fillRect((int)dots[4] - m_size2, (int)dots[5] - m_size2, 2 * m_size2, 2 * m_size2);
			pathIter.next();
		    }
		    else {
			g.drawRect((int)dots[4] - m_size2, (int)dots[5] - m_size2, 2 * m_size2, 2 * m_size2);
			pathIter.next();
		    }
		    break;
                default:
		    pathIter.next();
                    break;
                }
	    }
            g2d.draw(path);
            g.setColor(new Color(0,0,0));
        }
        if (m_p3 != null && m_p4 != null) {
	    g.setColor(new Color(255,0,0));
	    if (m_p0 == null) 
		g.drawRect((int)m_p3.getX() - m_size2, (int)m_p3.getY() - m_size2, 2 * m_size2, 2 * m_size2);
	    else if (m_p1 == null) 
		g2d.draw(new QuadCurve2D.Double(m_p0.getX(), m_p0.getY(),
						2*m_p3.getX() - m_p4.getX(), 2*m_p3.getY() - m_p4.getY(),
						m_p3.getX(), m_p3.getY()));
	    else 
		g2d.draw(new CubicCurve2D.Double(m_p0.getX(), m_p0.getY(),
						 m_p1.getX(), m_p1.getY(),
						 2*m_p3.getX() - m_p4.getX(), 2*m_p3.getY() - m_p4.getY(),
						 m_p3.getX(), m_p3.getY()));
	    g.drawRect((int)m_p3.getX() - m_size2, (int)m_p3.getY() - m_size2, 2 * m_size2, 2 * m_size2);
	    g.setColor(new Color(0,0,0));
	    g.drawLine((int)(2*m_p3.getX() - m_p4.getX()), (int)(2*m_p3.getY() - m_p4.getY()),
		       (int)m_p4.getX(), (int)m_p4.getY());
	    g.drawRect((int)(2*m_p3.getX() - m_p4.getX() - m_size2), (int)(2*m_p3.getY() - m_p4.getY() - m_size2), 2 * m_size2, 2 * m_size2);
	    g.drawRect((int)m_p4.getX() - m_size2, (int)m_p4.getY() - m_size2, 2 * m_size2, 2 * m_size2);
	}
    }
    
    public void mousePressed(MouseEvent e) { m_state = m_state.mousePressed(e); }
    public void mouseReleased(MouseEvent e) { m_state = m_state.mouseReleased(e); }
    public void mouseDragged(MouseEvent e) { m_state = m_state.mouseDragged(e); }
    public void mouseClicked(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
    public void mouseMoved(MouseEvent e) {}
}
