import java.io.*;
import java.util.Objects;
import java.util.StringTokenizer;
import java.util.Vector;

public class Kernel extends Thread {
    private static final String lineSeparator = System.getProperty("line.separator");
    public static byte addressRadix = 10;
    // The number of virtual pages must be fixed at 63 due to dependencies in the GUI
    private static int virtualPageNum = 63;
    public int runs;
    public int runCycles;
    public int faultNumber;
    public long block = (int) Math.pow(2, 12);
    private String output = null;
    private String command_file;
    private String config_file;
    private ControlPanel controlPanel;
    private final Vector<Page> memVector = new Vector<>();
    private final Vector<Instruction> instructVector = new Vector<>();
    private boolean doStdoutLog = false;
    private boolean doFileLog = false;

    public void init(String commands, String config) {
        new File(commands);
        File f;
        command_file = commands;
        config_file = config;
        faultNumber = 0;
        String line;
        String tmp = null;
        String command = "";
        byte R = 0;
        byte M = 0;
        int i;
        int j;
        int id;
        int physical;
        int physical_count = 0;
        int inMemTime;
        int lastTouchTime;
        double power;
        long high;
        long low;
        long address;
        long address_limit = (block * (virtualPageNum + 1)) - 1;
        if (config != null) {
            f = new File(config);
            try {
                DataInputStream in = new DataInputStream(new FileInputStream(f));
                while ((line = in.readLine()) != null) {
                    if (line.startsWith("numpages")) {
                        StringTokenizer st = new StringTokenizer(line);
                        while (st.hasMoreTokens()) {
                            tmp = st.nextToken();
                            virtualPageNum = Common.s2i(st.nextToken()) - 1;
                            if (virtualPageNum < 2 || virtualPageNum > 63) {
                                System.out.println("MemoryManagement: numpages out of bounds.");
                                System.exit(-1);
                            }
                            address_limit = (block * (virtualPageNum + 1)) - 1;
                        }
                    }
                }
                in.close();
            } catch (IOException e) { /* Handle exceptions */ }
            for (i = 0; i <= virtualPageNum; i++) {
                high = (block * (i + 1)) - 1;
                low = block * i;
                memVector.addElement(new Page(i, -1, R, M, 0, 0, high, low));
            }
            try {
                DataInputStream in = new DataInputStream(new FileInputStream(f));
                while ((line = in.readLine()) != null) {
                    if (line.startsWith("memset")) {
                        StringTokenizer st = new StringTokenizer(line);
                        st.nextToken();
                        while (st.hasMoreTokens()) {
                            id = Common.s2i(st.nextToken());
                            tmp = st.nextToken();
                            if (tmp.startsWith("x")) {
                                physical = -1;
                            } else {
                                physical = Common.s2i(tmp);
                            }
                            if ((0 > id || id > virtualPageNum) || (-1 > physical || physical > ((virtualPageNum - 1) / 2))) {
                                System.out.println("MemoryManagement: Invalid page value in " + config);
                                System.exit(-1);
                            }
                            R = Common.s2b(st.nextToken());
                            if (R < 0 || R > 1) {
                                System.out.println("MemoryManagement: Invalid R value in " + config);
                                System.exit(-1);
                            }
                            M = Common.s2b(st.nextToken());
                            if (M < 0 || M > 1) {
                                System.out.println("MemoryManagement: Invalid M value in " + config);
                                System.exit(-1);
                            }
                            inMemTime = Common.s2i(st.nextToken());
                            if (inMemTime < 0) {
                                System.out.println("MemoryManagement: Invalid inMemTime in " + config);
                                System.exit(-1);
                            }
                            lastTouchTime = Common.s2i(st.nextToken());
                            if (lastTouchTime < 0) {
                                System.out.println("MemoryManagement: Invalid lastTouchTime in " + config);
                                System.exit(-1);
                            }
                            Page page = memVector.elementAt(id);
                            page.physical = physical;
                            page.R = R;
                            page.M = M;
                            page.inMemTime = inMemTime;
                            page.lastTouchTime = lastTouchTime;
                        }
                    }
                    if (line.startsWith("enable_logging")) {
                        StringTokenizer st = new StringTokenizer(line);
                        while (st.hasMoreTokens()) {
                            if (st.nextToken().startsWith("true")) {
                                doStdoutLog = true;
                            }
                        }
                    }
                    if (line.startsWith("log_file")) {
                        StringTokenizer st = new StringTokenizer(line);
                        while (st.hasMoreTokens()) {
                            tmp = st.nextToken();
                        }
                        assert tmp != null;
                        if (tmp.startsWith("log_file")) {
                            doFileLog = false;
                            output = "tracefile";
                        } else {
                            doFileLog = true;
                            doStdoutLog = false;
                            output = tmp;
                        }
                    }
                    if (line.startsWith("pagesize")) {
                        StringTokenizer st = new StringTokenizer(line);
                        while (st.hasMoreTokens()) {
                            st.nextToken();
                            tmp = st.nextToken();
                            if (tmp.startsWith("power")) {
                                power = Integer.parseInt(st.nextToken());
                                block = (int) Math.pow(2, power);
                            } else {
                                block = Long.parseLong(tmp, 10);
                            }
                            address_limit = (block * (virtualPageNum + 1)) - 1;
                        }
                        if (block < 64 || block > Math.pow(2, 26)) {
                            System.out.println("MemoryManagement: pagesize is out of bounds");
                            System.exit(-1);
                        }
                        for (i = 0; i <= virtualPageNum; i++) {
                            Page page = memVector.elementAt(i);
                            page.high = (block * (i + 1)) - 1;
                            page.low = block * i;
                        }
                    }
                    if (line.startsWith("addressradix")) {
                        StringTokenizer st = new StringTokenizer(line);
                        while (st.hasMoreTokens()) {
                            st.nextToken();
                            tmp = st.nextToken();
                            addressRadix = Byte.parseByte(tmp);
                            if (addressRadix < 0 || addressRadix > 20) {
                                System.out.println("MemoryManagement: addressradix out of bounds.");
                                System.exit(-1);
                            }
                        }
                    }
                }
                in.close();
            } catch (IOException e) { /* Handle exceptions */ }
        }
        f = new File(commands);
        try {
            DataInputStream in = new DataInputStream(new FileInputStream(f));
            while ((line = in.readLine()) != null) {
                if (line.startsWith("READ") || line.startsWith("WRITE")) {
                    if (line.startsWith("READ")) {
                        command = "READ";
                    }
                    if (line.startsWith("WRITE")) {
                        command = "WRITE";
                    }
                    StringTokenizer st = new StringTokenizer(line);
                    st.nextToken();
                    tmp = st.nextToken();
                    if (tmp.startsWith("random")) {
                        instructVector.addElement(new Instruction(command, Common.randomLong(address_limit)));
                    } else {
                        if (tmp.startsWith("bin")) {
                            address = Long.parseLong(st.nextToken(), 2);
                        } else if (tmp.startsWith("oct")) {
                            address = Long.parseLong(st.nextToken(), 8);
                        } else if (tmp.startsWith("hex")) {
                            address = Long.parseLong(st.nextToken(), 16);
                        } else {
                            address = Long.parseLong(tmp);
                        }
                        if (0 > address || address > address_limit) {
                            System.out.println("MemoryManagement: " + address + ", Address out of range in " + commands);
                            System.exit(-1);
                        }
                        instructVector.addElement(new Instruction(command, address));
                    }
                }
            }
            in.close();
        } catch (IOException e) { /* Handle exceptions */ }
        runCycles = instructVector.size();
        if (runCycles < 1) {
            System.out.println("MemoryManagement: no instructions present for execution.");
            System.exit(-1);
        }
        if (doFileLog) {
            File trace = new File(output);
            trace.delete();
        }
        runs = 0;
        for (i = 0; i < virtualPageNum; i++) {
            Page page = memVector.elementAt(i);
            for (j = 0; j < virtualPageNum; j++) {
                Page tmp_page = memVector.elementAt(j);
                if (tmp_page.physical == page.physical && page.physical >= 0) {
                    physical_count++;
                }
            }
            if (physical_count > 1) {
                System.out.println("MemoryManagement: Duplicate physical page's in " + config);
                System.exit(-1);
            }
            physical_count = 0;
        }
        for (i = 0; i < virtualPageNum; i++) {
            Page page = memVector.elementAt(i);
            if (page.physical == -1) {
                controlPanel.removePhysicalPage(i);
            } else {
                controlPanel.addPhysicalPage(i, page.physical);
            }
        }
        for (i = 0; i < instructVector.size(); i++) {
            high = block * (virtualPageNum + 1) - 1;
            Instruction instruct = instructVector.elementAt(i);
            if (instruct.address < 0 || instruct.address > high) {
                System.out.println("MemoryManagement: Instruction (" + instruct.instruction + " " + instruct.address + ") out of bounds.");
                System.exit(-1);
            }
        }
    }

