import com.google.gson.Gson;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ServerSocketTask10 {
    public static final int THREADS = 5;

    private ServerSocket server = null;
    private Socket socket = null;
    private PrintWriter out = null;
    private BufferedReader in = null;

    public void start(int port) throws IOException {
        server = new ServerSocket(port);
        socket = server.accept();
        in = new BufferedReader(new InputStreamReader(socket.getInputStream( )));
        out = new PrintWriter(socket.getOutputStream(), true);
        ExecutorService agent = Executors.newFixedThreadPool(THREADS);
        while (true) {
            String query = in.readLine();
            agent.execute(new processQuery(out, query));
        }
    }

    private static class processQuery implements Runnable {
        private PrintWriter out;
        private String query;

        public processQuery(PrintWriter out, String query) {
            this.out = out;
            this.query = query;
        }

        @Override
        public void run() {
            if (query == null)
                return;
            String[] fields = query.split("#");
            if (fields.length == 0)
                return;

            var action = fields[0];

            String response = "";
            switch (action) {
                case "getId":
                    response = new Gson().toJson(fields[1]);
                    break;
                case "setId":
                    var train = new Gson().fromJson(fields[1], Train.class);
                    train.setId(12);
                    break;
                case "getDestination":
                    Integer id = Integer.parseInt(fields[1]);
                    train = Trains.getTrainById(id);
                    response = new Gson().toJson(train.getDestination());
                    break;
                case "setDestination":
                    train = new Gson().fromJson(fields[1], Train.class);
                    train.setDestination("Lviv");
                    break;
                case "getDepartureTime":
                    id = Integer.parseInt(fields[1]);
                    train = Trains.getTrainById(id);
                    response = new Gson().toJson(train.getDepartureTime());
                    break;
                case "setDepartureTime":
                    train = new Gson().fromJson(fields[1], Train.class);
                    train.setDepartureTime("12:12:12");
                    break;
            }
            out.println(response);
        }
    }

    public static void main(String[] args) {
        try {
            ServerSocketTask10 srv = new ServerSocketTask10();
            srv.start(12345);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
