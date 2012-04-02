import java.util.ArrayList;
import java.util.ListIterator;
public class Caddie {
    ArrayList<Reservation> m_reservations;
    public Caddie(){
      
    }


    public void addReservation(Reservation r){
      m_reservations.add(r);
    }

//     public boolean validerCaddie(){
//     
//     }
    
    public ArrayList<Reservation> getReservations(){
      return m_reservations;
    }

    public String toString(){
      ListIterator<Reservation> it = m_reservations.listIterator();
      String s = new String();
      while(it.hasNext()){
	s += it.next().toString()+"\n";
      }
      return s;
    }
}

