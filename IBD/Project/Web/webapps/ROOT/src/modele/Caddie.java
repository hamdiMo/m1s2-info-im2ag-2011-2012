package modele;
import java.util.ArrayList;
import java.util.ListIterator;


/**
 * Classe representant un caddie.
 */
public class Caddie {

    /** L'ensemble des reservations de la session courante. */
    ArrayList<Reservation> m_reservations;

    /** Creation d'un nouveaux caddie vide. */
    public Caddie(){
        m_reservations = new ArrayList<Reservation>();
    }

    /**
     * Ajoute une reservation au caddie.
     * @param r un objet de type Reservation à ajouter au caddie
     */
    public void addReservation(Reservation r){
      m_reservations.add(r);
    }

    /**
     * Supprime une reservation du caddie.
     * @param r un objet de type Reservation à supprimer du caddie
     */
    public void removeReservation(Reservation r){
        for(int i = 0; i < m_reservations.size(); i++){
            if(m_reservations.get(i).equals(r)){
                m_reservations.remove(i);
            }
        }
    }
    
   /**
    * Recupere la liste des reservations du caddie. 
    * @return  une collection de reservations d'un caddie
    */
    public ArrayList<Reservation> getReservations(){
      return m_reservations;
    }

   /**
    * Retourne une chaine de caracteres decrivant l'objet.
    * @return  une chaine de caracteres decrivant l'objet
    */
    public String toString(){
      ListIterator<Reservation> it = m_reservations.listIterator();
      String s = new String();
      while(it.hasNext()){
	s += it.next().toString()+"\n";
      }
      return s;
    }
}

