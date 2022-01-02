import java.io.IOException;
import java.rmi.Naming;
import java.rmi.NotBoundException;

public class ClientRmiTask10 {
    public static void main(String[] args) throws IOException, NotBoundException {
        String url = "//localhost:123/Exam";
        var server = (ServerRmiTask10) Naming.lookup(url);
        System.out.println("RMI object found");
    }
}
