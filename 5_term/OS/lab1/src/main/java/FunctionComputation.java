import org.newsclub.net.unix.AFUNIXServerSocket;
import org.newsclub.net.unix.AFUNIXSocketAddress;

import java.io.*;
import java.net.Socket;

public class FunctionComputation implements Runnable {
    private final char func;

    public FunctionComputation(char func) {
        this.func = func;
    }

    @Override
    public void run() {
        try (AFUNIXServerSocket server = AFUNIXServerSocket.newInstance()) {
            System.out.println();
            server.bind(AFUNIXSocketAddress.of(new File("socket" + func + ".socket")));
            System.out.println("Server: " + server);
            System.out.println("Waiting for connection...");
            try (Socket socket = server.accept()) {
                System.out.println("Connected: " + socket);
                try (InputStream inputStream = socket.getInputStream(); OutputStream outputStream = socket.getOutputStream()) {
                    outputStream.flush();
                    DataInputStream dataInputStream = new DataInputStream(inputStream);
                    DataOutputStream dataOutputStream = new DataOutputStream(outputStream);
                    if (func == 'F') {
                        dataOutputStream.writeDouble(FunctionF.calculate(dataInputStream.readDouble()));
                    } else if (func == 'G') {
                        dataOutputStream.writeDouble(FunctionG.calculate(dataInputStream.readDouble()));
                    }
                    dataOutputStream.flush();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
