import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

/**
 * A simple Servlet that requests parameters.
 *
 */

public class HappyBirthdayServlet extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException
    {
	String jour, mois, annee;
	Cookie[] cookies;
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Happy Birthday</title>");
        out.println("</head>");
        out.println("<body>");
	//	cookies = request.getCookies();
	// if (cookies.size > 0) {
	//     String s;
	//     for (int i=O; i< cookies.size(); i++){
	// 	if (cookies[i].getName().equals("jour")) jour = cookies[i].getValue();
	// 	if (cookies[i].getName().equals("mois")) mois = cookies[i].getValue();
	// 	if (cookies[i].getName().equals("annee")) annee = cookies[i].getValue();
	//     }
	//     out.println("Vous etes né le " );
	// } else {
	    jour = request.getParameter("jour");
	    mois = request.getParameter("mois");
	    annee = request.getParameter("annee");
	    
	    if (annee != null && mois != null && jour != null) {
		out.println("Vous etes né le " + jour + "/" + mois + "/" + annee );
		//cookie= new Cookie("HappyBirthdayServletCookie", new String(jour + "/" + mois + "/" + annee));
	    } else {
		out.println("year, day and month parameters not specified, Please enter some.");
		out.println("<P>");
		out.print("<form action=\"");
		out.print("HappyBirthdayServlet\" ");
		out.println("method=POST>");
		out.println("Jour:");
		out.println("<input type=text size=20 name=jour>");
		out.println("<br>");
		out.println("Mois:");
		out.println("<input type=text size=20 name=mois>");
		out.println("<br>");
		out.println("Annee:");
		out.println("<input type=text size=20 name=annee>");
		out.println("<br>");
		out.println("<input type=submit>");
		out.println("</form>");
	    }
	// }
	out.println("<a href=\"/\">back</a>");
        out.println("</body>");
        out.println("</html>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException
    {
        doGet(request, response);
    }
}