package server;

import java.util.List;
import java.util.Stack;
import java.util.LinkedList;
import java.util.Iterator;

public class Room implements RoomI {
    
    /** Attributs */
    private List<Client> m_clients;
    private Stack<Message> m_historic;
    private String m_name;
    
    /** Constructeur */
    Room(String name) {
	m_clients = new LinkedList();
	m_historic = new LinkedList();
	m_name = name;
    }

    /** Methodes */
    void join(Client client) throws RemoteException {
	m_clients.add(client);
	// envoyer les derniers messages au client
	// envoyer la liste des connectes
	Iterator<Client> it = new m_clients.listIterator();
	while (it.hasNext()) {
	    Client tmp = it.next();
	    tmp.notifyJoin(client);
	    client.notifyJoin(tmp);
	}
    }

    void quit(Client client) throws RemoteException {
	m_clients.remove(client);
	Iterator<Client> it = new m_clients.listIterator();
	while (it.hasNext()) it.next().notifyQuit(client);
    }

    void post(Client client, String text) throws RemoteException {
	Message message = new Message(client.getName(), text);
	m_historic.add(message);
	Iterator<Client> it = new m_clients.listIterator();
	while (it.hasNext()) it.next().notify(message);
    }
    
}