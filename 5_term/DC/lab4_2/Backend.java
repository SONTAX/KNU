package lab4_2;

import java.rmi.*;
import java.util.List;

public interface Backend extends Remote{
    public Section sectionFindById(Long id) throws RemoteException;
    public Good goodFindByName(String name) throws RemoteException;
    public Section sectionFindByName(String name) throws RemoteException;
    public boolean goodUpdate(Good good) throws RemoteException;
    public boolean sectionUpdate(Section section) throws RemoteException;
    public boolean goodInsert(Good good) throws RemoteException;
    public boolean sectionInsert(Section section) throws RemoteException;
    public boolean sectionDelete(Section section) throws RemoteException;
    public boolean goodDelete(Good good) throws RemoteException;
    public List<Section> sectionAll() throws RemoteException;
    public List<Good> goodAll() throws RemoteException;
    public List<Good> goodFindBySectionId(Long idc) throws RemoteException;
}
