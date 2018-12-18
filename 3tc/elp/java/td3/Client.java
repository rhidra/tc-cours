import java.net.*;
import java.io.*;
import java.util.*;

public class Client {
    public static void main(String args[]) {
        try {
            Socket socket = new Socket("localhost", 8888);
            PrintWriter w = new PrintWriter(socket.getOutputStream(), true);
            Scanner sc = new Scanner(System.in);
            String line = "";
            System.out.println("To stop write \"STOP\"");
            
            while(!line.equals("STOP")) {
                line = sc.nextLine();
                w.println(line);
            }
            w.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
