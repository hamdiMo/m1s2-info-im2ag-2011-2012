import java.util.List;
import java.util.Stack;
import java.util.LinkedList;
import java.util.Iterator;
import java.rmi.Remote;
import java.rmi.RemoteException;

public class Room implements RoomI {
    
    /** Attributs */
    private List<ClientI> m_clients;
    private Stack<Message> m_historic;
    private String m_name;
    
    /** Constructeur */
    Room(String name) {
	m_clients = new LinkedList<ClientI>();
	m_historic = new Stack<Message>();
	m_name = name;
    }

    /** Methodes */
    public void join(ClientI client) throws RemoteException {
	Iterator<ClientI> it = m_clients.listIterator();
	while (it.hasNext()) {
	    ClientI tmp = it.next();
	    tmp.notifyJoin(client);
	    client.notifyJoin(tmp);
	}
	m_clients.add(client);
	client.notifyJoin(client);
    }

    public void quit(ClientI client) throws RemoteException {
	m_clients.remove(client);
	Iterator<ClientI> it = m_clients.listIterator();
	while (it.hasNext()) it.next().notifyQuit(client);
    }

    public void post(ClientI client, String text) throws RemoteException {
	Message message = new Message(client.getName(), text);
	m_historic.add(message);
	Iterator<ClientI> it = m_clients.listIterator();
	while (it.hasNext()) it.next().notify(message);
    }

    public void printHistory(){
	Iterator<Message> it = m_historic.listIterator();
	while (it.hasNext()) System.out.println(it.next());
    }

    public void printClients() throws RemoteException {
	Iterator<ClientI> it = m_clients.listIterator();
	while (it.hasNext()) System.out.println(it.next().getName());
    }

    public boolean isNameAvailable(String name) throws RemoteException {
	Iterator<ClientI> it = m_clients.listIterator();
	while (it.hasNext()) if(name.equals(it.next().getName())) return false;
	return true;
    }
}