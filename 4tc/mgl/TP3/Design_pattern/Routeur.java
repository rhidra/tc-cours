interface RouteurInterface {
    public void visit(PaquetVoix paquet);
    public void visit(PaquetVideo paquet);
    public void visit(PaquetImage paquet);
    public void visit(PaquetTexte paquet);
    public void visit(PaquetControle paquet);
}

public class Routeur implements RouteurInterface {
    public int countVoix = 0;
    public int countVideo = 0;
    public int countImage = 0;
    public int countControle = 0;
    public int countTexte = 0;

    public void visit(PaquetVoix paquet) {
        System.out.println("Réception d'un paquet de voix ...");
        this.countVoix++;
    }

    public void visit(PaquetVideo paquet) {
        System.out.println("Réception d'un paquet de vidéo ...");
        this.countVideo++;
    }

    public void visit(PaquetImage paquet) {
        System.out.println("Réception d'un paquet d'image ...");
        this.countImage++;
    }

    public void visit(PaquetControle paquet) {
        System.out.println("Réception d'un paquet de contrôle ...");
        this.countControle++;
    }

    public void visit(PaquetTexte paquet) {
        System.out.println("Réception d'un paquet de texte ...");
        this.countTexte++;
    }

    public String toString() {
        String s = "\n\n";
        s += "----------------------------\n";
        s += "- Paquets Texte    : " + this.countTexte + "\n";
        s += "- Paquets Image    : " + this.countImage + "\n";
        s += "- Paquets Vidéo    : " + this.countVideo + "\n";
        s += "- Paquets Voix     : " + this.countVoix + "\n";
        s += "- Paquets Contrôle : " + this.countControle + "\n";
        s += "----------------------------";
        return s;
    }
}
