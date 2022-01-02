import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class ServerRmiTask10 extends UnicastRemoteObject implements Remote {
    protected ServerRmiTask10() throws RemoteException {
        super();
    }

    public Integer getId(Integer id) {
        return id;
    }

    public void setId(Train e) {
        e.setId(12);
    }

    public String getDestination(Integer id) {
        return Trains.findById(id).getDestination();
    }

    public void setDestination(Train e) {
        e.setDestination();
    }

    public String getDepartureTime(Integer id) {
        return Trains.findById(id).getDepartureTime();
    }

    public void setDepartureTime(Train e) {
        e.setDepartureTime();
    }

    public static void main(String[] args) throws RemoteException {
        var bck = new ServerRmiTask10();
        Registry registry = LocateRegistry.createRegistry(123);
        registry.rebind("Exam", bck);
        System.out.println("Server started!");
    }
}
