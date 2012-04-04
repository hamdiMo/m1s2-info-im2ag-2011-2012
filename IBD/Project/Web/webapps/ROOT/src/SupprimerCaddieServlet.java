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
import java.util.Date;
import java.util.ListIterator;

/**
 * NouvelleRepresentation Servlet.
 *
 * This servlet dynamically adds a new date a show.
 *
 * @author <a href="mailto:Sara.Bouchenak@imag.fr">Sara Bouchenak</a>
 * @version 1.0, 31/10/2007
 */

public class SupprimerCaddieServlet extends HttpServlet {

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
        String numS, dateS, heureS, noPlaceS, noRangS;
        ServletOutputStream out = res.getOutputStream();   
        HttpSession session = req.getSession(true);
        
        res.setContentType("text/html");

        out.println("<HEAD><TITLE> Supprimer un ticket du cadie  </TITLE></HEAD>");
        out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
        
        numS	= req.getParameter("numS");
        dateS	= req.getParameter("date");
        heureS	= req.getParameter("heure");
        noPlaceS= req.getParameter("noPlace");
        noRangS = req.getParameter("noRang");
        if (numS == null || dateS == null || heureS == null || noPlaceS == null || noRangS == null) {
            out.println("<font color=\"#FFFFFF\"><h1> Supprimer un ticket du caddie </h1>");
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
            out.println("Numero du rang :");
            out.println("<input type=text size=20 name=noRang>");
            out.println("<br>");
            out.println("Numero de la place :");
            out.println("<input type=text size=20 name=noPlace>");
            out.println("<br>");
            out.println("<input type=submit>");
            out.println("</form>");
        } else {
            try {
                Spectacle s1 = GestionRequete.trouveSpectacle(new Integer(numS).intValue());
                Representation r = GestionRequete.trouveRepresentation(s1, dateS, new Integer(heureS).intValue());
                Place p = new Place(new Integer(noPlaceS).intValue(), new Integer(noRangS).intValue());
                Reservation r2 = new Reservation(r, p);
                Caddie caddie = (Caddie)session.getAttribute("caddie");
                
                if (caddie == null) out.println("Votre caddie est vide");
		else {
		  ListIterator<Reservation> it = caddie.getReservations().listIterator();
		  while (it.hasNext()) {
		    Reservation reservation = it.next();
		    if(reservation.equals(r2)){
		      out.println("La reservation " + reservation + " a ete supprimee du caddie<br>");
		      caddie.removeReservation(reservation);
		    }
		  }
		  out.println("<a href=\"ValiderCaddieServlet\">valider le caddie</a>");
		}
                session.setAttribute("caddie", caddie);
                out.println("<font color=\"#FFFFFF\"><h1> Ajout au caddie </h1>");
                out.println("<p><i><font color=\"#FFFFFF\">");
                out.println("<a href=\"VisualiserCaddieServlet\">voir le contenu du caddie</a>");
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
