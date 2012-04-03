/*
 * File : GestionRequete.java
 */
 
package accesbd;

import java.sql.*;
import java.util.Date;
import java.util.ArrayList;
import java.text.SimpleDateFormat;

import modele.*;


/**
 * Classe pour la gestion des requetes. 
 * Cette classe contient toutes les methodes associees aux differentes requetes 
 * necessaires a l'application.
 */
public class GestionRequete {

    /* CLASS VARIABLES */
    private static SimpleDateFormat dateFormat, timeFormat, dateAndTimeFormat, dateAndTimeFormatBD;
    static {
        dateFormat = new SimpleDateFormat("dd-MMM-yyyy"); 
        timeFormat = new SimpleDateFormat("HH");
        dateAndTimeFormat = new SimpleDateFormat("dd-MMM-yyyy HH");
        dateAndTimeFormatBD = new SimpleDateFormat("dd-MMM-yyyy hh:mm:ss aa");
    }

    /**
     * Requete permettant de recuperer un spectacle depuis la BD.
     * @param numS_  l'identificateur unique d'un spectacle
     * @return  un objet de type spectacle spectacle, representant les donnees 
     *          associees a l'identificateur dans la BD
     * @throws SQLException  si aucun spectacle avec l'ID fourni n'existe, 
     *                       ou s'il y a un probleme d'acces a la BD
     */
    public static Spectacle trouveSpectacle(int numS_) throws SQLException {
        try {
            Connection conn = GestionAcces.getConnexion();
            Statement stmt = conn.createStatement();
            String req = "select nomS from LesSpectacles where numS = " + numS_;
            ResultSet rset = stmt.executeQuery(req);
            if(rset.next()) {
                Spectacle result = new Spectacle(numS_, rset.getString("nomS"));
                stmt.close();
                rset.close();
                // le commit ne sert ici qu'a liberer les ressources (verrous..)
                // reservees par la requete
                GestionAcces.commit();
                return result;
            }
            else {
                stmt.close();
                rset.close();
                GestionAcces.rollback();
                throw new SQLException("Aucun spectacle avec numS = " + numS_);
            }
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        }
    
    }
  
    /**
     * Requete permettant de recuperer toutes les spectacles existants dans la BD.
     * @return  une collection de spectacles
     * @throws SQLException  s'il y a un probleme d'acces a la BD
     */
    public static ArrayList<Spectacle> trouveSpectacles() throws SQLException {
        try {
            ArrayList<Spectacle> result = new ArrayList<Spectacle>();
            Connection conn = GestionAcces.getConnexion();
            Statement stmt = conn.createStatement();
            String req = "select numS, nomS from LesSpectacles";
            ResultSet rset = stmt.executeQuery(req);
            while(rset.next()) {
                Spectacle s = new Spectacle(rset.getInt("numS"), rset.getString("nomS"));
                result.add(s);
            }
            stmt.close();
            rset.close();
            GestionAcces.commit();
            return result;
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        }
    }
  
    /**
     * Requete permettant d'ajouter une nouvelle representation dans la BD, 
     * associee a un spectacle existant.
     * @param r_  l'objet de type Representation a ajouter dans la BD
     * @return  le nombre de lignes ajoutees dans la BD
     * @throws SQLException  si la representation n'a pas de spectacle associe, 
     *                       ou s'il y a un probleme d'acces a la BD
     */
    public static int ajouteRepresentation(Representation r_) throws SQLException {
        try {
            if (r_.getSpectacle() == null) {
                throw new SQLException("Pas de spectacle associe a la representation donnee " + r_);
            }
            return ajouteRepresentation(r_.getSpectacle().getNumS(), r_); 
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        }
    }
  
    /**
     * Requete permettant d'ajouter une nouvelle representation dans la BD, 
     * en connaissant l'identifiant du spectacle associe.
     * @param numS_  l'identifiant du spectacle associe a la representation
     * @param r_  l'objet de type Representation a ajouter dans la BD
     * @return  le nombre de lignes ajoutees dans la BD
     * @throws SQLException  s'il y a un probleme d'acces a la BD
     */
    public static int ajouteRepresentation(int numS_, Representation r_) 
        throws SQLException {
        try {
            Connection conn = GestionAcces.getConnexion();
            Statement stmt = conn.createStatement();
            String req = "insert into LesRepresentations values (" + 
                numS_ + "," + r_.getDateRepText() + ")";
            int ret = stmt.executeUpdate(req);
            stmt.close();
            GestionAcces.commit();
            return ret;
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        }
    }

