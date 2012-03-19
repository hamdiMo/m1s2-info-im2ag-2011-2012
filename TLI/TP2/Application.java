import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.event.*;


public class Application extends JFrame {

    /** Attributs */
    private Action m_resetAction, m_newLineAction;
    private JMenuBar m_menuBar;
    private JToolBar m_toolBar;
    private DrawingArea m_drawingArea;


    /** Constructeurs */
    public Application() {
	super("Subdivision");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
	createActions();
	setJMenuBar(createMenuBar());
	//	getContentPane().add(createToolBar(), BorderLayout.NORTH);
	getContentPane().add(createDrawingArea(), BorderLayout.CENTER);
        
        pack();
        setVisible(true);
    }

    /** Methodes internes */
    private void createActions() {
	m_resetAction = new AbstractAction("Reset") {
		public void actionPerformed(ActionEvent e) { m_drawingArea.reset(); }
	    };
	
	m_newLineAction = new AbstractAction("New Line") {
		public void actionPerformed(ActionEvent e) { m_drawingArea.newLine(); }
	    };
    }

    private JMenuBar createMenuBar() { 
	m_menuBar = new JMenuBar();
	m_menuBar.add(createEditMenu());
	return m_menuBar;
    }

    private JMenu createEditMenu() {
	JMenu menu = new JMenu("Edit");
	menu.add(m_newLineAction);
	menu.add(m_resetAction);
	return menu;
    }

    private JToolBar createToolBar() { return m_toolBar = null; }

    private JComponent createDrawingArea() {
	return m_drawingArea = new DrawingArea();
    }

    public static void main(String [] args) {
	SwingUtilities.invokeLater(new Runnable() {
		public void run() { Application app = new Application(); }
	    });
    }

}