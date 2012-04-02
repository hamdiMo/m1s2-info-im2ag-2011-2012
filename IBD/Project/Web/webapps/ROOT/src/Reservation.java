import modele.*;
import java.lang.String;

public class Reservation {
    Representation m_representation;
    Place m_place;

    public Reservation(Representation r, Place p){
      m_representation = r;
      m_place = p;
    }

    public Representation getRepresentation(){ return m_representation; }
    public Place getPlace(){ return m_place; }

    public String toString(){
      return new String("Réservation de la "+ m_representation.toString() + " à la " +m_place.toString());
    }
}