import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RoomI extends Remote {

    void join(Client client) throws RemoteException;
    void quit(Client client) throws RemoteException;
    void post(Client client, Message message) throws RemoteException;

}