import java.io.*;
import java.net.*;
import java.util.*;

import javax.servlet.*;
import javax.servlet.http.*;

/*
 * Quid servlet
 */
public class QuidServlet extends HttpServlet {

    public void service(HttpServletRequest req, HttpServletResponse res)
	throws IOException
    {
	ServletOutputStream out = res.getOutputStream();
	ServletContext servletContext = getServletContext();
	String name = servletContext.getRealPath("quid.html");
	RandomAccessFile fil = new RandomAccessFile(name, "rw");
	String entry = req.getParameter("entry");
	String noentry = req.getParameter("noentry");
	String entries[] = new String[50];
	int i;
	entries[0] = null;

        res.setContentType("text/html");

	for (i=1; i<50; i++)
	    if (fil.getFilePointer() < fil.length())
		entries[i] = fil.readLine();
	    else
		entries[i] = null;

	if (entry != null && noentry == null) {
	    fil.seek(0);
	    while ((i=entry.indexOf("\n")) != -1)
		entry=entry.substring(0,i-1).concat("<BR>").concat(entry.substring(i+1,entry.length()));
	    entries[0]=entry;
	    fil.writeBytes(entry + "\n");
	    for (i=1; i<50; i++)
		if (entries[i] != null)
		    fil.writeBytes(entries[i] + "\n");
	}
	fil.close();
	quid(out, entries);
    }

    public void quid(ServletOutputStream out, String entries[]) throws IOException {
	int i;

	out.print("<HR>");
	for (i=0; i<50; i++)
	    if (entries[i] != null) {
		out.print(entries[i]);
		out.print("<HR>");
	    }
        out.flush();
    }

}