    public void setControlPanel(ControlPanel newControlPanel) {
        controlPanel = newControlPanel;
    }

    public void getPage(int pageNum) {
        Page page = memVector.elementAt(pageNum);
        controlPanel.paintPage(page);
    }

    private void printLogFile(String message) {
        String line;
        StringBuilder temp = new StringBuilder();
        File trace = new File(output);
        if (trace.exists()) {
            try {
                DataInputStream in = new DataInputStream(new FileInputStream(output));
                while ((line = in.readLine()) != null) {
                    temp.append(line).append(lineSeparator);
                }
                in.close();
            } catch (IOException e) {
                /* Do nothing */
            }
        }
        try {
            PrintStream out = new PrintStream(new FileOutputStream(output));
            out.print(temp);
            out.print(message);
            out.close();
        } catch (IOException e) {
            /* Do nothing */
        }
    }

    public void run() {
        step();
        while (runs != runCycles) {
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                /* Do nothing */
            }
            step();
        }
    }

    public void step() {
        int i;
        Instruction instruction = instructVector.elementAt(runs);
        controlPanel.instructionValueLabel.setText(instruction.instruction);
        controlPanel.addressValueLabel.setText(Long.toString(instruction.address, addressRadix));
        getPage(Virtual2Physical.pageNum(instruction.address, virtualPageNum, block));
        if (Objects.equals(controlPanel.pageFaultValueLabel.getText(), "YES")) {
            controlPanel.pageFaultValueLabel.setText("NO");
        }
        if (instruction.instruction.startsWith("READ")) {
            Page page = memVector.elementAt(Virtual2Physical.pageNum(instruction.address, virtualPageNum, block));
            if (page.physical == -1) {
                if (doFileLog) {
                    faultNumber++;
                    printLogFile("READ " + Long.toString(instruction.address, addressRadix) + " ... page fault");
                }
                if (doStdoutLog) {
                    faultNumber++;
                    System.out.println("READ " + Long.toString(instruction.address, addressRadix) + " ... page fault");
                }
                PageFault.replacePage(memVector, Virtual2Physical.pageNum(instruction.address, virtualPageNum, block), controlPanel);
                controlPanel.pageFaultValueLabel.setText("YES");
            } else {
                page.R = 1;
                page.lastTouchTime = 0;
                if (doFileLog) {
                    printLogFile("READ " + Long.toString(instruction.address, addressRadix) + " ... okay");
                }
                if (doStdoutLog) {
                    System.out.println("READ " + Long.toString(instruction.address, addressRadix) + " ... okay");
                }
            }
        }
        if (instruction.instruction.startsWith("WRITE")) {
            Page page = memVector.elementAt(Virtual2Physical.pageNum(instruction.address, virtualPageNum, block));
            if (page.physical == -1) {
                if (doFileLog) {
                    faultNumber++;
                    printLogFile("WRITE " + Long.toString(instruction.address, addressRadix) + " ... page fault");
                }
                if (doStdoutLog) {
                    faultNumber++;
                    System.out.println("WRITE " + Long.toString(instruction.address, addressRadix) + " ... page fault");
                }
                PageFault.replacePage(memVector, Virtual2Physical.pageNum(instruction.address, virtualPageNum, block), controlPanel);
                controlPanel.pageFaultValueLabel.setText("YES");
            } else {
                page.M = 1;
                page.lastTouchTime = 0;
                if (doFileLog) {
                    printLogFile("WRITE " + Long.toString(instruction.address, addressRadix) + " ... okay");
                }
                if (doStdoutLog) {
                    System.out.println("WRITE " + Long.toString(instruction.address, addressRadix) + " ... okay");
                }
            }
        }
        for (i = 0; i <= virtualPageNum; i++) {
            Page page = memVector.elementAt(i);
            if (page.physical != -1) {
                page.inMemTime = page.inMemTime + 10;
                page.lastTouchTime = page.lastTouchTime + 10;
            }
        }
        runs++;
        controlPanel.timeValueLabel.setText(runs * 10 + " (ns)");
        controlPanel.pageFaultCountLabel.setText(String.valueOf(faultNumber));
    }

    public void reset() {
        memVector.removeAllElements();
        instructVector.removeAllElements();
        controlPanel.statusValueLabel.setText("STOP");
        controlPanel.timeValueLabel.setText("0");
        controlPanel.instructionValueLabel.setText("NONE");
        controlPanel.addressValueLabel.setText("NULL");
        controlPanel.pageFaultValueLabel.setText("NO");
        controlPanel.pageFaultCountLabel.setText("0");
        controlPanel.virtualPageValueLabel.setText("x");
        controlPanel.physicalPageValueLabel.setText("0");
        controlPanel.RValueLabel.setText("0");
        controlPanel.MValueLabel.setText("0");
        controlPanel.inMemTimeValueLabel.setText("0");
        controlPanel.lastTouchTimeValueLabel.setText("0");
        controlPanel.lowValueLabel.setText("0");
        controlPanel.highValueLabel.setText("0");
        init(command_file, config_file);
    }
}
