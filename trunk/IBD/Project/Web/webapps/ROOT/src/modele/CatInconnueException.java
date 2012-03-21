/*
 * File : CatInconnueException.java
 */

package modele;


/**
 * Classe modelisant l'exception a lever si le nom utilise n'identifie aucune 
 * categorie.
 */
public class CatInconnueException extends Exception {
  
  /**
    * Creation d'une nouvelle exception de type "categorie inconnue".
    */
  public CatInconnueException() {
  }

  /**
    * Creation d'une nouvelle exception de type "categorie inconnue" avec un 
    * message d'erreur associe.
    * @param message  le message qui explique le probleme
    */
  public CatInconnueException(String message) {
    super(message);
  }

  /**
    * Creation d'une nouvelle exception de type "categorie inconnue" avec un 
    * message d'erreur associe et la cause de l'exception.
    * @param message  le message qui explique le probleme
    * @param cause  une exception qui est la cause du probleme
    */
  public CatInconnueException(String message, Throwable cause) {
    super(message, cause);
  }

  /**
    * Creation d'une nouvelle exception de type "categorie inconnue" avec la 
    * cause de l'exception.
    * @param cause  une exception qui est la cause du probleme
    */
  public CatInconnueException(Throwable cause) {
    super(cause);
  }

}
