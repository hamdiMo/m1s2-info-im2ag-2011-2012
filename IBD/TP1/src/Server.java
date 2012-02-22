package server;

import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;

public class Server {

    public static void main(String[] args) {
	try {
	    Room mainRoom = new Room("MainRoom");
	    RoomI h_stub = (RoomI)UnicastRemoteObject.exportObject(mainRoom, 0);

	    Registry registry = LocateRegistry.getRegistry();
	    registry.bind("MainRoom", h_stub);
	    
	    System.out.println("Serveur prêt");
	}
	catch (Exception e) {
	    System.err.println("Error on server : " + e);
	    e.printStackTrace();
	    System.exit(1);
	}
    }

}