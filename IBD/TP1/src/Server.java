import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;
import java.util.Scanner;

public class Server {

    public static void main(String[] args) {
	// if(System.getSecurityManager() == null)
	//     System.setSecurityManager (new RMISecurityManager());
	try {
	    Room mainRoom = new Room("MainRoom");
	    RoomI h_stub = (RoomI)UnicastRemoteObject.exportObject(mainRoom, 0);

	    Registry registry = LocateRegistry.getRegistry();
	    registry.bind("rmi://localhost:1099/MainRoom", h_stub);
	    
	    System.out.println("Serveur prêt");
	    boolean exit = false;
	    Scanner sc = new Scanner(System.in);
	    int h;
	    do{
		System.out.println("Bonjour mon seigneur!\n MENU:");
		System.out.println("1 : Afficher Historique");
		System.out.println("2 : Afficher les clients");
		System.out.println("3: Quitter");
		h = sc.nextInt();
		if(h == 1) mainRoom.printHistory();
		else if(h == 2)mainRoom.printClients();
		else exit = true;
	    }while(!exit);
	}
	catch (Exception e) {
	    System.err.println("Error on server : " + e);
	    e.printStackTrace();
	    System.exit(1);
	}
    }

}