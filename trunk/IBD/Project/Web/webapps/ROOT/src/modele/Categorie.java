/*
 * File : Categorie.java
 */

package modele;

import java.util.ArrayList;


/**
 * Classe representant une categorie tarifaire.
 */
public class Categorie {
  
  /* CLASS VARIABLES */
  
  /* INSTANCE VARIABLES */
  
  /** Le nom de la categorie. */
  private String nomC;
  /** Le prix pour la categorie. */
  private double prix;
  /** L'ensemble de zones associees a la categorie. */
  private ArrayList<Zone> zones;
  
  /* CONSTRUCTORS */
  
  /**
    * Creation d'une nouvelle categorie pour un nom et un prix donnes.
    * @param nomC_  le nom de la categorie
    * @param prix_  le prix associe a la categorie
    * @throws CatInconnueException  si le nom fourni n'est pas un nom de 
    *                               categorie valide
    */
  public Categorie(String nomC_, double prix_) throws CatInconnueException {
    if(verifNomCat(nomC_))
      nomC = nomC_;
    else
      throw new CatInconnueException("Categorie \"" + nomC_ + "\" inconnue!");
    prix = prix_;
    zones = new ArrayList<Zone>();
  }
  
  /**
    * Creation d'une nouvelle categorie pour un nom, un prix et un ensemble de 
    * zones donnes.
    * @param nomC_  le nom de la categorie
    * @param prix_  le prix associe a la categorie
    * @param zones_  la collection de zones associees a cette categorie
    * @throws CatInconnueException  si le nom fourni n'est pas un nom de 
    *                               categorie valide
    */
  public Categorie(String nomC_, double prix_, ArrayList<Zone> zones_) 
      throws CatInconnueException {
    if(verifNomCat(nomC_))
      nomC = nomC_;
    else
      throw new CatInconnueException("Categorie \"" + nomC_ + "\" inconnue!");
    prix = prix_;
    zones = zones_;
  }
  
  /* GETTERS */
  
  /**
    * Recupere le nom de la categorie.
    * @return  le nom de la categorie
    */
  public String getNomC() {
    return this.nomC;
  }
  
  /**
    * Recupere le prix de la categorie.
    * @return  le prix de la categorie
    */
  public double getPrix() {
    return this.prix;
  }
  
  /**
    * Recupere l'ensemble de zones associees a cette categorie.
    * @return  une collection de zones associees a la categorie
    */
  public ArrayList<Zone> getZones() {
    return this.zones;
  }
  
  /* SETTERS */
  
  /**
    * Modifie le nom de la categorie courante.
    * @param nomC_  le nouveau nom pour la categorie
    */
  public void setNomC(String nomC_) throws CatInconnueException {
    if(verifNomCat(nomC_))
      this.nomC = nomC_;
    else
      throw new CatInconnueException("Categorie \"" + nomC_ + "\" inconnue!");
  }
  
  /**
    * Modifie le prix de la categorie courante.
    * @param prix_  le nouveau prix pour la categorie
    */
  public void setPrix(double prix_) {
    this.prix = prix_;
  }
  
  /**
    * Modifie l'ensemble de zones associees a la categorie courante.
    * @param nomC_  une nouvelle collection de zones
    */
  public void setZones(ArrayList<Zone> zones_) {
    this.zones = zones_;
  }
  
  /* OTHER METHODS */
  
  private boolean verifNomCat(String nomC_) {
    return (nomC_.equalsIgnoreCase("ORCHESTRE") ||
            nomC_.equalsIgnoreCase("BALCON") ||
            nomC_.equalsIgnoreCase("POULAILLER"));
  }
  
  /**
    * Retourne une chaine de caracteres decrivant l'objet.
    * @return  une chaine de caracteres decrivant l'objet
    */
  public String toString() {
    String result = "Categorie (" + nomC + ", " + prix + ")";
    return result;
  }
  
}
