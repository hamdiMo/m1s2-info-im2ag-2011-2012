/*
 * File : Spectacle.java
 */

package modele;

import java.util.ArrayList;


/**
 * Classe representant un spectacle prevu pour une saison.
 */
public class Spectacle {
  
  /* CLASS VARIABLES */
  
  /* INSTANCE VARIABLES */
  
  /** Le numero du spectacle. */
  private int numS;
  /** Le nom decrivant le spectacle. */
  private String nomS;
  /** L'ensemble de representations prevues pour le spectacle. */
  private ArrayList<Representation> representations;
  /** La saison du spectacle. */
  private Saison saison;
  
  /* CONSTRUCTORS */
  
  /**
    * Creation d'un nouveau spectacle avec un numero et un nom donnes.
    * @param numS_  le numero du spectacle
    * @param nomS_  le nom du spectacle
    */
  public Spectacle(int numS_, String nomS_) {
    numS = numS_;
    nomS = nomS_;
    representations = new ArrayList<Representation>();
    saison = null;
  }
  
  /**
    * Creation d'un nouveau spectacle avec un numero, un nom, un ensemble de 
    * representations et une saison donnes.
    * @param numS_  le numero du spectacle
    * @param nomS_  le nom du spectacle
    * @param representations_  l'ensemble de representations prevues pour le 
    *                          spectacle
    * @param saison  la saison du spectacle
    */
  public Spectacle(int numS_, String nomS_,
                   ArrayList<Representation> representations_, Saison saison_) {
    numS = numS_;
    nomS = nomS_;
    representations = representations_;
    saison = saison_;
  }
  
  /* GETTERS */
  
  /**
    * Recupere le nom du spectacle.
    * @return  le nom du spectacle
    */
  public String getNomS() {
    return this.nomS;
  }
  
  /**
    * Recupere le numero du spectacle.
    * @return  le numero du spectacle
    */
  public int getNumS() {
    return this.numS;
  }
  
  /**
    * Recupere l'ensemble de representations prevues pour le spectacle.
    * @return   une collection contenant l'ensemble de representations prevues 
    *           pour le spectacle
    */
  public ArrayList<Representation> getRepresentations() {
    return this.representations;
  }
  
  /**
    * Recupere la saison du spectacle.
    * @return  la saison du spectacle
    */
  public Saison getSaison() {
    return this.saison;
  }
  
  /* SETTERS */
  
  /**
    * Modifie le nom du spectacle courant.
    * @param nomS_  le nouveau nom du spectacle
    */
  public void setNomS(String nomS_) {
    this.nomS = nomS_;
  }
  
  /**
    * Modifie le numero du spectacle courant.
    * @param numS_  le nouveau numero du spectacle
    */
  public void setNumS(int numS_) {
    this.numS = numS_;
  }
  
  /**
    * Modifie l'ensemble de representations prevues pour le spectacle courant.
    * @param representations_   la nouvelle collection contenant l'ensemble de 
    *                           representations prevues pour le spectacle
    */
  public void setRepresentations(ArrayList<Representation> representations_) {
    this.representations = representations_;
  }
  
  /**
    * Modifie la saison du spectacle courant.
    * @param saison_  la nouvelle saison du spectacle
    */
  public void setSaison(Saison saison_) {
    this.saison = saison_;
  }
  
  /* OTHER METHODS */
  
  /**
    * Retourne une chaine de caracteres decrivant l'objet.
    * @return  une chaine de caracteres decrivant l'objet
    */
  public String toString() {
    String result = "Spectacle (" + numS + ", \"" + nomS + "\"";
    if(saison != null)
      result = result + ", saison:" + saison.getLibelle();
    result = result + ")";
    return result;
  }
  
}
