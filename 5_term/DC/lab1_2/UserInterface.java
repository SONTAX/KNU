package lab1_2;

import org.xml.sax.SAXException;

import javax.swing.*;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.util.Map;

public class UserInterface extends JFrame{
    private static Warehouse warehouse;
    private static Section section = null;
    private static Good good = null;

    private static boolean editMode = false;
    private static boolean sectionMode = true;

    private static final JButton btnAddSection = new JButton("Add Section");
    private static final JButton btnAddGood = new JButton("Add Good");
    private static final JButton btnEdit= new JButton("Edit Data");
    private static final JButton btnCancel= new JButton("Cancel");
    private static final JButton btnSave= new JButton("Save");
    private static final JButton btnDelete= new JButton("Delete");

    private static final Box menuPanel = Box.createVerticalBox();
    private static final Box actionPanel = Box.createVerticalBox();
    private static final Box comboPanel = Box.createVerticalBox();
    private static final Box goodPanel = Box.createVerticalBox();
    private static final Box sectionPanel = Box.createVerticalBox();

    private static final JComboBox comboSection = new JComboBox();
    private static final JComboBox comboGood = new JComboBox();

    private static final JTextField tfSectionName = new JTextField(30);
    private static final JTextField tfGoodName = new JTextField(30);
    private static final JTextField tfGoodSectionName = new JTextField(30);
    private static final JTextField tfGoodPrice = new JTextField(30);

    private static JFrame frame;

    UserInterface(){
        super("Warehouse");
        frame = this;
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                frame.dispose();
                try {
                    DOMParser.write(warehouse,"src/main/java/lab1_2/warehouse.xml");
                } catch (ParserConfigurationException | TransformerException e) {
                    e.printStackTrace();
                }
                System.exit(0);
            }
        });
        Box box = Box.createVerticalBox();

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
        comboSection.addActionListener (e -> {
            String name = (String) comboSection.getSelectedItem();
            section = warehouse.getSection(name);
            sectionMode = true;
            sectionPanel.setVisible(true);
            goodPanel.setVisible(false);
            fillSectionFields();
            //setContentPane(box);
            pack();
        });
        comboPanel.add(new JLabel("Good:"));
        comboPanel.add(comboGood);
        comboGood.addActionListener (e -> {
            String name = (String) comboGood.getSelectedItem();
            good = warehouse.getGood(name);
            sectionMode = false;
            sectionPanel.setVisible(false);
            goodPanel.setVisible(true);
            fillGoodFields();
            //setContentPane(box);
            pack();
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
                var oldname = section.getName();
                var newname = tfSectionName.getText();
                if (changeSection(section) && !section.getName().equals(oldname)) {
                    comboSection.removeItem(oldname);
                    comboSection.addItem(newname);
                    comboSection.setSelectedIndex(comboSection.getItemCount()-1);
                }
            } else {
                var oldname = good.getName();
                var newname = tfGoodSectionName.getText();
                if (changeGood(good) && !good.getName().equals(oldname)) {
                    comboGood.removeItem(oldname);
                    comboGood.addItem(newname);
                    comboGood.setSelectedIndex(comboGood.getItemCount()-1);
                }
            }
        } else {
            if (sectionMode) {
                var section = new Section();
                warehouse.generateId(section);
                if(changeSection(section)) {
                    warehouse.addSection(section);
                    comboSection.addItem(section.getName());
                }
            } else {
                var good = new Good();
                warehouse.generateId(good);
                if(changeGood(good)) {
                    warehouse.addGood(good);
                    comboGood.addItem(good.getName());
                }
            }
        }
    }
    private static boolean changeSection(Section section) {
        var newName = tfSectionName.getText();
        if(warehouse.getSection(newName) == null) {
            warehouse.rename(section, newName);
            return true;
        }
        fillSectionFields();
        JOptionPane.showMessageDialog(null, "Error: this section already exists!");
        return false;
    }
    private static boolean changeGood(Good good) {
        var section = warehouse.getSection(tfGoodSectionName.getText());
        if (section == null) {
            fillGoodFields();
            JOptionPane.showMessageDialog(null, "Error: no such section!");
            return false;
        }
        var newName = tfGoodName.getText();
        if(warehouse.getGood(newName) == null)
            warehouse.rename(good, newName);
        warehouse.transferGood(good, section);
        good.setPrice(Integer.parseInt(tfGoodPrice.getText()));
        return true;
    }

    private static void delete() {
        if(editMode) {
            if(sectionMode) {
                warehouse.removeSection(section);
                for(Good good: section.getCities())
                    comboGood.removeItem(good.getName());
                comboSection.removeItem(section.getName());
            } else {
                warehouse.removeGood(good);
                comboGood.removeItem(good.getName());
            }
        }
    }

    private void fillComboBoxes() {
        comboSection.removeAllItems();
        comboGood.removeAllItems();
        var sections = warehouse.getSections();
        for(Map.Entry<String, Section> entry : sections.entrySet()) {
            comboSection.addItem(entry.getValue().getName());
            for(Good good: entry.getValue().getCities()) {
                comboGood.addItem(good.getName());
            }
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
        var sections = warehouse.getSections();
        tfGoodName.setText(good.getName());
        tfGoodSectionName.setText(sections.get(good.getSectionId()).getName());
        tfGoodPrice.setText(String.valueOf(good.getPrice()));
    }

    public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException {
        warehouse = DOMParser.parse("src/main/java/part2/lab1_2/warehouse.xml");
        JFrame myWindow = new UserInterface();
        myWindow.setVisible(true);
    }
}
