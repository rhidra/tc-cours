import java.awt.*;

/**
 * Cette classe représente un objet physique de type miroir.
 * Un miroir réfléchi chaque rayon de lumière selon les lois de Descartes :
 * Tout rayon incident qui intersecte le plan du miroir avec un certain angle
 * à la normale au plan, est réfléchi par ce même angle à la normale au plan.
 * Pour obtenir les formules de manière vectorielle, sans passer par les angles,
 * nous nous sommes référé à cette source :
 * http://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
 * 
 * ATTENTION : Pour une raison inconnue, le miroir ne fonctionne pas correctement !
 * En effet, certains rayons (répartis de manière discrète et aléatoire) ne sont pas réfléchis.
 * Afin d'avoir un résultat physiquement correct, il est conseillé d'émettre un nombre 
 * important de rayons, pour diminuer la probabilité d'avoir des "aberrations".
 */
 
public class Miroir extends Objet {
	//Couleur du miroir
    public final Color color = new Color(17, 194, 238);
    
	// Epaisseur affichée de l'écran, sans réalité physique.
    public final int EPAISSEUR = 2;
    
    public double longueur;
    
    public Miroir () {
        super("Miroir");
        this.longueur = 100;
    }

    public Miroir (String nom) {
        super(nom);
        this.longueur = 0.0; 
    }

    public Miroir (String nom, Vecteur pos) {
        super(nom, pos);
        this.longueur = 0.0; 
    }

    public Miroir (String nom, Vecteur pos, double l) {
        super(nom, pos);
        this.longueur = l; 
    }

    public Miroir (String nom, Vecteur pos, Vecteur dir, double l) {
        super(nom, pos, dir);
        this.longueur = l; 
    }

    public Miroir (Vecteur pos) {
        super("Miroir",pos);
        this.longueur = 0.0; 
    }

    public Miroir (Vecteur pos, double l) {
        super("Miroir",pos);
        this.longueur = l; 
    }
    
    public Miroir (Vecteur pos, Vecteur dir) {
        super("Miroir",pos, dir);
        this.longueur = 0.0;
    }

    public Miroir (Vecteur pos, Vecteur dir, double l) {
        super("Miroir",pos, dir);
        this.longueur = l;
    }
    
    public Miroir(Miroir m) {
        super(m);
        this.longueur = m.longueur;
    }
    
    // Teste l'intersection entre un rayon et le miroir.
    public Vecteur intersection(Rayon r) {
		// a et b sont le début et la fin du miroir
		Vecteur a = direction.rotationHoraire().multiply((double)longueur/2).add(position);
		Vecteur b = direction.rotationAntihoraire().multiply((double)longueur/2).add(position);
		
	    Vecteur s1 = new Vecteur(b.x - a.x, b.y - a.y);
	    Vecteur s2 = new Vecteur(r.end.x - r.start.x, r.end.y - r.start.y);
	
	    double s = (-s1.y * (a.x - r.start.x) + s1.x * (a.y - r.start.y)) / (-s2.x * s1.y + s1.x * s2.y);
	    double t = ( s2.x * (a.y - r.start.y) - s2.y * (a.x - r.start.x)) / (-s2.x * s1.y + s1.x * s2.y);
	
	    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
	    	return new Vecteur(a.x + (t * s1.x), a.y + (t * s1.y));
	    }
	
	    return r.end; // Pas de collision
	}

	// Dessine le miroir
	// Le mode avancé affiche le nom du miroir, ainsi que sa normale.
    public void dessine(Graphics g, boolean advanced) {
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
		
		if (advanced) {
			g.setColor(new Color(255-MainPanel.backgroundColor.getRed(), 255-MainPanel.backgroundColor.getGreen(), 255-MainPanel.backgroundColor.getBlue()));
			g.drawLine((int)position.add(direction.multiply(-100)).x, (int)position.add(direction.multiply(-100)).y, 
					(int)position.add(direction.multiply(100)).x, (int)position.add(direction.multiply(100)).y);
			g.drawString(nom, (int)position.x - g.getFontMetrics().stringWidth(nom)/2, (int)position.y - 10 - (int)longueur/2);
		}
    }
}


