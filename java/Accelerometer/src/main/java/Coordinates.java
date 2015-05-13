/**
 * Created by FreeUser on 08.11.14.
 */

public class Coordinates {
    short x;
    short y;
    short z;

    double Zenit = 0.0d;
    double Azimut = 0.0d;

    double yaw;
    double pitch;
    double roll;

    public Coordinates() {
    }

    public short getX() {
        return x;
    }

    public void setX(short x) {
        this.x = x;
    }

    public short getY() {
        return y;
    }

    public void setY(short y) {
        this.y = y;
    }

    public short getZ() {
        return z;
    }

    public void setZ(short z) {
        this.z = z;
    }

    public double getZenit() {
        return Zenit;
    }

    public void setZenit(double zenit) {
        Zenit = zenit;
    }

    public double getAzimut() {
        return Azimut;
    }

    public void setAzimut(double azimut) {
        Azimut = azimut;
    }

    public double getYaw() {
        return yaw;
    }

    public void setYaw(double yaw) {
        this.yaw = yaw;
    }

    public double getPitch() {
        return pitch;
    }

    public void setPitch(double pitch) {
        this.pitch = pitch;
    }

    public double getRoll() {
        return roll;
    }

    public void setRoll(double roll) {
        this.roll = roll;
    }
//
//    @Override
    public String toString() {
        return "|_____|  \n\n\n\n\n\n\n\n\n" +
                (x <= 1000 && x >= -1000 ? x <= 100 && x >= -100 ? x <= 10 && x >= -10 ? x >= 0 ? x + "     |_____________|      " : x + "     |_____________|      " : x + "    |_____________|      " : x + "   |_____________|      " : x + "  |_____________|      ") +
                (y <= 1000 && y >= -1000 ? y <= 100 && y >= -100 ? y <= 10 && y >= -10 ? y >= 0 ? y + "     |_____________|      " : y + "     |_____________|      " : y + "    |_____________|      " : y + "   |_____________|      " : y + "  |_____________|      ") +
                (z <= 1000 && z >= -1000 ? z <= 100 && z >= -100 ? z <= 10 && z >= -10 ? z >= 0 ? z + "     |_____________|      " : z + "     |_____________|      " : z + "    |_____________|      " : z + "   |_____________|      " : z + "  |_____________|      ") ;
//                (Zenit <= 1000 && Zenit >= -1000 ? Zenit <= 100 && Zenit >= -100 ? Zenit <= 10 && Zenit >= -10 ? Zenit >= 0 ? Zenit + "      |_____________|      " : Zenit + "     |_____________|      " : Zenit + "    |_____________|      " : Zenit + "   |_____________|      " : Zenit + "  |_____________|      ") +
//                (Azimut <= 1000 && Azimut >= -1000 ? Azimut <= 100 && Azimut >= -100 ? Azimut <= 10 && Azimut >= -10 ? Azimut >= 0 ? Azimut + "      |_____________|      " : Azimut + "     |_____________|      " : Azimut + "    |_____________|      " : Azimut + "   |_____________|      " : Azimut + "  |_____________|      ") +
//                (roll <= 1000 && roll >= -1000 ? roll <= 100 && roll >= -100 ? roll <= 10 && roll >= -10 ? roll >= 0 ? roll + "  |_____________|  " : roll + " |_____________|  " : roll + "|_____________|  " : roll + "|____________|  " : roll + "|___________|  ") +
//                (pitch<= 1000 && pitch>= -1000 ? pitch<= 100 && pitch>= -100 ? pitch<= 10 && pitch>= -10 ? pitch>= 0 ? pitch+ "  |_____________|  " : pitch+ " |_____________|  " : pitch+ "|_____________|  " : pitch+ "|____________|  " : pitch + "|___________|  ") +
//                (yaw<= 1000 && yaw>= -1000 ? yaw <= 100 && yaw >= -100 ? yaw <= 10 && yaw >= -10 ? yaw >= 0 ? yaw + "  |_____________|  " : yaw+ " |_____________|  " : yaw+ "|____________|  " : yaw+ "|____________|  " : yaw + "  |____________|  ");
    }
//    @Override
//    public String toString() {
//        return "|_____|  \n\n\n\n\n\n\n\n" +
//                (roll <= 1000 && roll >= -1000 ? roll <= 100 && roll >= -100 ? roll <= 10 && roll >= -10 ? roll >= 0 ? roll + "  |_____________|  " : roll + " |_____________|  " : roll + "|_____________|  " : roll + "|____________|  " : roll + "|___________|  ") +
//                (pitch<= 1000 && pitch>= -1000 ? pitch<= 100 && pitch>= -100 ? pitch<= 10 && pitch>= -10 ? pitch>= 0 ? pitch+ "  |_____________|  " : pitch+ " |_____________|  " : pitch+ "|_____________|  " : pitch+ "|____________|  " : pitch + "|___________|  ") +
//                (yaw<= 1000 && yaw>= -1000 ? yaw <= 100 && yaw >= -100 ? yaw <= 10 && yaw >= -10 ? yaw >= 0 ? yaw + "  |_____________|  " : yaw+ " |_____________|  " : yaw+ "|____________|  " : yaw+ "|____________|  " : yaw + "  |____________|  ");
//    }
}
