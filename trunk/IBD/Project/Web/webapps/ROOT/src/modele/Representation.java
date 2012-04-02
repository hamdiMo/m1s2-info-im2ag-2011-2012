/*
 * File : Representation.java
 */

package modele;

import java.util.ArrayList;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.text.ParsePosition;


/**
 * Classe representant une representation pour un spectacle du theatre.
 */
public class Representation {
  
  /* CLASS VARIABLES */
  private static SimpleDateFormat dateFormat;
  static {
      dateFormat = new SimpleDateFormat("dd-MMM-yyyy KK:mm:ss aa");
  }
  
  /* INSTANCE VARIABLES */
  
  /** La date exacte de la representation. */
  private Date dateRep;
  /** Le spectacle pour lequel il y a la representation. */
  private Spectacle spectacle;
  /** L'ensemble de tickets emis pour la representation. */
  private ArrayList<Ticket> tickets;
  
  /* CONSTRUCTORS */
  
  /**
    * Creation d'une nouvelle representation a une date donnee. La date doit
    * respecter le format "jj-mm-aaaa", et l'heure est un entier compris entre
    * 0 et 23.
    * @param dateRep_  la chaine de caracteres indiquant la date de la 
    *                  representation
    * @param heure_  l'entier (compris entre 0 et 23) indiquant l'heure precise 
    *                de la representation
    * @throws FormatDateException  si la description de la date ne respecte pas 
    *                              le format souhaite 
    */
  public Representation(String dateRep_, int heure_) throws FormatDateException {
      // if(heure_ < 0 || heure_ > 23)
      //   throw new FormatDateException("Mauvaise heure : " + heure_);
      // if( (dateRep = dateFormat.parse(dateRep_+" "+heure_, new ParsePosition(0))) == null)
      //   throw new FormatDateException("Mauvaise date : " + dateRep_);
      if(heure_ < 0 || heure_ > 23) throw new FormatDateException("Mauvaise heure : " + heure_);
      boolean pm = heure_ >= 12;
      if (pm) heure_ -= 12;
      String format = new String(dateRep_+" "+heure_+":00:00 ");
      if (pm) format += "pm"; else format += "am";
      if( (dateRep = dateFormat.parse(format, new ParsePosition(0))) == null)
          throw new FormatDateException("Mauvaise date : " + dateRep_);
      spectacle = null;
      tickets = new ArrayList<Ticket>();
  }
  
  /**
    * Creation d'une nouvelle representation a une date donnee. 
    * @param dateRep_  l'objet de type date indiquant la date de la representation
    */
  public Representation(Date dateRep_) {
    dateRep = dateRep_;
    spectacle = null;
    tickets = new ArrayList<Ticket>();
  }
  
  /**
    * Creation d'une nouvelle representation a une date donnee, pour un 
    * spectacle et un ensemble de tickets emis.
    * La date doit respecter le format "jj-mm-aaaa", et l'heure est un entier 
    * compris entre 0 et 23.
    * @param dateRep_  la chaine de caracteres indiquant la date de la 
    *                  representation
    * @param heure_  l'entier (compris entre 0 et 23) indiquant l'heure precise 
    *                de la representation
    * @param spectacle_  le spectacle pour lequel il y a la representation
    * @param tickets_  l' ensemble de tickets emis pour la representation
    * @throws FormatDateException  si la description de la date ne respecte pas 
    * le format souhaite 
    */
  public Representation(String dateRep_, int heure_, Spectacle spectacle_,
                        ArrayList<Ticket> tickets_) throws FormatDateException {
      // if(heure_ < 0 || heure_ > 23)
      //   throw new FormatDateException("Mauvaise heure : " + heure_);
      // if( (dateRep = dateFormat.parse(dateRep_+" "+heure_, new ParsePosition(0))) == null)
      //   throw new FormatDateException("Mauvaise date : " + dateRep_);
      if(heure_ < 0 || heure_ > 23) throw new FormatDateException("Mauvaise heure : " + heure_);
      boolean pm = heure_ >= 12;
      if (pm) heure_ -= 12;
      String format = new String(dateRep_+" "+heure_+":00:00 ");
      if (pm) format += "pm"; else format += "am";
      if( (dateRep = dateFormat.parse(format, new ParsePosition(0))) == null)
          throw new FormatDateException("Mauvaise date : " + dateRep_);
      spectacle = spectacle_;
      tickets = tickets_;
  }
  
