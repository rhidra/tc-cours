public class PaquetControle implements Paquet {
    public void accept(RouteurInterface routeur) {
        routeur.visit(this);
    }
}
