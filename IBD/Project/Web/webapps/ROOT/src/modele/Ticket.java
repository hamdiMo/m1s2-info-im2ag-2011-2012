/*
 * File : Ticket.java
 */

package modele;

import java.util.ArrayList;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.text.ParsePosition;


/**
 * Classe representant un ticket emis pour une place et une representation.
 */
public class Ticket {
  
  /* CLASS VARIABLES */
  private static SimpleDateFormat dateFormat;
  static {
    dateFormat = new SimpleDateFormat("dd-MM-yyyy HH");
  }
  
  /* INSTANCE VARIABLES */
  
  /** Le numero de serie du ticket. */
  private int noSerie;
  /** La date d'emission du ticket. */
  private Date dateEmission;
  /** La representation associee au ticket. */
  private Representation rep;
  /** La place associee au ticket. */
  private Place place;
  
  /* CONSTRUCTORS */
  
  /**
    * Creation d'un nouveau ticket pour un numero de serie et une date donnes.
    * @param noSerie_  le numero du ticket
    * @param dateEmission_  la date d'emission
    */
  public Ticket(int noSerie_, Date dateEmission_) {
    noSerie = noSerie_;
    dateEmission = dateEmission_;
    rep = null;
    place = null;
  }
  
  /**
    * Creation d'un nouveau ticket pour un numero de serie et une date donnes.
    * @param noSerie_  le numero du ticket
    * @param dateEmission_  la chaine de caractere decrivant la date d'emission
    * @param heure_  l'heure d'emission (entier compris entre 0 et 23)
    * @throws FormatDateException  si la description de la date ne respecte pas 
    *                              le format souhaite
    */
  public Ticket(int noSerie_, String dateEmission_, int heure_) throws FormatDateException {
    noSerie = noSerie_;
    if(heure_ < 0 || heure_ > 23)
      throw new FormatDateException("Mauvaise heure : " + heure_);
    if( (dateEmission = dateFormat.parse(dateEmission_+" "+heure_, new ParsePosition(0))) == null)
      throw new FormatDateException("Mauvaise date : " + dateEmission_);
    rep = null;
    place = null;
  }
  
  /**
    * Creation d'un nouveau ticket pour un numero de serie, une date, une 
    * representation et une place donnes.
    * @param noSerie_  le numero du ticket
    * @param dateEmission_  la date d'emission
    * @param rep_  la representation associee au ticket
    * @param place_  la place associee au ticket
    */
  public Ticket(int noSerie_, Date dateEmission_, Representation rep_, 
                Place place_) {
    noSerie = noSerie_;
    dateEmission = dateEmission_;
    rep = rep_;
    place = place_;
  }
  
  /**
    * Creation d'un nouveau ticket pour un numero de serie, une date, une 
    * representation et une place donnes.
    * @param noSerie_  le numero du ticket
    * @param dateEmission_  la chaine de caractere decrivant la date d'emission
    * @param heure_  l'heure d'emission (entier compris entre 0 et 23)
    * @param rep_  la representation associee au ticket
    * @param place_  la place associee au ticket
    * @throws FormatDateException  si la description de la date ne respecte pas 
    *                              le format souhaite
    */
  public Ticket(int noSerie_, String dateEmission_, int heure_, Representation rep_, 
                Place place_) throws FormatDateException {
    noSerie = noSerie_;
    if(heure_ < 0 || heure_ > 23)
      throw new FormatDateException("Mauvaise heure : " + heure_);
    if( (dateEmission = dateFormat.parse(dateEmission_+" "+heure_, new ParsePosition(0))) == null)
      throw new FormatDateException("Mauvaise date : " + dateEmission_);
    rep = rep_;
    place = place_;
  }
  
  /* GETTERS */
  
  /**
    * Recupere la date d'emission du ticket.
    * @return  l'objet de type date indiquant la date d'emission du ticket
    */
  public Date getDateEmission() {
    return this.dateEmission;
  }
  
  /**
    * Recupere la date d'emission du ticket.
    * @return  chaine de caracteres decrivant la date d'emission du ticket
    */
  public String getDateEmissionText() {
    return (dateFormat.format(this.dateEmission));
  }
  
  /**
    * Recupere le numero du ticket.
    * @return le numero de serie du ticket
    */
  public int getNoSerie() {
    return this.noSerie;
  }
  
  /**
    * Recupere la representation associee au ticket.
    * @return  la representation associee au ticket
    */
  public Representation getRep() {
    return this.rep;
  }
  
  /**
    * Recupere la place associee au ticket.
    * @return  la place associee au ticket
    */
  public Place getPlace() {
    return this.place;
  }
  
  /* SETTERS */
  
  /**
    * Modifie la date d'emission du ticket.
    * @param dateEmission_  l'objet de type date indiquant la nouvelle date 
    *                       d'emission du ticket
    */
  public void setDateEmission(Date dateEmission_) {
    this.dateEmission = dateEmission_;
  }
  
  /**
    * Modifie la date d'emission du ticket.
    * @param dateEmission_  chaine de caracteres decrivant la nouvelle date 
    *                       d'emission du ticket
    * @param heure_  l'heure d'emission (entier compris entre 0 et 23)
    * @throws FormatDateException  si la description de la date ne respecte pas 
    *                              le format souhaite
    */
  public void setDateEmission(String dateEmission_, int heure_) throws FormatDateException {
    if(heure_ < 0 || heure_ > 23)
      throw new FormatDateException("Mauvaise heure : " + heure_);
    if( (dateEmission = dateFormat.parse(dateEmission_+" "+heure_, new ParsePosition(0))) == null)
      throw new FormatDateException("Mauvaise date : " + dateEmission_);
  }
  
  /**
    * Modifie le numero du ticket.
    * @param noSerie_  le nouveau numero de serie du ticket
    */
  public void setNoSerie(int noSerie_) {
    this.noSerie = noSerie_;
  }
  
  /**
    * Modifie la representation associee au ticket.
    * @param rep_  la nouvelle representation associee au ticket
    */
  public void setRep(Representation rep_) {
    this.rep = rep_;
  }
  
  /**
    * Modifie la place associee au ticket.
    * @param place_  la nouvelle place associee au ticket
    */
  public void setPlace(Place place_) {
    this.place = place_;
  }
  
  /* OTHER METHODS */
  
  /**
    * Retourne une chaine de caracteres decrivant l'objet.
    * @return  une chaine de caracteres decrivant l'objet
    */
  public String toString() {
    String result = "Ticket (" + noSerie + ", " + getDateEmissionText() + "h)";
    return result;
  }
  
}
