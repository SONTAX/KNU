package lab5_2;

import javax.jms.Connection;
import javax.jms.DeliveryMode;
import javax.jms.Destination;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageConsumer;
import javax.jms.MessageProducer;
import javax.jms.Session;
import javax.jms.TextMessage;
//import org.apache.activemq.ActiveMQConnectionFactory;

public class Server {
    private Connection connection;
    private Session session;
    private MessageProducer producer;
    private MessageConsumer consumer;

    public void start() {
        //ActiveMQConnectionFactory factory = new ActiveMQConnectionFactory("tcp://localhost:61616");

        try {
            //onnection = factory.createConnection();
            connection.start();
            session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
            Destination queueSend = session.createQueue("toClient");
            Destination queueRec = session.createQueue("fromClient");
            producer = session.createProducer(queueSend);
            producer.setDeliveryMode(DeliveryMode.NON_PERSISTENT);
            consumer = session.createConsumer(queueRec);
            while(processQuery()) {}
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }

    private boolean processQuery() {
        int result = 0;
        String response = "";
        String query = "";
        try {
            Message request = consumer.receive(500);
            if(request == null)
                return true;
            if (request instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) request;
                query = textMessage.getText();
            } else
                return true;
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
                        TextMessage message = session.createTextMessage(response);
                        producer.send(message);
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
                        message = session.createTextMessage(response);
                        producer.send(message);
                        break;
                    case "GoodFindByName":
                        var name = fields[1];
                        good = GoodDAO.findByName(name);
                        response = good.getId().toString()+"#"+good.getSectionId().toString()+"#"+good.getName()+"#"+good.getPrice().toString();
                        System.out.println(response);
                        message = session.createTextMessage(response);
                        producer.send(message);
                        break;
                    case "SectionFindByName":
                        name = fields[1];
                        section = SectionDAO.findByName(name);
                        response = section.getId().toString();
                        System.out.println(response);
                        message = session.createTextMessage(response);
                        producer.send(message);
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
                        message = session.createTextMessage(response);
                        producer.send(message);
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
                        message = session.createTextMessage(response);
                        producer.send(message);
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
                        message = session.createTextMessage(response);
                        producer.send(message);
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
                        message = session.createTextMessage(response);
                        producer.send(message);
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
                        message = session.createTextMessage(response);
                        producer.send(message);
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
                        message = session.createTextMessage(response);
                        producer.send(message);
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
                        message = session.createTextMessage(response);
                        producer.send(message);
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
                        message = session.createTextMessage(response);
                        producer.send(message);
                        break;
                }
            }
            return true;
        }
        catch(Exception e){
            return false;
        }
    }

    public void close() {
        try {
            session.close();
            connection.close();
        } catch (JMSException e) {
            e.printStackTrace();
        }

    }

    public static void main(String[] args) {
        var server = new Server();
        server.start();
    }
}
