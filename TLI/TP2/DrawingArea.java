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


public class DrawingArea extends JPanel {

    /** Attributs */
    private Path2D m_curPath;
    private Vector<Path2D> m_path;
    private Point m_p0, m_p1, m_p2, m_p3, m_p4, m_curPoint;
    private int m_size2;

    /** Constructeurs */
    public DrawingArea() {
        setPreferredSize(new Dimension(512, 512));
        m_size2 = 5;
        m_curPath = null;
        m_path = new Vector<Path2D>();

        newLine();

        Interaction interaction = new Interaction(this);
        addMouseListener(interaction);
        addMouseMotionListener(interaction);
    }
    
    /** Predicats */
    public boolean isOnCurve(Point p) { 
        PathIterator pathIter = m_curPath.getPathIterator(null);
        while (!pathIter.isDone()) {
            double[] dots = new double[6];
            switch (pathIter.currentSegment(dots)) {
            case PathIterator.SEG_MOVETO:
                if (p.equals(new Point((int)dots[0], (int)dots[1]))) return true;
                break;
            case PathIterator.SEG_LINETO:
                if (p.equals(new Point((int)dots[0], (int)dots[1]))) return true;
                break;
            case PathIterator.SEG_QUADTO:
                if (p.equals(new Point((int)dots[2], (int)dots[3]))) return true;
                break;
            case PathIterator.SEG_CUBICTO:
                if (p.equals(new Point((int)dots[4], (int)dots[5]))) return true;
                break;
            default:
                pathIter.next();
                break;
            }
            pathIter.next();
        }
        return false;
    }
    
    public boolean isSelected(Point p) { return isSelected(p.getX(), p.getY()); }

    public boolean isSelected(double x, double y) {
        return m_curPoint != null && m_curPoint.getX() == x && m_curPoint.getY() == y;
    }
    
    public boolean isClick(Point p, Point cur) {
        return isClick(p.getX(), p.getY(), cur);
    }

