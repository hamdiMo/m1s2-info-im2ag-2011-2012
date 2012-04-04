/*
 * File : Saison.java
 */

package modele;

import java.util.ArrayList;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.text.ParsePosition;

/**
 * Classe representant une saison de spectacles.
 */
public class Saison {
  
  /* CLASS VARIABLES */
  private static SimpleDateFormat dateFormat;
  static {
      dateFormat = new SimpleDateFormat("MMM-yyyy", java.util.Locale.US);
  }
  
  /* INSTANCE VARIABLES */
  
  /** Le libelle decrivant la saison. */
  private String libelle;
  /** La date de debut de saison. */
  private Date debut;
  /** La date de fin de saison. */
  private Date fin;
  /** L'ensemble de spectacles prevus pour la saison. */
  private ArrayList<Spectacle> spectacles;
  
  /* CONSTRUCTORS */
  
  /**
    * Creation d'une nouvelle saison.
    */
  public Saison() {
    libelle = null;
    debut = null;
    fin = null;
    spectacles = new ArrayList<Spectacle>();
  }
  
  /**
    * Creation d'une nouvelle saison avec un libelle, une date de debut et une 
    * date de fin donnes.
    * @param libelle_  le libelle de la saison
    * @param debut_  la date de debut de saison
    * @param fin_  la date de fin de saison
    */
  public Saison(String libelle_, Date debut_, Date fin_) {
    libelle = libelle_;
    debut = debut_;
    fin = fin_;
    spectacles = new ArrayList<Spectacle>();
  }
  
  /**
    * Creation d'une nouvelle saison avec un libelle, une date de debut et une 
    * date de fin donnes.
    * @param libelle_  le libelle de la saison
    * @param debut_  la chaine de caracteres decrivant la date de debut de saison
    * @param fin_  la chaine de caracteres decrivant la date de fin de saison
    * @throws FormatDateException  si la description de la date ne respecte pas 
    * le format souhaite
    */
  public Saison(String libelle_, String debut_, String fin_) 
    throws FormatDateException {
    libelle = libelle_;
    if( (debut = dateFormat.parse(debut_, new ParsePosition(0))) == null)
      throw new FormatDateException();
    if( (fin = dateFormat.parse(fin_, new ParsePosition(0))) == null)
      throw new FormatDateException();
    spectacles = new ArrayList<Spectacle>();
  }
  
  /**
    * Creation d'une nouvelle saison avec un libelle, une date de debut, une 
    * date de fin et un ensemble de spectacles donnes.
    * @param libelle_  le libelle de la saison
    * @param debut_  la date de debut de saison
    * @param fin_  la date de fin de saison
    * @param spectacles_  l'ensemble de spectacles prevus pour la saison
    */
  public Saison(String libelle_, Date debut_, Date fin_,
                ArrayList<Spectacle> spectacles_) {
    libelle = libelle_;
    debut = debut_;
    fin = fin_;
    spectacles = spectacles_;
  }
  
  /**
    * Creation d'une nouvelle saison avec un libelle, une date de debut, une 
    * date de fin et un ensemble de spectacles donnes.
    * @param libelle_  le libelle de la saison
    * @param debut_  la chaine de caracteres decrivant la date de debut de saison
    * @param fin_  la chaine de caracteres decrivant la date de fin de saison
    * @param spectacles_  l'ensemble de spectacles prevus pour la saison
    * @throws FormatDateException  si la description de la date ne respecte pas 
    *                              le format souhaite
    */
  public Saison(String libelle_, String debut_, String fin_,
                ArrayList<Spectacle> spectacles_) throws FormatDateException {
    libelle = libelle_;
    if( (debut = dateFormat.parse(debut_, new ParsePosition(0))) == null)
      throw new FormatDateException();
    if( (fin = dateFormat.parse(fin_, new ParsePosition(0))) == null)
      throw new FormatDateException();
    spectacles = spectacles_;
  }
  
  /* GETTERS */
  
  /**
    * Recupere le libelle de la saison.
    * @return le libelle de la saison
    */
  public String getLibelle() {
    return this.libelle;
  }
  
  /**
    * Recupere la date de debut de saison.
    * @return l'objet de type date indiquant la date de debut de saison
    */
  public Date getDebut() {
    return this.debut;
  }
  
  /**
    * Recupere la date de fin de saison.
    * @return l'objet de type date indiquant la date de fin de saison
    */
  public Date getFin() {
    return this.fin;
  }
  
  /**
    * Recupere la date de debut de saison.
    * @return la chaine de caracteres decrivant la date de debut de saison
    */
  public String getDebutText() {
    return (dateFormat.format(this.debut));
  }
  
  /**
    * Recupere la date de fin de saison.
    * @return la chaine de caracteres decrivant la date de fin de saison
    */
  public String getFinText() {
    return (dateFormat.format(this.fin));
  }
  
  /**
    * Recupere l'ensemble de spectacles prevus pour la saison.
    * @return  une collection contenant les spectacles prevus pour la saison
    */
  public ArrayList<Spectacle> getSpectacles() {
    return this.spectacles;
  }
  
  /* SETTERS */
  
  /**
    * Modifie le libelle de la saison courante.
    * @param libelle_  le nouveau libelle de la saison
    */
  public void setLibelle(String libelle_) {
    this.libelle = libelle_;
  }
  
  /**
    * Modifie la date de debut de saison courante.
    * @param debut_  l'objet de type date indiquant la nouvelle date de debut 
    *                de saison
    */
  public void setDebut(Date debut_) {
    this.debut = debut_;
  }
  
  /**
    * Modifie la date de fin de saison courante.
    * @param fin_ l'objet de type date indiquant la nouvelle date de fin de saison
    */
  public void setFin(Date fin_) {
    this.fin = fin_;
  }
  
  /**
    * Modifie la date de debut de saison courante.
    * @param debut_ la chaine de caracteres decrivant la nouvelle date de debut 
    *               de saison
    * @throws FormatDateException  si la description de la date ne respecte pas 
    *                              le format souhaite
    */
  public void setDebut(String debut_) throws FormatDateException {
    if( (debut = dateFormat.parse(debut_, new ParsePosition(0))) == null)
      throw new FormatDateException();
  }
  
  /**
    * Modifie la date de fin de saison courante.
    * @param fin_  la chaine de caracteres decrivant la nouvelle date de fin de 
    *              saison
    * @throws FormatDateException  si la description de la date ne respecte pas 
    *                              le format souhaite
    */
  public void setFin(String fin_) throws FormatDateException {
    if( (fin = dateFormat.parse(fin_, new ParsePosition(0))) == null)
      throw new FormatDateException();
  }
  
  /**
    * Modifie l'ensemble de spectacles prevus pour la saison courante.
    * @param  spectacles_  la nouvelle collection contenant les spectacles 
    * prevus pour la saison
    */
  public void setSpectacles(ArrayList<Spectacle> spectacles_) {
    this.spectacles = spectacles_;
  }
  
  /* OTHER METHODS */
  
  /**
    * Retourne une chaine de caracteres decrivant l'objet.
    * @return  une chaine de caracteres decrivant l'objet
    */
  public String toString() {
    String result = "Saison (\"" + libelle + "\", " + 
        getDebutText() + ", " + getFinText() + ")";
    return result;
  }
  
}
