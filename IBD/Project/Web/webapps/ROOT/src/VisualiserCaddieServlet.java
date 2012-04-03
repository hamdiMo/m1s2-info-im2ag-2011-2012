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
import java.util.ListIterator;


/**
 * NouvelleRepresentation Servlet.
 *
 * This servlet dynamically adds a new date a show.
 *
 * @author <a href="mailto:Sara.Bouchenak@imag.fr">Sara Bouchenak</a>
 * @version 1.0, 31/10/2007
 */

public class VisualiserCaddieServlet extends HttpServlet {

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

        out.println("<HEAD><TITLE> Validation du caddie  </TITLE></HEAD>");
        out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
        out.println("<font color=\"#FFFFFF\"><h1> Visualisation du caddie </h1>");
        out.println("<p><i><font color=\"#FFFFFF\">");
	
        Caddie caddie = (Caddie)session.getAttribute("caddie");
        if (caddie == null) out.println("Votre caddie est vide");
        else {
            ListIterator<Reservation> it = caddie.getReservations().listIterator();
            while (it.hasNext()) {
                Reservation reservation = it.next();
                out.println("Reservation : " + reservation.getRepresentation() + " : " + reservation.getPlace() + "<br>");
            }
            out.println("<a href=\"ValiderCaddieServlet\">valider le caddie</a>");
        }
        
        out.println("</i></p>");
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
        return "Reserve les places contenues dans caddie";
    }

}
