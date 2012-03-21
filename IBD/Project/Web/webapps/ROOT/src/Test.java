/*
 * File : Test.java
 */

import java.util.ArrayList;
import java.sql.SQLException;
import modele.*;
import accesbd.*;


public class Test {
  
    public static void main(String[] args) throws SQLException {
    
	/*  /!\ IMPORTANT /!\
	 *  Consultez la javadoc (fichier 'index.html' du repertoire 'doc') 
	 *  pour avoir plus d'info sur les methodes existantes et leur signatures!
	 */
    
	Saison saison = new Saison();
	boolean tran_1_ok = false;
    
	// TRANSACTION 1 :
	try {
	    // Trouver tous les spectacles de la saison en cours dans la BD...
	    saison.setSpectacles( GestionRequete.trouveSpectacles() );
	    // ...et les afficher
	    System.out.println("Spectacles : ");
	    for(int i=0; i<saison.getSpectacles().size(); i++) {
		System.out.println(saison.getSpectacles().get(i));
	    }
	    System.out.println();
	    tran_1_ok = true;
	}
	catch(SQLException e) {
	    System.err.println("Erreur oracle : " + e.getErrorCode() + e.getMessage());
	}
    
	if(tran_1_ok) {
      
	    // TRANSACTION 2 :
	    try {
		// Choisir le premier spectacle
		Spectacle s1 = saison.getSpectacles().get(0);
		// Creer une nouvelle representation pour ce spectacle
		Representation r1 = new Representation("31-12-2007", 21, s1, new ArrayList<Ticket>());
		System.out.println(r1);
		// Ajouter la representation a la BD
		int count = GestionRequete.ajouteRepresentation(r1);
		System.out.println("" + count + " ligne(s) ajoutee(s)");
	    }
	    catch(FormatDateException e1) {
		System.err.println("La date indiquee pour la representation ne respecte pas le bon format.");
		System.err.println("La transaction est annulee.");
		e1.printStackTrace();
	    }
	    catch(SQLException e2) {
		System.err.println("Erreur oracle : " + e2.getErrorCode() + e2.getMessage());
	    }
      
	}
	else {
	    System.err.println("Il est impossible d'effectuer la 2eme transaction " +
			       "puisque la premiere n'a pas abouti.");
	}
    
	// TRANSACTION 3 :
	try {
	    // Creer une nouvelle representation (spectacle inconnu)
	    Representation r2 = new Representation("02-01-2008", 22);
	    System.out.println(r2);
	    // Ajouter la representation a la BD, pour le spectacle 104 (existe-t-il ?)
	    int count = GestionRequete.ajouteRepresentation(104, r2);
	    System.out.println("" + count + " ligne(s) ajoutee(s)");
	}
	catch(FormatDateException e1) {
	    System.err.println("La date indiquee pour la representation ne respecte pas le bon format.");
	    System.err.println("La transaction sera annulee.");
	    e1.printStackTrace();
	}
	catch(SQLException e2) {
	    System.err.println("Erreur oracle : " + e2.getErrorCode() + e2.getMessage());
	}
	finally {
	    GestionAcces.fermeConnexion();
	}
    
    }
  
}
