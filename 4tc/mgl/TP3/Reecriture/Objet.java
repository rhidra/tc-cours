import java.awt.*;

/**
 * Objet élémentaire physique, qui peut-être affiché à l'écran,
 * être contenu dans l'environnement, et intéragir avec les rayons.
 * Est défini par une position et une direction (ou normale dans certains cas),
 * ainsi qu'un nom.
 */

public abstract class Objet {
	// Nom de l'objet, généralement affiché lors de l'affichage avancé.
    public String nom;
    public Vecteur position;
    public Vecteur direction;
    
    public Objet () {
        this.nom = "Sans_nom";
        this.position = new Vecteur();
        this.direction = new Vecteur(1,0);
    }
    
    public Objet (String nom) {
        this.nom = nom;
        this.position = new Vecteur();
        this.direction = new Vecteur(1,0);        
    }
    
    public Objet (String nom, Vecteur pos) {
        this.nom = nom;
        this.position = pos;
        this.direction = new Vecteur(1,0);        
    }    
    
    public Objet (String nom, Vecteur pos, Vecteur dir) {
        this.nom = nom;
        this.position = pos;
        this.direction = dir.vecteurNormalise();        
    }   
    
    public Objet(Objet o) {
        this.nom = new String(o.nom);
        this.position = new Vecteur(o.position);
        this.direction = new Vecteur(o.direction);
    }
    
    public String toString (){
        return nom;
    }
    
    // Teste l'intersection avec un rayon
	public abstract Vecteur intersection(Rayon r);
    
    // Dessine l'objet dans l'environnement.
    public abstract void dessine (Graphics g, boolean advanced);
}

