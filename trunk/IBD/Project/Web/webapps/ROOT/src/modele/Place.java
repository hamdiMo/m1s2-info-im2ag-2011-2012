/*
 * File : Place.java
 */

package modele;

import java.util.ArrayList;


/**
 * Classe representant une place dans le theatre.
 */
public class Place {
  
  /* CLASS VARIABLES */
  
  /* INSTANCE VARIABLES */
  
  /** Le numero de la place dans un rang. */
  private int noPlace;
  /** Le numero du rang de la place. */
  private int noRang;
  /** La zone associee a la place. */
  private Zone zone;
  /** L'ensemble de tickets emis pour cette place (differentes representations!) */
  private ArrayList<Ticket> tickets;
  
  /* CONSTRUCTORS */
  
  /**
    * Creation d'une nouvelle place avec un numero et un rang donnes.
    * @param noPlace_  le numero de la place dans le rang
    * @param noRang_  le numero du rang
    */
  public Place(int noPlace_, int noRang_) {
    noPlace = noPlace_;
    noRang = noRang_;
    zone = null;
    tickets = new ArrayList<Ticket>();
  }
  
  /**
    * Creation d'une nouvelle place avec un numero, un rang, une zone et un 
    * ensemble de tickets donnes.
    * @param noPlace_  le numero de la place dans le rang
    * @param noRang_  le numero du rang
    * @param zone_  la zone associee a la place
    * @param tickets_  l'ensemble de tickets emis pour cette place
    */
  public Place(int noPlace_, int noRang_, Zone zone_,
               ArrayList<Ticket> tickets_) {
    noPlace = noPlace_;
    noRang = noRang_;
    zone = zone;
    tickets = tickets_;
  }
  
  /* GETTERS */
  
  /**
    * Recupere le numero de la place dans son rang.
    * @return  le numero de la place
    */
  public int getNoPlace() {
    return this.noPlace;
  }
  
  /**
    * Recupere le numero du rang de la place.
    * @return  le numero du rang de la place
    */
  public int getNoRang() {
    return this.noRang;
  }
  
  /**
    * Recupere la zone contenant la place.
    * @return  la zone de la place
    */
  public Zone getZone() {
    return this.zone;
  }
  
  /**
    * Recupere l'ensemble de tickets emis pour la place.
    * @return  une collection de tickets emis pour la place
    */
  public ArrayList<Ticket> getTickets() {
    return this.tickets;
  }
  
  /* SETTERS */
  
  /**
    * Modifie le numero de la place courante.
    * @param noPlace_  le nouveau numero de place dans son rang
    */
  public void setNoPlace(int noPlace_) {
    this.noPlace = noPlace_;
  }
  
  /**
    * Modifie le rang de la place courante.
    * @param noRang_  le nouveau rang de la place
    */
  public void setNoRang(int noRang_) {
    this.noRang = noRang_;
  }
  
  /**
    * Modifie la zone contenant la place courante.
    * @param noRang_  la nouvelle zone de la place
    */
  public void setZone(Zone zone_) {
    this.zone = zone_;
  }
  
  /**
    * Modifie l'ensemble de tickets emis pour la place courante.
    * @param tickets_  la nouvelle collection de tickets emis pour la place
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
    String result = "Place (" + noPlace + ", " + noRang;
    if(zone != null)
      result = result + ", zone:" + zone.getNumZ();
    result = result + ")";
    return result;
  }
  
}
