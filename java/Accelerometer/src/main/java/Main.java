import gnu.io.*;

import java.io.IOException;
import java.io.InputStream;

//My first project with Java
public class Main {

    public static void main(String[] args) {
        try {
            (new Main()).connect("/dev/rfcomm0");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    void connect(String portName) throws Exception {
        CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
        if (portIdentifier.isCurrentlyOwned()) {
            System.out.println("Error: Port is currently in use");
        } else {
            CommPort commPort = portIdentifier.open(this.getClass().getName(), 2000);

            if (commPort instanceof SerialPort) {
                SerialPort serialPort = (SerialPort) commPort;
                serialPort.setSerialPortParams(115200, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.FLOWCONTROL_NONE);

                InputStream in = serialPort.getInputStream();
                (new Thread(new SerialReader(in))).start();

            } else {
                System.out.println("Error: Only serial ports are handled by this example.");
            }
        }
    }

    class SerialReader implements Runnable {

        private final int DOUBLED_PCKG_LENGHT = 9 * 2;
        private final InputStream inputStream;

        public SerialReader(InputStream in) {
            this.inputStream = in;
        }

        public void run() {
            try {
                if (inputStream.available() > DOUBLED_PCKG_LENGHT) { // if package start is slided
                    int value;
                    while ((value = inputStream.read()) > 0) {
                        if (value == 10 && inputStream.read() == 13) { // read \n\r
                            Coordinates coordinates = new Coordinates();
                            coordinates.setX((short) ((inputStream.read() << 8) + inputStream.read()));
                            inputStream.read();//read comma
                            coordinates.setY((short) ((inputStream.read() << 8) + inputStream.read()));
                            inputStream.read();//read comma
                            coordinates.setZ((short) ((inputStream.read() << 8) + inputStream.read()));
                            toSphericalCoordinateSystemV2(coordinates);
                            System.out.println(coordinates);
                        }
                    }
                }
            } catch (IOException ioe) {
                System.out.println("IOException");
                ioe.printStackTrace();
            }
        }//0699981257

        private void toSphericalCoordinateSystemV2(Coordinates coordinates) {
            try {
                int x = coordinates.getX();
                int y = coordinates.getY();
                int z = coordinates.getZ();
                double pitch;
                double roll;
                double yaw;

                pitch = (int) (Math.atan(x / Math.sqrt((y * y) + (z * z))) * 100);
                roll = (int) (Math.atan(y / Math.sqrt((x * x) + (z * z))) * 100);
                yaw = (int) (Math.atan(Math.sqrt((x * x) + (y * y)) / z) * 100);

                coordinates.setRoll(roll);
                coordinates.setPitch(pitch);
                coordinates.setYaw(yaw);
            } catch (ArithmeticException ae) {
                System.out.println("Divide by zero");
            }
        }
    }


    static void toSphericalCoordinateSystem(Coordinates coordinates) {
        try {
            int x = coordinates.getX();
            int y = coordinates.getY();
            int z = coordinates.getZ();
            int Zenit;
            int Azimut;
            double r = (Math.sqrt((x * x) + (y * y) + (z * z)));
            if (!(r == 0)) {
                Zenit = z == 0 ? 0 : (int) (((Math.acos(z / r)) * 180) / Math.PI);
                Azimut = x == 0 || y == 0 ? 0 : (int) ((((Math.atan(y / x)) * 180) / Math.PI));
            } else {
                Zenit = 360;
                Azimut = 360;
            }
            coordinates.setAzimut(Azimut);
            coordinates.setZenit(Zenit);
        } catch (ArithmeticException ae) {
            System.out.println("Divide by zero");
        }
    }


}