    public boolean isClick(double x, double y, Point cur) {
        return x - m_size2 <= cur.getX() && cur.getX() <= x + m_size2
            && y - m_size2 <= cur.getY() && cur.getY() <= y + m_size2;
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
            Point p0 = null, p1 = null, p2 = null;
            switch (pathIter.currentSegment(dots)) {
            case PathIterator.SEG_MOVETO:
                p0 = new Point((int)dots[0], (int)dots[1]);
                break;
            case PathIterator.SEG_LINETO:
                p0 = new Point((int)dots[0], (int)dots[1]);
                break;
            case PathIterator.SEG_QUADTO:
                p0 = new Point((int)dots[2], (int)dots[3]);
                p1 = new Point((int)dots[0], (int)dots[1]);
                break;
            case PathIterator.SEG_CUBICTO:
                p0 = new Point((int)dots[4], (int)dots[5]);
                p1 = new Point((int)dots[2], (int)dots[3]);
                break;
            default:
                pathIter.next();
                break;
            }
            pathIter.next();
            if (!pathIter.isDone()) {
                int n = pathIter.currentSegment(dots);
                if (n == PathIterator.SEG_QUADTO || n == PathIterator.SEG_CUBICTO)
                    p2 = new Point((int)dots[0], (int)dots[1]);
            }
            if (p0 != null) {
                if (isClick(p0, p)) res = p0;
                if (isSelected(p0)) {
                    if (p1 != null && isClick(p1, p)) res = p1;
                    if (p2 != null && isClick(p2, p)) res = p2;
                }
            }
        }
        return res;
    }
    
    public void move(Point pi, Point pf) {
        boolean selected = false;
        Path2D copy = new Path2D.Double();
        PathIterator pathIter = m_curPath.getPathIterator(null);
        while (!pathIter.isDone()) {
            double[] dots = new double[6];
            Point p0 = null, p1 = null, p2 = null;
            switch (pathIter.currentSegment(dots)) {
            case PathIterator.SEG_MOVETO:
                p0 = new Point((int)dots[0], (int)dots[1]);
                if (isSelected(p0) && p0.equals(pi)) {
                    dots[0] = pf.getX();
                    dots[1] = pf.getY();
                }
                else if (isSelected(p0)) selected = true;
                copy.moveTo(dots[0], dots[1]);
                break;
            case PathIterator.SEG_LINETO:
                p0 = new Point((int)dots[0], (int)dots[1]);
                if (isSelected(p0) && p0.equals(pi)) {
                    dots[0] = pf.getX();
                    dots[1] = pf.getY();
                }
                else if (isSelected(p0)) selected = true;
                copy.lineTo(dots[0], dots[1]);
                break;
            case PathIterator.SEG_QUADTO:
                p0 = new Point((int)dots[2], (int)dots[3]);
                p1 = new Point((int)dots[0], (int)dots[1]);
                if (isSelected(p0) && p0.equals(pi)) {
                    dots[2] = pf.getX();
                    dots[3] = pf.getY();
                }
                else if ((isSelected(p0) || selected) && p1.equals(pi)) {
                    dots[0] = pf.getX();
                    dots[1] = pf.getY();
                }
                else if (isSelected(p0)) selected = true;
                copy.quadTo(dots[0], dots[1], dots[2], dots[3]);
                break;
            case PathIterator.SEG_CUBICTO:
                p0 = new Point((int)dots[4], (int)dots[5]);
                p1 = new Point((int)dots[2], (int)dots[3]);
                p2 = new Point((int)dots[0], (int)dots[1]);
                if (isSelected(p0) && p0.equals(pi)) {
                    dots[4] = pf.getX();
                    dots[5] = pf.getY();
                }
                else if ((isSelected(p0) || selected) && p1.equals(pi)) {
                    dots[2] = pf.getX();
                    dots[3] = pf.getY();
                }
                else if (selected && p2.equals(pi)) {
                    dots[0] = pf.getX();
                    dots[1] = pf.getY();
                }
                else if (isSelected(p0)) selected = true;
                copy.curveTo(dots[0], dots[1], dots[2], dots[3], dots[4], dots[5]);
                break;
            default:
                pathIter.next();
                break;
            }
            pathIter.next();
            selected = selected && isSelected(p0);
        }
        m_curPath = copy;
        m_path.set(m_path.size()-1, copy);
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
            Color c = new Color(0,0,0);
            Path2D path = m_path.get(i);
            PathIterator pathIter = path.getPathIterator(null);
            if (i == m_path.size() - 1) c = new Color(255,0,0);
            while (!pathIter.isDone()) {
                double[] dots = new double[6];
                Point p0 = null, p1 = null, p2 = null;
                switch (pathIter.currentSegment(dots)) {
                case PathIterator.SEG_MOVETO:
                    p0 = new Point((int)dots[0], (int)dots[1]);
                    break;
                case PathIterator.SEG_LINETO:
                    p0 = new Point((int)dots[0], (int)dots[1]);
                    break;
                case PathIterator.SEG_QUADTO:
                    p0 = new Point((int)dots[2], (int)dots[3]);
                    p1 = new Point((int)dots[0], (int)dots[1]);
                    break;
                case PathIterator.SEG_CUBICTO:
                    p0 = new Point((int)dots[4], (int)dots[5]);
                    p1 = new Point((int)dots[2], (int)dots[3]);
                    break;
                default:
                    pathIter.next();
                    break;
                }
                pathIter.next();
                if (!pathIter.isDone()) {
                    int n = pathIter.currentSegment(dots);
                    if (n == PathIterator.SEG_QUADTO || n == PathIterator.SEG_CUBICTO)
                        p2 = new Point((int)dots[0], (int)dots[1]);
                }
                if (p0 != null) {
                    if (isSelected(p0)) {
                        drawSelectedPoint(p0, g, c);
                        if (p1 != null) drawTangent(p1, p0, g);
                        if (p2 != null) drawTangent(p0, p2, g);
                    } else drawPoint(p0, g, c);
                }
            }
            g.setColor(c);
            g2d.draw(path);
        }
        if (m_p3 != null && m_p4 != null) {
            Color c = new Color(255,0,0);
            g.setColor(c);
            m_p2 = new Point((int)(2*m_p3.getX() - m_p4.getX()), (int)(2*m_p3.getY() - m_p4.getY()));
            if (m_p0 != null && m_p1 == null) {
                g2d.draw(new QuadCurve2D.Double(m_p0.getX(), m_p0.getY(),
                                                m_p2.getX(), m_p2.getY(),
                                                m_p3.getX(), m_p3.getY()));
            } else if (m_p0 != null && m_p1 != null)
                g2d.draw(new CubicCurve2D.Double(m_p0.getX(), m_p0.getY(),
                                                 m_p1.getX(), m_p1.getY(),
                                                 m_p2.getX(), m_p2.getY(),
                                                 m_p3.getX(), m_p3.getY()));
            drawPoint(m_p3, g, c);
            drawTangent(m_p2, m_p4, g);
        }
    }
    
    /** Methodes privées */
    private void drawLine(Point p0, Point p1, Graphics g, Color c) {
        g.setColor(c);
        g.drawLine((int)p0.getX(), (int)p0.getY(), (int)p1.getX(), (int)p1.getY());
    }
    
    private void drawPoint(Point p, Graphics g, Color c) {
        g.setColor(c);
        g.drawRect((int)p.getX() - m_size2, (int)p.getY() - m_size2, 2 * m_size2, 2 * m_size2);
    }

    private void drawSelectedPoint(Point p, Graphics g, Color c) {
        g.setColor(c);
        g.fillRect((int)p.getX() - m_size2, (int)p.getY() - m_size2, 2 * m_size2, 2 * m_size2);
    }

    private void drawTangent(Point p0, Point p1, Graphics g) {
        Color c = new Color(0,0,0);
        drawLine(p0, p1, g, c);
        drawPoint(p0, g, c);
        drawPoint(p1, g, c);
    }


}


/** Type interne */
class Interaction implements MouseListener, MouseMotionListener {
        
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
                else if (m_drawingArea.isOnCurve(m_p0)) m_drawingArea.select(m_p0);
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
                if (m_drawingArea.isOnCurve(m_p0)) m_drawingArea.select(m_p0);
                return SELECT;
            }
        };
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
    private DrawingArea m_drawingArea;

    /** Constructeurs */
    public Interaction(DrawingArea drawingArea) {
        m_drawingArea = drawingArea;
        m_state = State.InitState(m_drawingArea);
    }

    /** Methodes */
    public void mousePressed(MouseEvent e) { m_state = m_state.mousePressed(e); }
    public void mouseReleased(MouseEvent e) { m_state = m_state.mouseReleased(e); }
    public void mouseDragged(MouseEvent e) { m_state = m_state.mouseDragged(e); }
    public void mouseClicked(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
    public void mouseMoved(MouseEvent e) {}
}
