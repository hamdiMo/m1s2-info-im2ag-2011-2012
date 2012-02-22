import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;
import java.io.Serializable;
import java.util.Scanner;

public class Client implements ClientI, Serializable {

    /** Attributs */
    private String m_name;
    private RoomI m_mainRoom;
    private Scanner m_sc;
    private ClientI m_clientI;

    /** Consructeurs */
    public Client(RoomI mainRoom) throws Exception {
	m_mainRoom = mainRoom;
	m_sc = new Scanner(System.in);
	m_clientI = (ClientI)UnicastRemoteObject.exportObject(this, 0);
    }

    /** Accesseurs */
    public String getName() throws RemoteException {
	return m_name;
    }

    /** Methodes */
    public void notifyJoin(ClientI client) throws RemoteException {
	System.out.println(client.getName() + " est connecte");
    }
    
    public void notifyQuit(ClientI client) throws RemoteException {
	System.out.println(client.getName() + " est de connecte");
    }
    
    public void notify(Message message) throws RemoteException {
	System.out.println(message);
    }
    
    public void connect() throws RemoteException {
	String name;
	do{
	    System.out.println("veuillez entrer votre nom");
	    name = m_sc.nextLine();
	}while(!m_mainRoom.isNameAvailable(name));
	m_name = name;
	m_mainRoom.join(m_clientI);
    }
    
    public void chat() throws RemoteException {
	String line;
	System.out.println("-->");
	while((line = m_sc.nextLine()) != null){
	    m_mainRoom.post(m_clientI, line);
	}
    }

    public void run() throws RemoteException {
	connect();
	chat();
    }

    /** Methodes de classe */
    public static void main(String [] args) {

	try {
	    if (args.length != 1) {
		System.out.println("Usage: java HelloClient <server host>");
		return;
	    }
	    String host = args[0];

	    // Get remote object reference
	    Registry registry = LocateRegistry.getRegistry(host);
	    RoomI mainRoom = (RoomI) registry.lookup("rmi://localhost:1099/MainRoom");
	    Client client = new Client(mainRoom);
	    client.run();  
	} catch (Exception e) {
	    System.err.println("Error on client : " + e);
	}
    }
    
}