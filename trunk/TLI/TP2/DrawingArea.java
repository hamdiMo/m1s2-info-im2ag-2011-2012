import javax.swing.*;
import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.Point;

import java.awt.event.*;

import java.util.ArrayList;

public class DrawingArea extends JPanel {

    /** Type interne */
    private enum State { ADD };

    /** Attributs */
    private ArrayList<Point> m_points;
    private 

    /** Constructeurs */
    public DrawingArea() {
	setPreferredSize(new Dimension(512, 512));
        addMouseListener(new MouseAdapter() { public void mouseClicked(MouseEvent e) { clickOn(e.getPoint()); } });
        
	m_points = new ArrayList<Point>();
    }

    /** Methodes */
    public void reset() {}

    public void newLine() {}

    public void clickOn(Point p) {}

    public void paintComponent(Graphics g) {
	drawPoint(m_points[0], g);
	for (int i = 0; i < m_points.length - 1; i++) drawSeg(m_points[i], m_points[i+1], g);
    }
    
    private void drawPoint(Point p, Graphics g) {
	int size2 = 5;
	g.drawRect((int)p.getX() - size2, (int)p.getY() - size2, 2 * size2, 2 * size2);
    }

    private void drawSeg(Point p0, Point p1, Graphics g) {
	g.drawLine((int)p0.getX(), (int)p0.getY(), (int)p1.getX(), (int)p1.getY());
    }

}