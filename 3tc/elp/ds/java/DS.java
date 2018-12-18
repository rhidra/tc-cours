import java.net.*;
import java.io.*;
import java.util.*;

public class DS {
    public static void main(String[] args) {
        int lignesLues = 0;
        int lignesEcrites = 0;

        if (args.length == 1) {
            System.out.println("Usage: java DS [option] ('d' pour inclure les doublons et 'n' pour les retirer)");
        }

        try {
            URL url = new URL("https://liris.cnrs.fr/tristan.roussillon/ens/proc");
            InputStream is = url.openConnection().getInputStream();
            BufferedReader in = new BufferedReader(new InputStreamReader(is));
            String line = "";

            PrintWriter w = new PrintWriter(new OutputStreamWriter(new FileOutputStream("out.txt")));

            if (args[1] != "d") { // Avec java DS d, on inclu des doublons
                while((line = in.readLine()) != null) {
                    w.println(line);
                    lignesLues++;
                    lignesEcrites++;
                }
            } else if (args[1] == "n") {
                Set<String> s = new HashSet<>();

                while((line = in.readLine()) != null) {
                    s.add(line);
                    lignesLues++;
                }

                for (String str : s) {
                    w.println(str);
                    lignesEcrites++;
                }
            }
        } catch (IOException e) {
            System.out.println("ERREUR : "+e);
        } finally {
            System.out.println("Nombre de lignes lues = "+lignesLues);
            System.out.println("Nombre de lignes écrites = "+lignesEcrites);
        }
    }
}
