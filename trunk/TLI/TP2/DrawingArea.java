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
    private enum State { ADD, MOVE };

    /** Attributs */
    private State m_state;
    private Path2D m_curPath;
    private Vector<Path2D> m_path;
    private Point m_p0, m_p1, m_p2, m_p3, m_p4;

    /** Constructeurs */
    public DrawingArea() {
        setPreferredSize(new Dimension(512, 512));
        m_curPath = null;
        m_path = new Vector<Path2D>();
        newLine();
	
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
        m_p0 = m_p1 = m_p2 = m_p3 = m_p4 = null;
        m_curPath = new Path2D.Double();
        m_path.add(m_curPath);
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
        else if (m_p1 == null) m_curPath.quadTo(2*p.getX() - t.getX(), 2*p.getY() - t.getY(),
                                                p.getX(), p.getY());
        else m_curPath.curveTo(m_p1.getX(), m_p1.getY(),
                               2*p.getX() - t.getX(), 2*p.getY() - t.getY(),
                               p.getX(), p.getY());
        m_p0 = p;
        m_p1 = t;
        repaint();
    }

    public void paintComponent(Graphics g) {
        int size2 = 2;
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
                    g.drawRect((int)dots[0] - size2, (int)dots[1] - size2, 2 * size2, 2 * size2);
                    break;
                case PathIterator.SEG_LINETO:
                    g.drawRect((int)dots[0] - size2, (int)dots[1] - size2, 2 * size2, 2 * size2);
                    break;
                case PathIterator.SEG_QUADTO:
                    g.drawRect((int)dots[2] - size2, (int)dots[3] - size2, 2 * size2, 2 * size2);
                    break;
                case PathIterator.SEG_CUBICTO:
                    g.drawRect((int)dots[4] - size2, (int)dots[5] - size2, 2 * size2, 2 * size2);
                    break;
                default:
                    break;
                }
                pathIter.next();
            }
            g2d.draw(path);
            g.setColor(new Color(0,0,0));
        }
        if (m_p3 != null && m_p4 != null) {
            g.setColor(new Color(255,0,0));
            if (m_p0 == null) 
                g.drawRect((int)m_p3.getX() - size2, (int)m_p3.getY() - size2, 2 * size2, 2 * size2);
            else if (m_p1 == null) 
                g2d.draw(new QuadCurve2D.Double(m_p0.getX(), m_p0.getY(),
                                                2*m_p3.getX() - m_p4.getX(), 2*m_p3.getY() - m_p4.getY(),
                                                m_p3.getX(), m_p3.getY()));
            else 
                g2d.draw(new CubicCurve2D.Double(m_p0.getX(), m_p0.getY(),
                                                 m_p1.getX(), m_p1.getY(),
                                                 2*m_p3.getX() - m_p4.getX(), 2*m_p3.getY() - m_p4.getY(),
                                                 m_p3.getX(), m_p3.getY()));
            g.setColor(new Color(0,0,0));
            g.drawLine((int)(2*m_p3.getX() - m_p4.getX()), (int)(2*m_p3.getY() - m_p4.getY()),
                       (int)m_p4.getX(), (int)m_p4.getY());
            g.drawRect((int)(2*m_p3.getX() - m_p4.getX()), (int)(2*m_p3.getY() - m_p4.getY()), 2 * size2, 2 * size2);
            g.drawRect((int)m_p3.getX() - size2, (int)m_p3.getY() - size2, 2 * size2, 2 * size2);
            g.drawRect((int)m_p4.getX() - size2, (int)m_p4.getY() - size2, 2 * size2, 2 * size2);
        }
    }
    
    public void mouseClicked(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
    
    public void mousePressed(MouseEvent e) { 
        Point p = e.getPoint();
        m_p4 = m_p3 = p;

        m_state = State.ADD;
        PathIterator pathIter = m_curPath.getPathIterator(null);
        while (!pathIter.isDone()) {
            double[] dots = new double[6];
            switch (pathIter.currentSegment(dots)) {
            case PathIterator.SEG_MOVETO:
                if (p.getX() == dots[0] && p.getY() == dots[1]) m_state = State.MOVE;
                break;
            case PathIterator.SEG_LINETO:
                if (p.getX() == dots[0] && p.getY() == dots[1]) m_state = State.MOVE;
                break;
            case PathIterator.SEG_QUADTO:
                if (p.getX() == dots[2] && p.getY() == dots[3]) m_state = State.MOVE;
                break;
            case PathIterator.SEG_CUBICTO:
                if (p.getX() == dots[4] && p.getY() == dots[5]) m_state = State.MOVE;
                break;
            default:
                break;
            }
            pathIter.next();
        }
    }
    
    public void mouseReleased(MouseEvent e) {
        if (m_p3 != null) {
            m_p4 = e.getPoint();
            switch (m_state) {
            case ADD:
                if (m_p4.equals(m_p3)) addPoint(m_p3);
                else addPoint(m_p3, m_p4);
                break;
            case MOVE:
                throw new RuntimeException();
            }
        }
        m_p3 = m_p4 = null;
    }
    
    public void mouseDragged(MouseEvent e) {
        if (m_p3 != null && !m_p4.equals(e.getPoint())) {
            m_p4 = e.getPoint();
            repaint();
        }
    }
    public void mouseMoved(MouseEvent e) {}
}