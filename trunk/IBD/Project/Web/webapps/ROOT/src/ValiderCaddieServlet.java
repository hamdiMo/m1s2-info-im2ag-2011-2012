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

public class ValiderCaddieServlet extends HttpServlet {

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

	res.setContentType("text/html");

	HttpSession session = getSession();
	Caddie caddie = session.getAttribute("caddie");

	out.println("<HEAD><TITLE> Validation du caddie  </TITLE></HEAD>");
	out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
	out.println("<font color=\"#FFFFFF\"><h1> Valider Caddie </h1>");
	
	if (caddie == null) out.println("Le caddie est vide");
	else{
	      try{
		Ticket t;
		ListIterator<Reservation> it = caddie.getReservations().listIterator();
		  while(it.hasNext()){
		    Reservation reservation = it.next();
		    t = GestionRequete.reserverTicket(reservation.getRepresentation(), reservation.getPlace());
		    if (t != null) out.println(" Le " + t.toString() + " a ete reserve");
		  }
	    }
	    
	    catch(SQLException e2) {
	    	out.println("Erreur oracle : " + e2.getErrorCode() + e2.getMessage());
	    }
// 	    catch(Exception e1) {
// 	    	out.println("erreur constructeur Ticket");
// 	    }
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
        return "Reserve les places contenues dans caddie";
    }

}
