/*
 * File : Theatre.java
 */

package modele;

import java.util.ArrayList;


/**
 * Classe representant un theatre.
 */
public class Theatre {
  
  /* CLASS VARIABLES */
  
  /* INSTANCE VARIABLES */
  
  /** Le nom du theatre. */
  private String nom;
  /** L'ensemble des zones du theatre. */
  private ArrayList<Zone> zones;
  
  /* CONSTRUCTORS */
  
  /**
    * Creation d'un nouveau theatre avec un nom donne.
    * @param nom_  le nom du theatre
    */
  public Theatre(String nom_) {
    nom = nom_;
    zones = new ArrayList<Zone>();
  }
  
  /**
    * Creation d'un nouveau theatre avec un nom et un ensemble de zones donnes.
    * @param nom_  le nom du  theatre
    * @param zones_  l'ensemble des zones du  theatre
    */
  public Theatre(String nom_, ArrayList<Zone> zones_) {
    nom = nom_;
    zones = zones_;
  }
  
  /* GETTERS */
  
  /**
    * Recupere le nom du theatre.
    * @return  le nom du  theatre
    */
  public String getNom() {
    return this.nom;
  }
  
  /**
    * Recupere l'ensemble de zones du theatre.
    * @return   une collection contenant l'ensemble de zones du theatre
    */
  public ArrayList<Zone> getZones() {
    return this.zones;
  }
  
  /* SETTERS */
  
  /**
    * Modifie le nom du theatre courant.
    * @param nom_  le nouveau nom du theatre
    */
  public void setNom(String nom_) {
    this.nom = nom_;
  }
  
  /**
    * Modifie l'ensemble de zones du theatre courant.
    * @param zones_  la nouvelle collection contenant l'ensemble de zones du theatre
    */
  public void setZones(ArrayList<Zone> zones_) {
    this.zones = zones_;
  }
  
  /* OTHER METHODS */
  
  /**
    * Retourne une chaine de caracteres decrivant l'objet.
    * @return  une chaine de caracteres decrivant l'objet
    */
  public String toString() {
    String result = "Theatre (\"" + nom + "\")";
    return result;
  }
  
}