  /**
    * Creation d'une nouvelle representation a une date donnee, pour un 
    * spectacle et un ensemble de tickets emis.
    * @param dateRep_  l'objet de type date indiquant la date de la representation
    * @param spectacle_  le spectacle pour lequel il y a la representation
    * @param tickets_  l' ensemble de tickets emis pour la representation
    */
  public Representation(Date dateRep_, Spectacle spectacle_,
                        ArrayList<Ticket> tickets_) {
    dateRep = dateRep_;
    spectacle = spectacle_;
    tickets = tickets_;
  }
  
  /* GETTERS */
  
  /**
    * Recupere l'objet indiquant la date de la representation.
    * @return  l'objet de type date indiquant la date de la representation
    */
  public Date getDateRep() {
    return this.dateRep;
  }
  
  /**
    * Recupere la date de la representation.
    * @return  une chaine de caracteres decrivant la date de la representation
    */
  public String getDateRepText() {
    return (dateFormat.format(this.dateRep));
  }
  
  /**
    * Recupere le spectacle associe a la representation.
    * @return  le spectacle associe a la representation
    */
  public Spectacle getSpectacle() {
    return this.spectacle;
  }
  
  /**
    * Recupere l'ensemble de tickets emis pour la representation.
    * @return   une collection de tickets emis pour la representation
    */
  public ArrayList<Ticket> getTickets() {
    return this.tickets;
  }
  
  /* SETTERS */
  
  /**
    * Modifie la date de la representation courante.
    * @param dateRep_  l'objet de type date indiquant la nouvelle date de la representation
    */
  public void setDateRep(Date dateRep_) {
    this.dateRep = dateRep_;
  }
  
  /**
    * Modifie la date de la representation courante.
    * @param dateRep_  la chaine de caracteres indiquant la nouvelle date de la 
    *                  representation
    * @param heure_  l'entier (compris entre 0 et 23) indiquant l'heure precise 
    *                de la representation
    * @throws FormatDateException  si la description de la date ne respecte pas 
    *                              le format souhaite 
    */
  public void setDateRep(String dateRep_, int heure_) throws FormatDateException  {
      // if(heure_ < 0 || heure_ > 23)
      //   throw new FormatDateException("Mauvaise heure : " + heure_);
      // if( (dateRep = dateFormat.parse(dateRep_+" "+heure_, new ParsePosition(0))) == null)
      //   throw new FormatDateException("Mauvaise date : " + dateRep_);
      if(heure_ < 0 || heure_ > 23) throw new FormatDateException("Mauvaise heure : " + heure_);
      boolean pm = heure_ >= 12;
      if (pm) heure_ -= 12;
      String format = new String(dateRep_+" "+heure_+":00:00 ");
      if (pm) format += "pm"; else format += "am";
      if( (dateRep = dateFormat.parse(format, new ParsePosition(0))) == null)
          throw new FormatDateException("Mauvaise date : " + dateRep_);
  }
  
  /**
    * Modifie le spectacle de la representation courante.
    * @param spectacle_  le nouveau spectacle associee a la representation
    */
  public void setSpectacle(Spectacle spectacle_) {
    this.spectacle = spectacle_;
  }
  
  /**
    * Modifie l'ensemble de tickets emis pour la representation curante.
    * @param tickets_  le nouveau ensemble de tickets emis pour la representation
    */
  public void setTickets(ArrayList<Ticket> tickets_) {
    this.tickets = tickets_;
  }
  
  /* OTHER METHODS */
  
  /**
    * Retourne une chaine de caracteres decrivant l'objet.
    * @return  une chaine de caracteres decrivant l'objet
    */
  public String toString() {
    String result = "Representation (";
    if(spectacle != null) {
      result = result + spectacle.getNumS() + ", ";
    }
    result = result + getDateRepText() + ")";
    return result;
  }
  
}
