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

//     public boolean validerCaddie(){
//     
//     }

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

