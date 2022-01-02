package lab3_2.server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    private ServerSocket server = null;
    private Socket sock = null;
    private PrintWriter out = null;
    private BufferedReader in = null;

    public void start(int port) throws IOException {
        server = new ServerSocket(port);
        while (true) {
            sock = server.accept();
            in = new BufferedReader(new InputStreamReader(sock.getInputStream( )));
            out = new PrintWriter(sock.getOutputStream(), true);
            while (processQuery());
        }
    }

    private boolean processQuery() {
        int result = 0;
        String response = "";
        try {
            String query = in.readLine();
            if (query==null)
                return false;

            String[] fields = query.split("#");
            if (fields.length == 0){
                return true;
            } else {
                var action = fields[0];
                Section section;
                Good good;

                System.out.println(action);

                switch(action) {
                    case "SectionFindById":
                        var id = Long.parseLong(fields[1]);
                        section = SectionDAO.findById(id);
                        response = section.getName();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "GoodFindBySectionId":
                        id = Long.parseLong(fields[1]);
                        var list = GoodDAO.findBySectionId(id);
                        var str = new StringBuilder();
                        for(Good c: list) {
                            str.append(c.getId());
                            str.append("#");
                            str.append(c.getSectionId());
                            str.append("#");
                            str.append(c.getName());
                            str.append("#");
                            str.append(c.getPrice());
                            str.append("#");
                        }
                        response = str.toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "GoodFindByName":
                        var name = fields[1];
                        good = GoodDAO.findByName(name);
                        response = good.getId().toString()+"#"+good.getSectionId().toString()+"#"+good.getName()+"#"+good.getPrice().toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "SectionFindByName":
                        name = fields[1];
                        section = SectionDAO.findByName(name);
                        response = section.getId().toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "GoodUpdate":
                        id = Long.parseLong(fields[1]);
                        var sectionid = Long.parseLong(fields[2]);
                        name = fields[3];
                        var price = Long.parseLong(fields[4]);
                        good = new Good(id,sectionid,name,price);
                        if(GoodDAO.update(good))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "SectionUpdate":
                        id = Long.parseLong(fields[1]);
                        name = fields[2];
                        section = new Section(id,name);
                        if (SectionDAO.update(section))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "GoodInsert":
                        sectionid = Long.parseLong(fields[1]);
                        name = fields[2];
                        price = Long.parseLong(fields[3]);
                        good = new Good((long) 0,sectionid,name,price);
                        if(GoodDAO.insert(good))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "SectionInsert":
                        name = fields[1];
                        section = new Section();
                        section.setName(name);

                        System.out.println(name);

                        if(SectionDAO.insert(section))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "GoodDelete":
                        id = Long.parseLong(fields[1]);
                        good = new Good();
                        good.setId(id);
                        if(GoodDAO.delete(good))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "SectionDelete":
                        id = Long.parseLong(fields[1]);
                        section = new Section();
                        section.setId(id);
                        if(SectionDAO.delete(section))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "GoodAll":
                        var list1 = GoodDAO.findAll();
                        str = new StringBuilder();
                        for(Good c: list1) {
                            str.append(c.getId());
                            str.append("#");
                            str.append(c.getSectionId());
                            str.append("#");
                            str.append(c.getName());
                            str.append("#");
                            str.append(c.getPrice());
                            str.append("#");
                        }
                        response = str.toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "SectionAll":
                        var list2 = SectionDAO.findAll();
                        str = new StringBuilder();
                        for(Section c: list2) {
                            str.append(c.getId());
                            str.append("#");
                            str.append(c.getName());
                            str.append("#");
                        }
                        response = str.toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                }
            }

            return true;
        }
        catch(IOException e){
            return false;
        }
    }
    public static void main(String[] args) {
        try {
            Server srv = new Server();
            srv.start(12345);
        } catch(IOException e) {
            System.out.println("Возникла ошибка");
        }
    }
}