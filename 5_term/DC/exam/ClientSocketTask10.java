import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;

public class ClientSocketTask10 {
    private Socket socket = null;
    private PrintWriter out = null;
    private BufferedReader in = null;

    public ClientSocketTask10(String ip, int port) throws IOException {
        this.socket = new Socket(ip,port);
        this.in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.out = new PrintWriter(socket.getOutputStream(), true);
    }

    public Integer getId(Integer id) {
        var query = "getId#" + id;
        out.println(query);
        try {
            return new Gson().fromJson(in.readLine(), Integer.class);
        } catch (JsonSyntaxException | IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void setId(Train e) {
        var query = "setId#" + (new Gson().toJson(e));
        out.println(query);
    }

    public String getDestination(Integer id) {
        var query = "getDestination#" + id;
        out.println(query);
        try {
            return new Gson().fromJson(in.readLine(), String.class);
        } catch (JsonSyntaxException | IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void setDestination(Train e) {
        var query = "setDestination#" + (new Gson().toJson(e));
        out.println(query);
    }

    public String getDepartureTime(Integer id) {
        var query = "getDepartureTime#" + id;
        out.println(query);
        try {
            return new Gson().fromJson(in.readLine(), String.class);
        } catch (JsonSyntaxException | IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void setDepartureTime(Train e) {
        var query = "setDepartureTime#" + (new Gson().toJson(e));
        out.println(query);
    }

    public static void main(String[] args) throws IOException {
        var client = new ClientSocketTask10("localhost",12345);
    }
}
