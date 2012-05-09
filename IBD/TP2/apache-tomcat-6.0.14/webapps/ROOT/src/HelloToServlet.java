import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

/**
 * A simple Servlet that requests parameters.
 *
 */

public class HelloToServlet extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException
    {
	String firstName, lastName;

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Hello To</title>");
        out.println("</head>");
        out.println("<body>");
	firstName = request.getParameter("firstname");
	lastName= request.getParameter("lastname");
        if (firstName != null && lastName != null) {
            out.println("<h1>Hello " + firstName + " " + lastName + "!</h1>");
        } else {
            out.println("Firstname and lastname parameters not specified, Please enter some.");
            out.println("<P>");
            out.print("<form action=\"");
            out.print("HelloToServlet\" ");
            out.println("method=POST>");
            out.println("First Name:");
            out.println("<input type=text size=20 name=firstname>");
            out.println("<br>");
            out.println("Last Name:");
            out.println("<input type=text size=20 name=lastname>");
            out.println("<br>");
            out.println("<input type=submit>");
            out.println("</form>");
        }
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