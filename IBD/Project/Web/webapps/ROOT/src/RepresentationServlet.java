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

import java.text.SimpleDateFormat;


/**
 * NouvelleRepresentation Servlet.
 *
 * This servlet dynamically adds a new date a show.
 *
 * @author <a href="mailto:Sara.Bouchenak@imag.fr">Sara Bouchenak</a>
 * @version 1.0, 31/10/2007
 */

public class RepresentationServlet extends HttpServlet {

    /* CLASS VARIABLES */
    private static SimpleDateFormat dateFormat, timeFormat;
    static {
      dateFormat = new SimpleDateFormat("dd-MMM-yyyy"); 
      timeFormat = new SimpleDateFormat("HH");
    }

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

        out.println("<HEAD><TITLE> Representations </TITLE></HEAD>");
        out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");

        numS	= req.getParameter("numS");
        if (numS == null) {
            out.println("<font color=\"#FFFFFF\"><h1> Voir les representations </h1>");
            out.println("<font color=\"#FFFFFF\">Veuillez saisir les informations relatives au spectatcle :");
            out.println("<P>");
            out.print("<form action=\"");
            out.print("RepresentationServlet\" ");
            out.println("method=POST>");
            out.println("Num&eacute;ro de spectacle :");
            out.println("<input type=text size=20 name=numS>");
            out.println("<br>");
            out.println("<input type=submit>");
            out.println("</form>");
        } else {
            try {
                Spectacle s1 = GestionRequete.trouveSpectacle(new Integer(numS).intValue());
                out.println("<font color=\"#FFFFFF\"><h1> Representations de " + s1 + "</h1>");
                out.println("<p><i><font color=\"#FFFFFF\">");
                ArrayList<Representation> representations = GestionRequete.trouveRepresentations(s1);
                for(int i=0; i<representations.size(); i++) {
                    Representation r = representations.get(i);
                    out.println(r.toString()
                                + " : <a href=\"PlacesDisponiblesServlet?numS=" + numS
                                + "&date=" + dateFormat.format(r.getDateRep())
                                + "&heure=" + timeFormat.format(r.getDateRep()) 
                                + "\">voir les places disponibles</a>"
                                + "<form action=\"ReserverPlaceServlet?numS=" + numS
                                + "&date=" + dateFormat.format(r.getDateRep())
                                + "&heure=" + timeFormat.format(r.getDateRep()) 
                                + "\" method=POST>"
                                + "Num&eacute;ro de zone :"
                                + "<input type=text size=20 name=numZ>"
                                + "<input type=submit>"
                                + "</form><br>");
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
