public class PaquetImage implements Paquet {
    public void accept(RouteurInterface routeur) {
        routeur.visit(this);
    }
}
