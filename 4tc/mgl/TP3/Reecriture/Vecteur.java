import java.io.Serializable;

/**
 * Un vecteur représente un point du plan de coordonnées (x,y).
 * On peut lui opérer plusieurs opérations mathématiques vectorielles,
 * telles que l'addition, la soustraction, le produit scalaire.
 * Il est aussi possible de récupérer son angle par rapport à un autre vecteur,
 * ou encore d'effectuer une rotation vectorielle.
 */

public class Vecteur implements Serializable {
	// Coordonnées du vecteur
    public double x,y;
    
    public Vecteur(double x, double y){
        this.x = x;
        this.y = y;
    }
    
    public Vecteur(int a, int b){
        x = (double) a;
        y = (double) b;
    }
     
    public Vecteur(){
        x = 0.0;
        y = 0.0;
    }
    
    public Vecteur(Vecteur v) {
        x = v.x;
        y = v.y;
    }
	
	// Addition
    public Vecteur add(Vecteur v){
        return new Vecteur (this.x + v.x , this.y + v.y );
    }
	
	// Soustraction
    public Vecteur substract(Vecteur v){
        return new Vecteur (this.x - v.x , this.y - v.y );
    }
    
    // Produit par un scalaire
    public Vecteur multiply(double a){
        return new Vecteur (a*x , a*y);
    }
    
    // Test d'égalité
    public boolean equals(Vecteur v){
        return (this.x == v.x && this.y == v.y);
    }
    
    // Produit scalaire
    public double scalaire(Vecteur v){
        return this.x*v.x + this.y*v.y;
    }
    
    // Norme du vecteur, lente à l'exécution
    public double norme(){
        return Math.sqrt(x*x+y*y);
    }
    
    // Norme au carrée du vecteur, rapide à l'exécution
    public double normeCarree(){
        return x*x+y*y;
    }
    
    // Opposé du vecteur.
    public Vecteur opposite() {
		return this.multiply(-1);
	}
    
    // Vecteur unitaire
    public Vecteur vecteurNormalise(){
		double norme = norme();
        return new Vecteur(x/norme, y/norme);
    }
    
    // Vecteur unitaire correspondant à l'angle (en radians) avec l'axe x correspondant.
    public static Vecteur angleToVecteur(double theta){
        return new Vecteur(Math.cos(theta), Math.sin(theta)); 
    }
    
    // Angle (en radians) du vecteur par rapport à l'axe x.
    public static double VecteurToAngle(Vecteur v){
        return Math.atan2(v.y, v.x);
    }
    
    // Angle (en radians) du vecteur par rapport à l'axe x.
    public double VecteurToAngle() {
        return VecteurToAngle(this);
    }
    
    // Converti l'angle radians -> degrés
	public static double radianToDegre(double radian) {
        return ((radian*180)/Math.PI);
    }
    
    // Converti l'angle degrés -> radians
	public static double degreToRadian(double degre) {
        return Math.toRadians(degre);
    }
    
    public String toString() {
        return "(" +x+ ", "+y+")";
    }
    
    // Fait tourner le vecteur de 90° dans le sens horaire.
    public Vecteur rotationHoraire() {
		return new Vecteur(-y, x);
	}
    
    // Fait tourner le vecteur d'un angle de 90° dans le sens antihoraire.
    public Vecteur rotationAntihoraire() {
		return new Vecteur(y, -x);
	}
	
	// Effectue une rotation du vecteur par l'angle en radians.
	public Vecteur rotation(double a) {
		return new Vecteur(x*Math.cos(a) - y*Math.sin(a), x*Math.sin(a) + y*Math.cos(a));
	}
	
	// Renvoie l'angle (en radians, entre -Pi et Pi) entre deux vecteurs.
	public static double angle(Vecteur a, Vecteur b) {
		return Math.atan2(b.y, b.x) - Math.atan2(a.y, a.x);
	}
	
	// Renvoie l'angle (en radians, entre -Pi et Pi) entre deux vecteurs.
	public double angle(Vecteur a) {
		return angle(this, a);
	}
    
	// Renvoie l'angle (en radians, entre -Pi et Pi) entre deux vecteurs.
    public double getAngle() {
        return angle(new Vecteur(1, 0));
    }
    
    // Distance entre deux vecteurs
    public double distance(Vecteur p) {
		return substract(p).norme();
	}
}

