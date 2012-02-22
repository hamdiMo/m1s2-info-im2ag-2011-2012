package util;

import java.util.Serializable;
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
	m_date = (new Calendar()).getDate();
    }

    /** Methodes */
    
    
    /** Variables de classe */
    // private static final long serialVersionUID = 42L;
    
}