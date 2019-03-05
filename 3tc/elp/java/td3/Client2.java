import java.net.*;
import java.io.*;
import java.util.*;

public class Client2 {
    public static void main(String args[]) {
        try {
            Socket socket = new Socket("localhost", 8888);
            PrintWriter w = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader r = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            Scanner sc = new Scanner(System.in);
            String line = "";
            System.out.println("To stop write \"STOP\"");

            while(!line.equals("STOP") && line!=null) {
                line = sc.nextLine();
                w.println(line);
                String input = r.readLine();
                System.out.println(input);
            }
            w.close();
            r.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
