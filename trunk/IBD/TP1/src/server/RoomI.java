import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RoomI extends Remote {

    void join(Client) throws RemoteException;
    void quit(Client) throws RemoteException;
    void post(Client, Message) throws RemoteException;

}