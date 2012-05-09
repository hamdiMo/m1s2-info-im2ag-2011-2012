package accesBD;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Vector;

import exceptions.CategorieException;
import exceptions.ExceptionConnexion;

import modele.Categorie;
import modele.Utilisateur;

public class BDCategories {

	public BDCategories () {
		
	}
	/**
	 * retourne la liste des catégories définies dans la bd
	 * @param Utilisateur
	 * @return Vector<Categorie>
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static Vector<Categorie> getCategorie (Utilisateur user)
	throws CategorieException, ExceptionConnexion {
		Vector<Categorie> res = new Vector<Categorie>();
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "select nomc, prix from LesCategories order by nomc";
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			while (rs.next()) {
				res.addElement(new Categorie (rs.getString(1), rs.getFloat(2)));
			}
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'interrogation des catégories.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		BDConnexion.FermerTout(conn, stmt, rs);
		return res;
	}

	/**
	 * ajoute une catégorie et son prix dans la bd
	 * @param Utilisateur
	 * @return Vector<Categorie>void
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
    public static void addCategorie (Utilisateur user, Categorie categorie)
	throws CategorieException, ExceptionConnexion {
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "insert into LESCATEGORIES values ('" + categorie.getCategorie()+"',"+ categorie.getPrix() + ")";
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'ajout d'une catégorie.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		BDConnexion.FermerTout(conn, stmt, rs);
	}

    public static void editCategorie (Utilisateur user, String oldCategorie, Categorie newCategorie)
	throws CategorieException, ExceptionConnexion {
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		requete = "UPDATE LESCATEGORIES SET nomC = '" + newCategorie.getCategorie() + "', prix = " + newCategorie.getPrix() + 
		    " WHERE nomC = '" + oldCategorie + "'" ;
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'edition d'une catégorie.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		BDConnexion.FermerTout(conn, stmt, rs);
    }


}