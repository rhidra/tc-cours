public class Simulation {
    public static void main(String args[]) {
        System.out.println("Début de la simulation ...");
        int n = (int)(Math.random() * 100 + 50);
        System.out.println("Génération de " + n + " paquets ...");

        try {
            Thread.sleep(1000);
        } catch (Exception e) {}

        Paquet[] paquets = new Paquet[n];

        for (int i = 0; i < n; i++) {
            switch((int)(Math.random() * 5)) {
                case 1:
                    paquets[i] = new PaquetTexte();
                    break;
                case 2:
                    paquets[i] = new PaquetVideo();
                    break;
                case 3:
                    paquets[i] = new PaquetControle();
                    break;
                case 4:
                    paquets[i] = new PaquetImage();
                    break;
                default:
                    paquets[i] = new PaquetVoix();
            }
        }

        Routeur routeur = new Routeur();
        System.out.println("Transfer des paquets ...");

        for (Paquet p : paquets) {
            try {
                Thread.sleep(100);
            } catch (Exception e) {}

            p.accept(routeur);
        }

        try {
            Thread.sleep(1000);
        } catch (Exception e) {}

        System.out.println("--- FIN DE LA SIMULATION ----");
        System.out.println(routeur);
    }
}
