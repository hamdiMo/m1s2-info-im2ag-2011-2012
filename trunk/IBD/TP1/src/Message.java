import java.io.Serializable;
import java.util.Calendar;
import java.util.Date;


public class Message implements Serializable {

    /** Attributs */
    private String m_nom;
    private String m_message;
    private Date m_date;

    /** Constructeurs */
    Message(String nom, String message){
	m_nom = nom;
	m_message = message;
	m_date = Calendar.getInstance().getTime();
    }

    /** Methodes */
    public String toString(){
	return m_date.toString()+" "+ m_nom + " : "+ m_message;
    }
    
    /** Variables de classe */
    // private static final long serialVersionUID = 42L;
    
}