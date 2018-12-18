public class BaigneurTest {
    public static void main(String args[]) {
        Piscine piscine = new Piscine();    //la piscine
        int n = 150;
        Thread[] baigneurs = new Thread[n];
        for (int i = 0; i < n; i++)         //les baigneurs
            baigneurs[i] = new Thread( new Baigneur(piscine, 5) );
            baigneurs[i].start();
        }
}
