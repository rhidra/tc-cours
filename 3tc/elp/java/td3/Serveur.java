import java.net.*;
import java.io.*;

public class Serveur {
    public static void main(String args[]) {
        try {
            ServerSocket connection = new ServerSocket(8888);
            Socket socket = connection.accept();
            BufferedReader r = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter w = new PrintWriter(socket.getOutputStream(), true);

            String line = "";
            while ((line = r.readLine()) != null) {
                System.out.println(line);
                w.println(line);
            }
            w.close();
            r.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
