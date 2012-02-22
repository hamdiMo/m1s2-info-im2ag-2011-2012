import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RoomI extends Remote {

    void join(ClientI client) throws RemoteException;
    void quit(ClientI client) throws RemoteException;
    void post(ClientI client, String text) throws RemoteException;
    boolean isNameAvailable(String name) throws RemoteException;
}