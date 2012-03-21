/*
 * File : GestionAcces.java
 * Thanks to Richard GRIN for the original sourcecode
 */

package accesbd;

import java.io.IOException;
import java.sql.Connection;
import java.sql.SQLException;

/**
  * Controleur d'acces a la BD. 
  * Cette classe fournit les methodes pour obtenir et fermer une connexion, 
  * ainsi que celles pour effectuer commit et rollback. 
  * ATTENTION : MODIFIER POUR UTILISER LA NOTION DE POOL DE CONNEXIONS.
  */
public class GestionAcces {
  
  private static Connection connexion;
  
  /**
    * Obtenir la connexion active courante (une nouvelle connexion est creee si 
    * aucune connexion a la BD n'existe).
    * @return  une connexion active a la BD
    * @throws SQLException  s'il y a un probleme d'acces a la BD
    */
  public static Connection getConnexion() throws SQLException {
    if (connexion != null) {
      return connexion;
    }
    try {
      connexion = ConfigConnexion.getConnexion("connexion.cfg");
      connexion.setAutoCommit(false);
    }
    catch (ClassNotFoundException ex) {
      ex.printStackTrace();
    }
    catch (IOException ex) {
      ex.printStackTrace();
    }
    return connexion;
  }

  /**
    * Fermer la connexion active a la BD.
    * @throws SQLException  s'il y a un probleme d'acces a la BD
    */
  public static void fermeConnexion() throws SQLException {
    if (connexion != null) {
      connexion.close();
    }
    else {
      System.err.println("Aucune connexion existante");
    }
  }
  
  /**
    * Valider toutes les modifications de la transaction en cours.
    * @throws SQLException  s'il y a un probleme d'acces a la BD
    */
  public static void commit() throws SQLException {
    if (connexion != null) {
      connexion.commit();
    }
    else {
      System.err.println("Aucune connexion existante");
    }
  }
  
  /**
    * Annuler toutes les modifications de la transaction en cours.
    * @throws SQLException  s'il y a un probleme d'acces a la BD
    */
  public static void rollback() throws SQLException {
    if (connexion != null) {
      connexion.rollback();
    }
    else {
      System.err.println("Aucune connexion existante");
    }
  }

}
