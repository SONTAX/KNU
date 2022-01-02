package lab1_2;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.io.IOException;
import java.util.Map;

public class DOMParser {
    public static class SimpleErrorHandler implements ErrorHandler {
        public void warning(SAXParseException e) throws SAXException {
            System.out.println("Line " +e.getLineNumber() + ":");
            System.out.println(e.getMessage());
        }
        public void error(SAXParseException e) throws SAXException {
            System.out.println("Line " +e.getLineNumber() + ":");
            System.out.println(e.getMessage());
        }
        public void fatalError(SAXParseException e) throws SAXException {
            System.out.println("Line " +e.getLineNumber() + ":");
            System.out.println(e.getMessage());
        }
    }

    public static Warehouse parse(String path) throws ParserConfigurationException, SAXException, IOException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
        builder.setErrorHandler(new SimpleErrorHandler());
        Document doc = builder.parse(new File(path));
        doc.getDocumentElement().normalize();

        var map = new Warehouse();
        NodeList nodes = doc.getElementsByTagName("section");

        for(int i = 0; i < nodes.getLength(); ++i) {
            Element n = (Element)nodes.item(i);
            var section = new Section();
            section.setId(n.getAttribute("id"));
            section.setName(n.getAttribute("name"));
            map.addSection(section);

        }

        nodes = doc.getElementsByTagName("good");
        for(int j =0; j < nodes.getLength(); ++j) {
            Element e = (Element) nodes.item(j);
            var good = new Good();
            good.setId(e.getAttribute("id"));
            good.setSectionId(e.getAttribute("sectionId"));
            good.setName(e.getAttribute("name"));
            good.setPrice(Integer.parseInt(e.getAttribute("price")));
            map.addGood(good);
        }

        return map;
    }

    public static void write(Warehouse map, String path) throws ParserConfigurationException, TransformerException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
        var doc = builder.newDocument();
        Element root = doc.createElement("warehouse");
        doc.appendChild(root);

        var sections = map.getSections();
        for(Map.Entry<String, Section> entry : sections.entrySet()) {
            Element ctr = doc.createElement("section");
            ctr.setAttribute("id", entry.getValue().getId());
            ctr.setAttribute("name", entry.getValue().getName());
            root.appendChild(ctr);

            for(Good good: entry.getValue().getCities()) {
                Element ct = doc.createElement("good");
                ct.setAttribute("id", good.getId());
                ct.setAttribute("sectionId", good.getSectionId());
                ct.setAttribute("name", good.getName());
                ct.setAttribute("price", String.valueOf(good.getPrice()));
                ctr.appendChild(ct);
            }
        }
        Source domSource = new DOMSource(doc);
        Result fileResult = new StreamResult(new File(path));
        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        Transformer transformer = transformerFactory.newTransformer();
        transformer.setOutputProperty(OutputKeys.ENCODING,"UTF-8");
        transformer.setOutputProperty(OutputKeys.DOCTYPE_SYSTEM,"warehouse.dtd");
        transformer.transform(domSource, fileResult);
    }
}
