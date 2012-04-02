/*
 * @(#)ProgrammeServlet.java	1.0 2007/10/31
 * 
 * Copyright (c) 2007 Sara Bouchenak.
 */
import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

import java.util.ArrayList;
import java.sql.SQLException;
import modele.*;
import accesbd.*;


/**
 * Proramme Servlet.
 *
 * This servlet dynamically returns the theater program.
 *
 * @author <a href="mailto:Sara.Bouchenak@imag.fr">Sara Bouchenak</a>
 * @version 1.0, 31/10/2007
 */

public class ProgrammeServlet extends HttpServlet {

    /**
     * HTTP GET request entry point.
     *
     * @param req	an HttpServletRequest object that contains the request 
     *			the client has made of the servlet
     * @param res	an HttpServletResponse object that contains the response 
     *			the servlet sends to the client
     *
     * @throws ServletException   if the request for the GET could not be handled
     * @throws IOException	   if an input or output error is detected 
     *					   when the servlet handles the GET request
     */
    public void doGet(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException
    {
        ServletOutputStream out = res.getOutputStream();   

	res.setContentType("text/html");

	out.println("<HEAD><TITLE> Programme de la saison </TITLE></HEAD>");
	out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
	out.println("<font color=\"#FFFFFF\"><h1> Programme de la saison </h1>");
out.println("Spectacles : <br/>");
	// TO DO
	// Recuperation de la liste de tous les spectacles de la saison.
	try {
	    Saison saison = new Saison();
	    saison.setSpectacles(GestionRequete.trouveSpectacles()); 
	    out.println("<p>");
	    out.println("Spectacles : <br/>");
	    for(int i=0; i<saison.getSpectacles().size(); i++) {
		Spectacle s = saison.getSpectacles().get(i);
		out.println("<a href=\"RepresentationServlet?numS="+s.getNumS()+"\">");
		out.println(s.toString());
		out.println("</a>" + "<br>");
	    }
	    out.println("</p>");
	}
	catch(SQLException e) {
	    System.err.println("Erreur oracle : " + e.getErrorCode() + e.getMessage());
	}

	// Puis construction dynamique d'une page web decrivant ces spectacles.
	out.println("<p><i><font color=\"#FFFFFF\">...</i></p>");

	out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/index.html\">Accueil</a></p>");
	out.println("</BODY>");
	out.close();

    }

    /**
     * HTTP POST request entry point.
     *
     * @param req	an HttpServletRequest object that contains the request 
     *			the client has made of the servlet
     * @param res	an HttpServletResponse object that contains the response 
     *			the servlet sends to the client
     *
     * @throws ServletException   if the request for the POST could not be handled
     * @throws IOException	   if an input or output error is detected 
     *					   when the servlet handles the POST request
     */
    public void doPost(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException
    {
	doGet(req, res);
    }


    /**
     * Returns information about this servlet.
     *
     * @return String information about this servlet
     */

    public String getServletInfo() {
        return "Retourne le programme du theatre";
    }

}
