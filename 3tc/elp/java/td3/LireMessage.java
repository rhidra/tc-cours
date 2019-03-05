import java.io.*;
import java.util.*;

public class LireMessage {
    public static void main(String args[]) {
        if (args.length < 1 || args.length > 1) {
            System.out.println("usage: java LireMessage <src>");
        } else {
            try {
                File src = new File(args[0]);
                FileInputStream fin = new FileInputStream(src);
                ObjectInputStream oin = new ObjectInputStream(fin);

                Message msg = (Message)oin.readObject();

                System.out.println(msg);
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }
}
