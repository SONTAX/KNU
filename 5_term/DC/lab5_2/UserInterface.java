package lab5_2;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public class UserInterface extends JFrame{
    private static Client client = null;
    private static Section section = null;
    private static Good good = null;

    private static boolean editMode = false;
    private static boolean sectionMode = true;

    private static JButton btnAddSection = new JButton("Add Section");
    private static JButton btnAddGood = new JButton("Add Good");
    private static JButton btnEdit= new JButton("Edit Data");
    private static JButton btnCancel= new JButton("Cancel");
    private static JButton btnSave= new JButton("Save");
    private static JButton btnDelete= new JButton("Delete");

    private static Box menuPanel = Box.createVerticalBox();
    private static Box actionPanel = Box.createVerticalBox();
    private static Box comboPanel = Box.createVerticalBox();
    private static Box goodPanel = Box.createVerticalBox();
    private static Box sectionPanel = Box.createVerticalBox();

    private static JComboBox comboSection = new JComboBox();
    private static JComboBox comboGood = new JComboBox();

    private static JTextField tfSectionName = new JTextField(30);
    private static JTextField tfGoodName = new JTextField(30);
    private static JTextField tfGoodSectionName = new JTextField(30);
    private static JTextField tfGoodPrice = new JTextField(30);

    private static JFrame frame;

    UserInterface(){
        super("Warehouse");
        frame = this;
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                frame.dispose();
                client.close();
                System.exit(0);
            }
        });
        Box box = Box.createVerticalBox();
        client.cleanMessages();

        menuPanel.add(btnAddSection);
        btnAddSection.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                editMode = false;
                sectionMode = true;
                menuPanel.setVisible(false);
                comboPanel.setVisible(false);
                sectionPanel.setVisible(true);
                goodPanel.setVisible(false);
                actionPanel.setVisible(true);
                //setContentPane(box);
                pack();
            }
        });
        menuPanel.add(btnAddGood);
        btnAddGood.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                editMode = false;
                sectionMode = false;
                menuPanel.setVisible(false);
                comboPanel.setVisible(false);
                sectionPanel.setVisible(false);
                goodPanel.setVisible(true);
                actionPanel.setVisible(true);
                //setContentPane(box);
                pack();
            }
        });
        menuPanel.add(btnEdit);
        btnEdit.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                editMode = true;
                menuPanel.setVisible(false);
                comboPanel.setVisible(true);
                sectionPanel.setVisible(false);
                goodPanel.setVisible(false);
                actionPanel.setVisible(true);
                //setContentPane(box);
                pack();
            }
        });

        comboPanel.add(new JLabel("Section:"));
        comboPanel.add(comboSection);
        comboSection.addActionListener (new ActionListener () {
            public void actionPerformed(ActionEvent e) {
                String name = (String) comboSection.getSelectedItem();
                section = client.sectionFindByName((String) comboSection.getSelectedItem());
                sectionMode = true;
                sectionPanel.setVisible(true);
                goodPanel.setVisible(false);
                fillSectionFields();
                //setContentPane(box);
                pack();
            }
        });
        comboPanel.add(new JLabel("Good:"));
        comboPanel.add(comboGood);
        comboGood.addActionListener (new ActionListener () {
            public void actionPerformed(ActionEvent e) {
                String name = (String) comboGood.getSelectedItem();
                good = client.goodFindByName((String) comboGood.getSelectedItem());
                sectionMode = false;
                sectionPanel.setVisible(false);
                goodPanel.setVisible(true);
                fillGoodFields();
                //setContentPane(box);
                pack();
            }
        });
        fillComboBoxes();
        comboPanel.setVisible(false);

        goodPanel.add(new JLabel("Name:"));
        goodPanel.add(tfGoodName);
        goodPanel.add(new JLabel("Section Name:"));
        goodPanel.add(tfGoodSectionName);
        goodPanel.add(new JLabel("Price:"));
        goodPanel.add(tfGoodPrice);
        goodPanel.setVisible(false);

        sectionPanel.add(new JLabel("Name:"));
        sectionPanel.add(tfSectionName);
        sectionPanel.setVisible(false);

        actionPanel.add(btnSave);
        btnSave.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                save();
            }
        });
        actionPanel.add(btnDelete);
        btnDelete.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                delete();
            }
        });
        actionPanel.add(btnCancel);
        btnCancel.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                clearFields();
                menuPanel.setVisible(true);
                comboPanel.setVisible(false);
                sectionPanel.setVisible(false);
                goodPanel.setVisible(false);
                actionPanel.setVisible(false);
                //setContentPane(box);
                pack();
            }
        });
        actionPanel.setVisible(false);

        clearFields();
        box.add(menuPanel);
        box.add(comboPanel);
        box.add(sectionPanel);
        box.add(goodPanel);
        box.add(actionPanel);
        setContentPane(box);
        pack();
    }

    private static void save() {
        if(editMode) {
            if(sectionMode) {
                section.setName(tfSectionName.getText());
                if (!client.sectionUpdate(section)) {
                    JOptionPane.showMessageDialog(null, "Error: something went wrong!");
                }
            } else {
                good.setName(tfGoodName.getText());
                Section section = client.sectionFindByName(tfGoodSectionName.getText());
                if(section == null) {
                    JOptionPane.showMessageDialog(null, "Error: no such section!");
                    return;
                }
                good.setSectionId(section.getId());
                good.setPrice(Long.parseLong(tfGoodPrice.getText()));
                if (!client.goodUpdate(good)) {
                    JOptionPane.showMessageDialog(null, "Error: something went wrong!");
                }
            }
        } else {
            if (sectionMode) {
                var section = new Section();
                section.setName(tfSectionName.getText());
                if(client.sectionInsert(section)) {
                    comboSection.addItem(section.getName());
                }
            } else {
                var good = new Good();
                good.setName(tfGoodName.getText());
                Section section = client.sectionFindByName(tfGoodSectionName.getText());
                if(section == null) {
                    JOptionPane.showMessageDialog(null, "Error: no such section!");
                    return;
                }
                good.setSectionId(section.getId());
                good.setPrice(Long.parseLong(tfGoodPrice.getText()));
                if(client.goodInsert(good)) {
                    comboGood.addItem(good.getName());
                }
            }
        }
    }

    private static void delete() {
        if(editMode) {
            if(sectionMode) {
                var list = client.goodFindBySectionId(section.getId());
                for(Good c: list) {
                    comboGood.removeItem(c.getName());
                    client.goodDelete(c);
                }
                client.sectionDelete(section);
                comboSection.removeItem(section.getName());

            } else {
                client.goodDelete(good);
                comboGood.removeItem(good.getName());
            }
        }
    }

    private void fillComboBoxes() {
        comboSection.removeAllItems();
        comboGood.removeAllItems();
        var sections = client.sectionAll();
        var goods = client.goodAll();
        for(Section c: sections) {
            comboSection.addItem(c.getName());
        }
        for(Good c: goods) {
            comboGood.addItem(c.getName());
        }
    }

    private static void clearFields() {
        tfSectionName.setText("");
        tfGoodName.setText("");
        tfGoodSectionName.setText("");
        tfGoodPrice.setText("");
        section = null;
        good = null;
    }

    private static void fillSectionFields() {
        if (section == null)
            return;
        tfSectionName.setText(section.getName());
    }
    private static void fillGoodFields() {
        if(good == null)
            return;
        Section section = client.sectionFindById(good.getSectionId());
        tfGoodName.setText(good.getName());
        tfGoodSectionName.setText(section.getName());
        tfGoodPrice.setText(String.valueOf(good.getPrice()));
    }

    public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException {
        client = new Client();
        JFrame myWindow = new UserInterface();
        myWindow.setVisible(true);
    }
}
