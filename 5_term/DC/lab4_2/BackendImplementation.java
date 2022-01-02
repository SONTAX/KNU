package lab4_2;


import java.rmi.server.UnicastRemoteObject;
import java.util.List;
import java.net.MalformedURLException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class BackendImplementation extends UnicastRemoteObject implements Backend {

    protected BackendImplementation() throws RemoteException {
        super();
    }

    @Override
    public Section sectionFindById(Long id) throws RemoteException {
        return SectionDAO.findById(id);
    }

    @Override
    public Good goodFindByName(String name) throws RemoteException {
        return GoodDAO.findByName(name);
    }

    @Override
    public Section sectionFindByName(String name) throws RemoteException {
        return SectionDAO.findByName(name);
    }

    @Override
    public boolean goodUpdate(Good good) throws RemoteException {
        return GoodDAO.update(good);
    }

    @Override
    public boolean sectionUpdate(Section section) throws RemoteException {
        return SectionDAO.update(section);
    }

    public boolean goodInsert(Good good) throws RemoteException {
        return GoodDAO.insert(good);
    }

    @Override
    public boolean sectionInsert(Section section) throws RemoteException {
        return SectionDAO.insert(section);
    }

    @Override
    public boolean sectionDelete(Section section) throws RemoteException {
        return SectionDAO.delete(section);
    }

    @Override
    public boolean goodDelete(Good good) throws RemoteException {
        return GoodDAO.delete(good);
    }

    @Override
    public List<Section> sectionAll() throws RemoteException {
        return SectionDAO.findAll();
    }

    @Override
    public List<Good> goodAll() throws RemoteException {
        return GoodDAO.findAll();
    }

    @Override
    public List<Good> goodFindBySectionId(Long idc) throws RemoteException {
        return GoodDAO.findBySectionId(idc);
    }


    public static void main(String[] args) throws RemoteException, MalformedURLException {
        var bck = new BackendImplementation();
        Registry registry = LocateRegistry.createRegistry(123);
        registry.rebind("Lab13", bck);
        System.out.println("Server started!");
    }
}
