/*
 * File : FormatDateException.java
 */

package modele;


/**
 * Classe modelisant l'exception a lever si la date indiquee dans une chaine de 
 * caracteres ne respecte pas le format souhaite.
 */
public class FormatDateException extends Exception {
  
  /**
    * Creation d'une nouvelle exception de type "format non valide".
    */
  public FormatDateException() {
  }

  /**
    * Creation d'une nouvelle exception de type "format non valide" avec un 
    * message d'erreur associe.
    * @param message  le message qui explique le probleme
    */
  public FormatDateException(String message) {
    super(message);
  }

  /**
    * Creation d'une nouvelle exception de type "format non valide" avec un 
    * message d'erreur associe et la cause de l'exception.
    * @param message  le message qui explique le probleme
    * @param cause  une exception qui est la cause du probleme
    */
  public FormatDateException(String message, Throwable cause) {
    super(message, cause);
  }

  /**
    * Creation d'une nouvelle exception de type "format non valide" avec la 
    * cause de l'exception.
    * @param cause  une exception qui est la cause du probleme
    */
  public FormatDateException(Throwable cause) {
    super(cause);
  }

}
