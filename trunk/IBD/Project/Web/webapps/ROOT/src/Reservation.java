import modele.*;
import java.lang.String;

/**
 * Classe representant une reservation.
 */
public class Reservation {
    /** La representation pour laquelle on reserve une place */
    Representation m_representation;
    /** La place réservé */
    Place m_place;

  /**
    * Creation d'une nouvelle reservation avec une representant et une place donnes.
    * @param r  la representation pour laquelle on souhaite avoir une reservation
    * @param p  la place qu'on veut reserver
    */
    public Reservation(Representation r, Place p){
      m_representation = r;
      m_place = p;
    }

  /**
    * Recupere la representation de la reservation.
    * @return  la representation de la reservation
    */
    public Representation getRepresentation(){ return m_representation; }  

  /**
    * Recupere la place de la reservation.
    * @return  la place de la reservation.
    */
    public Place getPlace(){ return m_place; }

  /**
    * Retourne une chaine de caracteres decrivant l'objet.
    * @return  une chaine de caracteres decrivant l'objet
    */
    public String toString(){
        return new String("Reservation (" + m_representation.toString() + ", " + m_place.toString() + ")");
    }
}