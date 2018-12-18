import java.io.*;

public class Copy {
    private static void copy(InputStream in, OutputStream out) throws IOException {
        int o;
        while ((o = in.read()) != -1) {
            out.write(o);
        }
        in.close();
        out.close();
    }

    public static void main(String args[]) {
        try {
        FileInputStream in = new FileInputStream(new File("GroupeEtudiant.java"));
        FileOutputStream out = new FileOutputStream(new File("Copy_GroupeEtudiant.java"));
            copy(in, out);
        } catch (IOException e) {
            System.out.println(e);
        }
    }
}
