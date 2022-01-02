package lab5_2;

import java.util.ArrayList;
import java.util.List;

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

public class Client {
    private Connection connection;
    private Session session;
    private MessageProducer producer;
    private MessageConsumer consumer;
    private static final String split = "#";

    Client(){
        //ActiveMQConnectionFactory factory = new ActiveMQConnectionFactory("tcp://localhost:61616");
        try {
            //connection = factory.createConnection();
            connection.start();
            session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
            Destination queueSend = session.createQueue("fromClient");
            Destination queueRec = session.createQueue("toClient");
            producer = session.createProducer(queueSend);
            producer.setDeliveryMode(DeliveryMode.NON_PERSISTENT);
            consumer = session.createConsumer(queueRec);
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }

    public Section sectionFindById(Long id) {
        var query = "SectionFindById"+split+id.toString();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return null;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            return new Section(id,response);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
    public Good goodFindByName(String name) {
        var query = "GoodFindByName"+split+name;
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return null;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            String[] fields = response.split(split);
            var id = Long.parseLong(fields[0]);
            var sectionid = Long.parseLong(fields[1]);
            var price = Long.parseLong(fields[3]);
            return new Good(id,sectionid,name,price);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public Section sectionFindByName(String name) {
        var query = "SectionFindByName"+split+name;
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return null;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            var responseid = Long.parseLong(response);
            return new Section(responseid,name);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public boolean goodUpdate(Good good) {
        var query = "GoodUpdate"+split+good.getId().toString()+
                "#"+good.getSectionId().toString()+"#"+good.getName()
                +"#"+good.getPrice().toString();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return false;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean sectionUpdate(Section section) {
        var query = "SectionUpdate"+split+section.getId().toString()+
                "#"+section.getName();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(10000000);
            if(message == null)
                return false;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean goodInsert(Good good) {
        var query = "GoodInsert"+
                "#"+good.getSectionId().toString()+"#"+good.getName()
                +"#"+good.getPrice().toString();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return false;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean sectionInsert(Section section) {
        var query = "SectionInsert"+
                "#"+section.getName();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return false;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean sectionDelete(Section section) {
        var query = "SectionDelete"+split+section.getId().toString();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return false;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean goodDelete(Good good) {
        var query = "GoodDelete"+split+good.getId().toString();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return false;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public List<Section> sectionAll(){
        var query = "SectionAll";
        var list = new ArrayList<Section>();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return null;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            String[] fields = response.split(split);
            for(int i=0;i<fields.length; i+=2) {
                var id = Long.parseLong(fields[i]);
                var name = fields[i+1];
                list.add(new Section(id,name));
            }
            return list;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public List<Good> goodAll(){
        var query = "GoodAll";
        var list = new ArrayList<Good>();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return null;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            String[] fields = response.split(split);
            for(int i=0;i<fields.length; i+=4) {
                var id = Long.parseLong(fields[i]);
                var sectionid = Long.parseLong(fields[i+1]);
                var name = fields[i+2];
                var price = Long.parseLong(fields[i+3]);
                list.add(new Good(id,sectionid,name,price));
            }
            return list;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public List<Good> goodFindBySectionId(Long idc){
        var query = "GoodFindBySectionId"+split+idc.toString();
        var list = new ArrayList<Good>();
        String response = "";
        try {
            TextMessage mes = session.createTextMessage(query);
            producer.send(mes);
            Message message = consumer.receive(5000);
            if(message == null)
                return null;
            if (message instanceof TextMessage) {
                TextMessage textMessage = (TextMessage) message;
                response = textMessage.getText();
            }
            if ("".equals(response))
                return list;
            String[] fields = response.split(split);
            for(int i=0;i<fields.length; i+=4) {
                var id = Long.parseLong(fields[i]);
                var sectionid = Long.parseLong(fields[i+1]);
                var name = fields[i+2];
                var price = Long.parseLong(fields[i+3]);
                list.add(new Good(id,sectionid,name,price));
            }
            return list;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public void cleanMessages() {
        try {
            Message message = consumer.receiveNoWait();
            while(message != null)
                message = consumer.receiveNoWait();
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }

    public void close(){
        try {
            session.close();
            connection.close();
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args){
        //(new Client()).test("localhost",12345);
    }
}
