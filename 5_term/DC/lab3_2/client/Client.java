package lab3_2.client;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Client {
    private Socket sock = null;
    private PrintWriter out = null;
    private BufferedReader in = null;
    private static final String split = "#";

    Client(String ip, int port) throws IOException{
        sock = new Socket(ip,port);
        in = new BufferedReader(
                new InputStreamReader(sock.getInputStream( )));
        out = new PrintWriter(sock.getOutputStream(), true);
    }

    public Section sectionFindById(Long id) {
        var query = "SectionFindById"+split+id.toString();
        out.println(query);
        String response = "";
        try {
            response = in.readLine();
            return new Section(id, response);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public Good goodFindByName(String name) {
        var query = "GoodFindByName"+split+name;
        out.println(query);
        String response = "";
        try {
            response = in.readLine();
            String[] fields = response.split(split);
            var id = Long.parseLong(fields[0]);
            var sectionid = Long.parseLong(fields[1]);
            var price = Long.parseLong(fields[3]);
            return new Good(id,sectionid,name,price);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public Section sectionFindByName(String name) {
        var query = "SectionFindByName"+split+name;
        out.println(query);
        try {
            var response = Long.parseLong(in.readLine());
            return new Section(response,name);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public boolean goodUpdate(Good good) {
        var query = "GoodUpdate"+split+good.getId().toString()+
                "#"+good.getSectionId().toString()+"#"+good.getName()
                +"#"+good.getSectionId().toString();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean sectionUpdate(Section section) {
        var query = "SectionUpdate"+split+section.getId().toString()+
                "#"+section.getName();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean goodInsert(Good good) {
        var query = "GoodInsert"+
                "#"+good.getSectionId().toString()+"#"+good.getName()
                +"#"+good.getPrice().toString();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean sectionInsert(Section section) {
        var query = "SectionInsert"+
                "#"+section.getName();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean sectionDelete(Section section) {
        var query = "SectionDelete"+split+section.getId().toString();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean goodDelete(Good good) {
        var query = "GoodDelete"+split+good.getId().toString();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    public List<Section> sectionAll(){
        var query = "SectionAll";
        out.println(query);
        var list = new ArrayList<Section>();
        try {
            var response = in.readLine();
            String[] fields = response.split(split);
            for(int i=0;i<fields.length; i+=2) {
                var id = Long.parseLong(fields[i]);
                var name = fields[i+1];
                list.add(new Section(id,name));
            }
            return list;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public List<Good> goodAll(){
        var query = "GoodAll";
        out.println(query);
        var list = new ArrayList<Good>();
        try {
            var response = in.readLine();
            String[] fields = response.split(split);
            for(int i=0;i<fields.length; i+=4) {
                var id = Long.parseLong(fields[i]);
                var sectionid = Long.parseLong(fields[i+1]);
                var name = fields[i+2];
                var price = Long.parseLong(fields[i+3]);
                list.add(new Good(id,sectionid,name,price));
            }
            return list;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public List<Good> goodFindBySectionId(Long idc){
        var query = "GoodFindBySectionId"+split+idc.toString();
        out.println(query);
        var list = new ArrayList<Good>();
        try {
            var response = in.readLine();
            String[] fields = response.split(split);
            for(int i=0;i<fields.length; i+=4) {
                var id = Long.parseLong(fields[i]);
                var sectionid = Long.parseLong(fields[i+1]);
                var name = fields[i+2];
                var price = Long.parseLong(fields[i+3]);
                list.add(new Good(id,sectionid,name,price));
            }
            return list;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void disconnect(){
        try {
            sock.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws IOException {
        (new Client()).test("localhost",12345);
    }
}