    public static ArrayList<Representation> trouveRepresentations(Spectacle s) throws SQLException {
        try {
            ArrayList<Representation> result = new ArrayList<Representation>();
            Connection conn = GestionAcces.getConnexion();
            Statement stmt = conn.createStatement();
            String req = "select dateRep from LesRepresentations where numS = " + s.getNumS();
            ResultSet rset = stmt.executeQuery(req);
            while (rset.next())
                result.add(new Representation(rset.getDate("dateRep")));
            stmt.close();
            rset.close();
            GestionAcces.commit();
            return result;
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        }
    }

    public static Representation trouveRepresentation(Spectacle s,  String d, int h) throws SQLException {
        try {
            if(h < 0 || h > 23) throw new SQLException("Mauvaise heure : " + h);
            boolean pm = h >= 12;
            if (pm) h -= 12;
            String formatTime = new String(d+" "+h+":00:00 ");
            if (pm) formatTime += "pm"; else formatTime += "am";

            Connection conn = GestionAcces.getConnexion();
            Statement stmt = conn.createStatement();
            String req = "select * from LesRepresentations where numS="+s.getNumS()+" and dateRep='"+formatTime+"'";
            ResultSet rset = stmt.executeQuery(req);
            rset.next();
            Representation r = new Representation(rset.getDate("dateRep"), s, new ArrayList<Ticket>());
            stmt.close();
            rset.close();
            GestionAcces.commit();
            return r;
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        }
    }

    public static ArrayList<Zone> trouveZonesLibres(Representation r) throws SQLException {
        try {
            Connection conn = GestionAcces.getConnexion();
            Statement stmt = conn.createStatement();
            String req = "select distinct LP.numZ, LC.nomC, LC.prix from LesPlaces LP, LesZones LZ, LesCategories LC"
                + " where LP.numZ = LZ.numZ"
                + " and LZ.nomC=LC.nomC" 
                + " and (LP.noPlace, LP.noRang) not in"
                + " (select noPlace, noRang from LesTickets where dateRep ='" + r.getDateRepText() + "')";
            ResultSet rset = stmt.executeQuery(req);
            ArrayList<Zone> result = new ArrayList<Zone>();
            while(rset.next()) 
                try {
                    result.add(new Zone(rset.getInt("numZ"),
                                        new Categorie(rset.getString("nomC"), rset.getDouble("prix")),
                                        new ArrayList<Place>(), null));
                } catch (CatInconnueException e2) {}
            stmt.close();
            rset.close();
            GestionAcces.commit();
            return result;
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        } 
    }

    public static ArrayList<Place> trouvePlacesDisponibles(Representation r) throws SQLException {
        try {
            ArrayList<Place> result = new ArrayList<Place>();
            Connection conn = GestionAcces.getConnexion();
            Statement stmt = conn.createStatement();
            String req = "select noPlace, noRang from LesPlaces where (noPlace, noRang) not in (select noPlace, noRang from LesTickets where dateRep ='" + r.getDateRepText() + "')";
            ResultSet rset = stmt.executeQuery(req);
            while(rset.next()) result.add(new Place(rset.getInt("noPlace"), rset.getInt("noRang")));
            stmt.close();
            rset.close();
            GestionAcces.commit();
            return result;
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        }
    }

    public static Ticket reserverTicket(Representation r, Zone z) throws SQLException {
        try {
            Connection conn = GestionAcces.getConnexion();
            Statement stmt = conn.createStatement();
            ResultSet rset = stmt.executeQuery("select noPlace, noRang from LesPlaces where numZ="
                                               + z.getNumZ()
                                               + " and (noPlace, noRang) not in "
                                               + "(select noPlace, noRang from LesTickets where dateRep ='" 
                                               + r.getDateRepText() 
                                               + "')");
            rset.next();
            return reserverTicket(r, new Place(rset.getInt("noPlace"), rset.getInt("noRang"), z, new ArrayList<Ticket>()));
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        }
    }

    public static Ticket reserverTicket(Representation r, Place p) throws SQLException {
        try {
            Connection conn = GestionAcces.getConnexion();
            Statement stmt = conn.createStatement();
            ResultSet rset = stmt.executeQuery("Select count(*) as Tralala from LesTickets");
            rset.next();
            int nbSerie = rset.getInt("Tralala")+1;

            Date dateEmission = new Date();
            Ticket ticket = new Ticket(nbSerie, dateEmission, r, p);
            String req = "insert into LesTickets values ('" + nbSerie
                + "','" + r.getSpectacle().getNumS()
                + "','" + r.getDateRepText()
                + "','" + p.getNoPlace()
                + "','" + p.getNoRang()
                + "','" + dateAndTimeFormatBD.format(dateEmission)
                + "','71')";
            rset = stmt.executeQuery(req);
            stmt.close();
            rset.close();
            GestionAcces.commit();
            return ticket;
        } catch (SQLException e) {
            GestionAcces.rollback();
            throw e;
        }
    }

}
