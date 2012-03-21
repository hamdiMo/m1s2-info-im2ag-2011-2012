/*
 * File : Zone.java
 */

package modele;

import java.util.ArrayList;


/**
 * Classe representant un zone dans le theatre.
 */
public class Zone {
  
  /* CLASS VARIABLES */
  
  /* INSTANCE VARIABLES */
  
  /** Le numero de la zone. */
  private int numZ;
  /** La categorie de la zone. */
  private Categorie cat;
  /** L'ensemble de places dans cette zone. */
  private ArrayList<Place> places;
  /** Le theatre contenant cette zone. */
  private Theatre theatre;
  
  /* CONSTRUCTORS */
  
  /**
    * Creation d'une nouvelle zone dans le theatre, avec un numero donne.
    * @param numZ_  le numero de la zone
    */
  public Zone(int numZ_) {
    numZ = numZ_;
    cat = null;
    places = new ArrayList<Place>();
    theatre = null;
  }
  
  /**
    * Creation d'une nouvelle zone dans le theatre, avec un numero, une 
    * categorie, un ensemble de places et un theatre donnes.
    * @param numZ_  le numero de la zone
    * @param cat_  la categorie de la zone
    * @param places_  l'ensemble de places de la zone
    * @param theatre_  le theatre contenant cette zone
    */
  public Zone(int numZ_, Categorie cat_, ArrayList<Place> places_,
              Theatre theatre_) {
    numZ = numZ_;
    cat = cat_;
    places = places_;
    theatre = theatre_;
  }
  
  /* GETTERS */
  
  /**
    * Recupere le numero de la zone.
    * @return le numero de la zone
    */
  public int getNumZ() {
    return this.numZ;
  }
  
  /**
    * Recupere la categorie de la zone.
    * @return la categorie de la zone
    */
  public Categorie getCategorie() {
    return this.cat;
  }
  
  /**
    * Recupere le theatre qui contient cette zone.
    * @return le theatre contenant cette zone
    */
  public Theatre getTheatre() {
    return this.theatre;
  }
  
  /**
    * Recupere l'ensemble de places de cette zone.
    * @return une collection contenant l'ensemble des places de la zone
    */
  public ArrayList<Place> getPlaces() {
    return this.places;
  }
  
  /* SETTERS */
  
  /**
    * Modifie le numero de la zone.
    * @param numZ_ le nouveau numero de la zone
    */
  public void setNumZ(int numZ_) {
    this.numZ = numZ_;
  }
  
  /**
    * Modifie la categorie de la zone.
    * @param cat_ la nouvelle categorie de la zone
    */
  public void setCategorie(Categorie cat_) {
    this.cat = cat_;
  }
  
  /**
    * Modifie le theatre qui contient cette zone.
    * @param theatre_ le nouveat theatre contenant cette zone
    */
  public void setTheatre(Theatre theatre_) {
    this.theatre = theatre_;
  }
  
  /**
    * Modifie l'ensemble de places de cette zone.
    * @param places_  la nouvelle collection contenant l'ensemble des places 
    *                 de la zone
    */
  public void setPlaces(ArrayList<Place> places_) {
    this.places = places_;
  }
  
  /* OTHER METHODS */
  
  /**
    * Retourne une chaine de caracteres decrivant l'objet.
    * @return  une chaine de caracteres decrivant l'objet
    */
  public String toString() {
    String result = "Zone (" + numZ;
    if(cat != null)
      result = result + ", categorie:" + cat.getNomC();
    if(theatre != null)
      result = result + ", theatre:" + theatre.getNom();
    result = result + ")";
    return result;
  }
  
}
