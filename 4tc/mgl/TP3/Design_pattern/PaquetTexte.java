public class PaquetTexte implements Paquet {
    public void accept(RouteurInterface routeur) {
        routeur.visit(this);
    }
}
