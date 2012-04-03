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
import java.sql.Timestamp;
import java.util.Date;

/**
 * NouvelleRepresentation Servlet.
 *
 * This servlet dynamically adds a new date a show.
 *
 * @author <a href="mailto:Sara.Bouchenak@imag.fr">Sara Bouchenak</a>
 * @version 1.0, 31/10/2007
 */

public class ReserverPlaceServlet extends HttpServlet {

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
        String numS, dateS, heureS, numZ;
        ServletOutputStream out = res.getOutputStream();   

        res.setContentType("text/html");

        out.println("<HEAD><TITLE> Reservation d'une place  </TITLE></HEAD>");
        out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");

        numS	= req.getParameter("numS");
        dateS	= req.getParameter("date");
        heureS	= req.getParameter("heure");
        numZ    = req.getParameter("numZ");
        if (numS == null || dateS == null || heureS == null || numZ == null) {
            out.println("<font color=\"#FFFFFF\"><h1> Reserver une place </h1>");
            out.println("<font color=\"#FFFFFF\">Veuillez saisir les informations relatives a la place que vous desirez reserver :");
            out.println("<P>");
            out.print("<form action=\"");
            out.print("ReserverPlaceServlet\" ");
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
            out.println("Numero de la zone :");
            out.println("<input type=text size=20 name=numZ>");
            out.println("<br>");
            out.println("<input type=submit>");
            out.println("</form>");
        } else {
            try{
                Spectacle s1 = GestionRequete.trouveSpectacle(new Integer(numS).intValue());
                Representation r = GestionRequete.trouveRepresentation(s1, dateS, new Integer(heureS).intValue());
                Ticket t = GestionRequete.reserverTicket(r, new Zone(new Integer(numZ).intValue()));
                out.println("<font color=\"#FFFFFF\"><h1> Reserver une place pour " + r + " </h1>");
                out.println("<p><i><font color=\"#FFFFFF\">");
                if (t != null) {
                    out.println("Le ticket " + t + " vous a été attribué avec succes");
                }
                else {
                    out.println("Pas de places disponibles dans la zone " + numZ);
                }
                out.println("</i></p>");

                // ArrayList<Place> placesDisponibles = GestionRequete.trouvePlacesDisponibles(r);
                // int indexPlace = 0;
                // while (placesDisponibles.get(indexPlace) != null
                //        && (placesDisponibles.get(indexPlace).getNoPlace() != new Integer(noPlaceS).intValue()
                //            || placesDisponibles.get(indexPlace).getNoRang() != new Integer(noRangS).intValue())) 
                //     indexPlace++;
                // Place p = placesDisponibles.get(indexPlace);
                // Ticket ti;
                // if(p != null && r !=null) ti = GestionRequete.reserverTicket(r, p);
                // else out.println("Erreur place nulle");
                // out.println("</i></p>");
            }
            catch(SQLException e2) {
                out.println("Erreur oracle : " + e2.getErrorCode() + e2.getMessage());
                // Object[] rep = e2.getStackTrace();
                // for (int i = 0; i < rep.length; i++)
                //     out.println(" " + i + " : " + rep[i] + " <br>");
            }
        }

        out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/admin/admin.html\">Page d'administration</a></p>");
        out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/index.html\">Page d'accueil</a></p>");
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
