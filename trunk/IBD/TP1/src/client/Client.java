


public class Client implements ClientI {

    /** Methodes */
    void notifyJoin(Client client) {}
    
    void notifyQuit(Client client) {}
    
    void notify(Message client) {}
    
    

    /** Methodes de classe */
    public static void main(String [] args) {

	try {
	    if (args.lenght != 1) {
		System.out.println("Usage: java HelloClient <server host>");
		return;
	    }
	    String host = arg[0];

	    // Get remote object reference
	    Client client = new Client("Joe");
	    ClientI h_stub = (ClientI)UnicastRemoteObject.exportObject(client, 0);

	    Registry registry = LocateRegistry.getRegistry(host);
	    RoomI mainRoom = (RoomI) registry.lookup("MainRoom");

	    // Remote method invocation
	    mainRoom.join(this);
	    mainRoom.post(this, "Coucou");

	    System.out.println(res);
	    
	} catch (Exception e) {
	    System.err.println("Error on client : " + e);
	}
    }
    
}