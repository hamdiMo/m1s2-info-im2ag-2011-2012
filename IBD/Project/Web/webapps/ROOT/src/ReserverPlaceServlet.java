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
	String numS, dateS, heureS, noPlaceS, noRangS;
	ServletOutputStream out = res.getOutputStream();   

	res.setContentType("text/html");

	out.println("<HEAD><TITLE> Reservation d'une place  </TITLE></HEAD>");
	out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
	out.println("<font color=\"#FFFFFF\"><h1> Reserver une place </h1>");

	numS	= req.getParameter("numS");
	dateS	= req.getParameter("date");
	heureS	= req.getParameter("heure");
	noPlaceS = req.getParameter("noPlace");
	noRangS =  req.getParameter("noRang");
	if (numS == null || dateS == null || heureS == null) {
	    out.println("<font color=\"#FFFFFF\">Veuillez saisir les informations relatives a la place que vous desirez reserver :");
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
	    out.println("Numero de la place :");
	    out.println("<input type=text size=20 name=noPlace>");
	    out.println("<br>");
	    out.println("Numero du rang :");
	    out.println("<input type=text size=20 name=noRang>");
	    out.println("<br>");
	    out.println("<input type=submit>");
	    out.println("</form>");
	} else {
		try{
	   	Spectacle s1 = GestionRequete.trouveSpectacle(new Integer(numS).intValue());
		Timestamp t = new Timestamp(new Integer(dateS.substring(6,10)).intValue()-1900, 
					    new Integer(dateS.substring(3,5)).intValue()-1, 
					    new Integer(dateS.substring(0,2)).intValue(), 
					    (new Integer(heureS).intValue()+1)%12, 0, 0, 0);
		String d = t.toGMTString();
		d = d.substring(0,20)+" pm";

		out.println(d);		
		//-----------------
// 		Date dat = new Date();
// 		t = new Timestamp(dat.getTime());
// 		t.setHours((t.getHours()+2)%12);
// 		d = t.toGMTString();
// 	    
// 	    
// 	    
// 	    
// 	    //d = "06-NOV-08 08:45:00 pm";
// 	    String dateEmission = d.substring(0,20)+" pm";
// 		out.println(dateEmission);
		//--------------
		Representation r = GestionRequete.trouveRepresentation(s1, d);
		//-----------------
		
// 		Date d1 = r.getDateRep();
// 		t = new Timestamp(dat.getTime());
// 		t.setHours((t.getHours()+2)%12);
// 		d = t.toGMTString();
// 		String daterep = d.substring(0,20)+" pm";
// 		out.println(daterep);
		//------------------
		ArrayList<Place> placesDisponibles = GestionRequete.trouvePlacesDisponibles(r);
		int indexPlace = 0;
		while (placesDisponibles.get(indexPlace) != null && (placesDisponibles.get(indexPlace).getNoPlace() != new Integer(noPlaceS).intValue()
		       || placesDisponibles.get(indexPlace).getNoRang() != new Integer(noRangS).intValue())) 
		    indexPlace++;
		Place p = placesDisponibles.get(indexPlace);
		Ticket ti;
		if(p != null && r !=null) ti = GestionRequete.reserverTicket(r, p);
		else out.println("Erreur place nulle");
		
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
        return "Affiche les representations pour un spectacle existant";
    }

}
