public class PaquetVoix implements Paquet {
    public void accept(RouteurInterface routeur) {
        routeur.visit(this);
    }
}
