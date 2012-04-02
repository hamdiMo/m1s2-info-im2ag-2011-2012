/*
 * @(#)NouvelleRepresentationServlet.java	1.0 2007/10/31
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
 * NouvelleRepresentation Servlet.
 *
 * This servlet dynamically adds a new date a show.
 *
 * @author <a href="mailto:Sara.Bouchenak@imag.fr">Sara Bouchenak</a>
 * @version 1.0, 31/10/2007
 */

public class PlacesDisponiblesServlet extends HttpServlet {

    /**
     * HTTP GET request entry point.
     *
     * @param req	an HttpServletRequest object that contains the request 
     *			the client has made of the servlet
     * @param res	an HttpServletResponse object that contains the response 
     *			the servlet sends to the client
     *
     * @throws ServletException   if the request for the GET could not be handled
     * @throws IOException	 if an input or output error is detected 
     *				 when the servlet handles the GET request
     */
    public void doGet(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException
    {
	String numS, dateS, heureS;
	ServletOutputStream out = res.getOutputStream();   

	res.setContentType("text/html");

	out.println("<HEAD><TITLE> Places Disponibles </TITLE></HEAD>");
	out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
    
	numS	= req.getParameter("numS");
	dateS	= req.getParameter("date");
	heureS	= req.getParameter("heure");
	if (numS == null || dateS == null || heureS == null) {
        out.println("<font color=\"#FFFFFF\"><h1> Voir les places disponibles </h1>");
	    out.println("<font color=\"#FFFFFF\">Veuillez saisir les informations relatives a la representation :");
	    out.println("<P>");
	    out.print("<form action=\"");
	    out.print("PlacesDisponiblesServlet\" ");
	    out.println("method=POST>");
	    out.println("Num&eacute;ro de spectacle :");
	    out.println("<input type=text size=20 name=numS>");
	    out.println("<br>");
	    out.println("Date de la repr&eacute;sentation :");
	    out.println("<input type=text size=20 name=date>");
	    out.println("<br>");
	    out.println("Heure de d&eacute;but de la repr&eacute;sentation :");
	    out.println("<input type=text size=20 name=heure>");
	    out.println("<br>");
	    out.println("<input type=submit>");
	    out.println("</form>");
	} else {
	    try {
            Spectacle s1 = GestionRequete.trouveSpectacle(new Integer(numS).intValue());
            Representation r = GestionRequete.trouveRepresentation(s1, dateS, new Integer(heureS).intValue());
            ArrayList<Place> placesDisponibles = GestionRequete.trouvePlacesDisponibles(r);
            out.println("<font color=\"#FFFFFF\"><h1> Places disponibles pour " + r + " de " + r.getSpectacle() +" </h1>");
            out.println("<p><i><font color=\"#FFFFFF\">");
            for(int i=0; i<placesDisponibles.size(); i++) {
                Place p = placesDisponibles.get(i);
                out.println("<a href=\"ReserverPlaceServlet?numS="+numS+"&date="+dateS+"&heure="+heureS+"&noPlace="+p.getNoPlace()+"&noRang="+p.getNoRang()+"\">");
                out.println(p.toString());
                out.println("</a> <br>");
            }
            out.println("</i></p>");
	    }
	    catch(SQLException e2) {
	    	out.println("Erreur oracle : " + e2.getErrorCode() + e2.getMessage());
	    }
	}
    
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
        return "Affiche les representations pour un spectacle existant";
    }

}
