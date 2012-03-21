/*
 * File : ConfigConnexion.java
 * Thanks to Richard GRIN for the original sourcecode
 */

package accesbd;

import java.sql.*;
import java.io.*;
import java.util.*;
import java.net.URL;

/**
  * Classe utilitaire, permettant d'ouvrir une nouvelle connexion a la BD.
  */
public class ConfigConnexion {

  private ConfigConnexion() { }

  /**
    * Obtenir une nouvelle connexion a la BD, en fonction des parametres 
    * contenus dans un fichier de configuration.
    * @param fichierConf_  la parcours vers le fichier de configuration
    * @return  une nouvelle connexion a la BD
    * @throws IOException  en cas de problemes avec le fichier de proprietes
    * @throws ClassNotFoundException  si la classe du pilote jdbc ne peut pas 
    *                                 etre identifiee
    * @throws SQLException  s'il y a un probleme d'acces a la BD
    */
  public static Connection getConnexion(String fichierConf_)
    throws IOException, ClassNotFoundException, SQLException {
    
    Properties p = new Properties();
    InputStream is = null;
    
    try {
      is = new FileInputStream(fichierConf_);
      p.load(is);
      String driver = p.getProperty("driver");
      String url = "jdbc:";
      url = url + p.getProperty("sousproto") + ":";
      url = url + "@" + p.getProperty("machine") + ":";
      url = url + p.getProperty("port") + ":";
      url = url + p.getProperty("nombd");
      String utilisateur = p.getProperty("utilisateur");
      String mdp = p.getProperty("mdp");
      Class.forName(driver);
      return DriverManager.getConnection(url, utilisateur, mdp);
    }
    finally {
      if (is != null) {
        is.close();
      }
    }
  }

  /**
    * Obtenir une nouvelle connexion a la BD, en fonction des parametres 
    * contenus dans un fichier de configuration, du nom utilisateur et du mdp fournis.
    * @param fichierConf_  la parcours vers le fichier de configuration
    * @param utilisateur  le nom utilisateur de la BD
    * @param mdp  le mot de passe de l'utilisateur
    * @return  une nouvelle connexion a la BD
    * @throws IOException  en cas de problemes avec le fichier de proprietes
    * @throws ClassNotFoundException  si la classe du pilote jdbc ne peut pas 
    *                                 etre identifiee
    * @throws SQLException  s'il y a un probleme d'acces a la BD
    */
  public static Connection getConnexion(String fichierConf_,
                                         String utilisateur,
                                         String mdp)
    throws IOException, ClassNotFoundException, SQLException {
    
    Properties p = new Properties();
    URL u = ConfigConnexion.class.getResource(fichierConf_);
    BufferedInputStream is = null;
    
    try {
      is = new BufferedInputStream(u.openStream());
      p.load(is);
      String driver = p.getProperty("driver");
      String url = "jdbc:";
      url = url + p.getProperty("sousproto") + ":";
      url = url + "@" + p.getProperty("machine") + ":";
      url = url + p.getProperty("port") + ":";
      url = url + p.getProperty("nombd");
      Class.forName(driver);
      return DriverManager.getConnection(url, utilisateur, mdp);
    }
    finally {
      if (is != null) {
        is.close();
      }
    }
  }
  
}
