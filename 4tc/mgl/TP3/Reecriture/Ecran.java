import java.awt.Graphics;
import java.awt.Color;
import java.awt.Polygon;

/**
 * Cette classe représente un objet physique de type écran.
 * Un écran peut bloquer le passage de la lumière sur un segment.
 */

public class Ecran extends Objet {
	// Epaisseur affichée de l'écran, sans réalité physique.
	public final int EPAISSEUR = 2;
    public final Color color = new Color(155,76,13);
    public double longueur;
    
    public Ecran () {
        super("Ecran");
        this.longueur = 100.; 
    }

    public Ecran (String nom) {
        super(nom);
        this.longueur = 100.; 
    }

    public Ecran (String nom, Vecteur pos) {
        super(nom, pos);
        this.longueur = 100.; 
    }

    public Ecran (String nom, Vecteur pos, double l) {
        super(nom, pos);
        this.longueur = l; 
    }

    public Ecran (String nom, Vecteur pos, Vecteur dir, double l) {
        super(nom, pos, dir);
        this.longueur = l; 
    }

    public Ecran (Vecteur pos) {
        super("Ecran",pos);
        this.longueur = 50.; 
    }

    public Ecran (Vecteur pos, double l) {
        super("Ecran",pos);
        this.longueur = l; 
    }
    
    public Ecran (Vecteur pos, Vecteur dir) {
        super("Ecran",pos, dir);
        this.longueur = 50.;
    }

    public Ecran (Vecteur pos, Vecteur dir, double l) {
        super("Ecran",pos, dir);
        this.longueur = l;
    }
    
    public Ecran(Ecran e) {
        super(e);
        this.longueur = e.longueur;
    }
    
    // Teste l'intersection entre un rayon et l'écran.
    public Vecteur intersection(Rayon r) {
		// a et b sont le début et la fin de l'écran (du segment).
		Vecteur a = direction.rotationHoraire().multiply((double)longueur/2).add(position);
		Vecteur b = direction.rotationAntihoraire().multiply((double)longueur/2).add(position);
		
	    Vecteur s1 = new Vecteur(b.x - a.x, b.y - a.y);
	    Vecteur s2 = new Vecteur(r.end.x - r.start.x, r.end.y - r.start.y);
	
	    double s = (-s1.y * (a.x - r.start.x) + s1.x * (a.y - r.start.y)) / (-s2.x * s1.y + s1.x * s2.y);
	    double t = ( s2.x * (a.y - r.start.y) - s2.y * (a.x - r.start.x)) / (-s2.x * s1.y + s1.x * s2.y);
	
	    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
	    	return new Vecteur(a.x + (t * s1.x), a.y + (t * s1.y));
	    }
	
		// S'il n'y a pas eu d'intersection, on renvoie la fin du rayon.
	    return r.end;
	}
	
	public void dessine(Graphics g, boolean advanced){
        Vecteur u = direction.rotationHoraire();
        Vecteur v = direction.rotationAntihoraire();
        Polygon p = new Polygon();
        Vecteur a = u.multiply(longueur/2).add(u.rotationHoraire().multiply(EPAISSEUR)).add(position);
        Vecteur b = u.multiply(longueur/2).add(u.rotationAntihoraire().multiply(EPAISSEUR)).add(position);
        Vecteur c = v.multiply(longueur/2).add(u.rotationAntihoraire().multiply(EPAISSEUR)).add(position);
        Vecteur d = v.multiply(longueur/2).add(u.rotationHoraire().multiply(EPAISSEUR)).add(position);
        p.addPoint((int)a.x, (int)a.y);
        p.addPoint((int)b.x, (int)b.y);
        p.addPoint((int)c.x, (int)c.y);
        p.addPoint((int)d.x, (int)d.y);
        
        g.setColor(color);
        g.fillPolygon(p);
		
		// Le mode avancé permet d'afficher le nom de l'écran
		if (advanced) {
			g.setColor(new Color(255-MainPanel.backgroundColor.getRed(), 255-MainPanel.backgroundColor.getGreen(), 255-MainPanel.backgroundColor.getBlue()));
			g.drawString(nom, (int)position.x - g.getFontMetrics().stringWidth(nom)/2, (int)position.y - 10 - (int)longueur/2);
		}
    }
}

