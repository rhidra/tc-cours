public class PaquetVideo implements Paquet {
    public void accept(RouteurInterface routeur) {
        routeur.visit(this);
    }
}
