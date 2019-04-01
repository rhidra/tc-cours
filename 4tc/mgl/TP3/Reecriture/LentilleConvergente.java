import java.awt.*;

/**
 * LentilleConvergente représente une lentille convergente classique.
 * Notre modèle prend en compte l'épaisseur d'une lentille, 
 * contrairement à l'hypothèse des lentilles minces dans les conditions de Gauss.
 * Une lentille est définie par un assemblage de points discrets, 
 * qui tend vers l'infini pour une meilleure simulation.
 * De part cela, elle est définie de la même manière que n'importe quel
 * ObjetOptique.
 * Sa distance focale f>0 et sa hauteur permettent de déterminer la position
 * de ses points.
 */

public class LentilleConvergente extends ObjetOptique {
    private double distFocale;
    private double hauteur;
    
    // Variable proportionnelle à la quantité de points générés
    public static final int echantillonnage = 40;

    public LentilleConvergente(Vecteur pos, double f, double h) {
		this.nom = "Lentille Convergente";
        this.distFocale = Math.abs(f);
        this.position = pos;
        this.indice = 1.5;
        // On vérifie que h < hmax = R
        this.hauteur = (h > 2*distFocale*(indice-1)) ? 2*distFocale*(indice-1)-1 : h;
        
        init();
    }
    
    public LentilleConvergente(LentilleConvergente l) {
        super(l);
		this.nom = "Lentille Convergente";
        this.hauteur = l.hauteur;
        this.distFocale = l.distFocale;
    }
    
    public LentilleConvergente() {
        super();
		this.nom = "Lentille Convergente";
        hauteur = 100;
        distFocale = 100;
        indice = 1.5;
        init();
    }
    
    /**
     * Génère les points d'une lentille.
     * Une lentille convergente est définie par l’intersection de deux cercles $
     * de centres C1 et C2 (alignés sur l’axe optique) et de rayons R (lentille symétrique 
     * donc même rayon pour les deux cercles). Les données, définies par l’utilisateur sont f, 
     * H, et xC et yC les coordonnées du centre de la lentille. 
     * Si f est la distance focale et n l’indice du milieu de la lentille :
     * 1/f = 2*(n-1)/R soit R = 2*f*(n-1)
     * La distance entre les deux centres vaut l = 2*sqrt(R² – H²/4) avec H la hauteur de la lentille.
     * L’équation de création de la lentille est donc :
     * C1 : y = + sqrt(R² – (x - l/2 + xC)²) + yC et y = - sqrt(R² – (x – l/2 + xC)²) + yC avec l/2 < x < R
     * C2 : y = + sqrt(R² – (x + l/2 + xC)²) + yC et y = - sqrt(R² – (x + l/2 + xC)²) + yC avec -R < x < -l/2
    **/
    public void init() {
        double r = 2*distFocale*(indice-1); // Rayon de chaque cercle
        double l = 2*Math.sqrt(r*r - hauteur*hauteur/4); // Longueur entre C1 et C2
        int N = echantillonnage;
        double pas = (r-l/2)/N;
        int i = 0;
        points = new Vecteur[N*4];
        
        // Quart supérieur droit (centre C1)
        for (double x = l/2; i < N; x += pas, i++) {
            double y = Math.sqrt(r*r - (x)*(x));
            points[i] = new Vecteur(x-l/2, y);
        }
        
        // Quart inférieur droit (centre C1)
        for (double x = r; i < N*2; x -= pas, i++) {
            double y = - Math.sqrt(r*r - (x)*(x));
            points[i] = new Vecteur(x-l/2, y);
        }
        
        // Quart inférieur gauche (centre C2)
        for (double x = -l/2; i < N*3; x -= pas, i++) {
            double y = - Math.sqrt(r*r - (x)*(x));
            points[i] = new Vecteur(x+l/2, y);
        }
        
        // Quart supérieur gauche (centre C2)
        for (double x = -r; i < N*4; x += pas, i++) {
            double y = Math.sqrt(r*r - (x)*(x));
            points[i] = new Vecteur(x+l/2, y);
        }
    }
    
    public void setHauteur(double h) {
		hauteur = (h > 4*distFocale*(indice-1)) ? 4*distFocale*(indice-1)-1 : h;
	}
	
	public void setDistFocale(double f) {
		distFocale = f;
		setHauteur(hauteur);
	}
	
	public int getHauteur() {
		return (int)hauteur;
	}
	
	public int getDistFocale() {
		return (int)distFocale;
	}
	
	public void setIndice(double n) {
		super.setIndice(n);
		setHauteur(hauteur);
	}
	
	// Dessin de la lentille convergente.
	// En mode avancé, on affiche le nom de la lentille, ainsi que ses points focaux.
	public void dessine(Graphics g, boolean advanced) {
		super.dessine(g, advanced);
		if (advanced) {
			g.setColor(new Color(255-MainPanel.backgroundColor.getRed(), 255-MainPanel.backgroundColor.getGreen(), 255-MainPanel.backgroundColor.getBlue()));
			g.drawLine((int)position.add(direction.multiply(-distFocale)).x, (int)position.add(direction.multiply(-distFocale)).y, 
						(int)position.add(direction.multiply(distFocale)).x, (int)position.add(direction.multiply(distFocale)).y);
			g.drawString("F", (int)position.add(direction.multiply(-distFocale)).x, (int)position.add(direction.multiply(-distFocale)).y-5);
			g.drawString("F'", (int)position.add(direction.multiply(distFocale)).x, (int)position.add(direction.multiply(distFocale)).y+16);
			g.fillOval((int)position.add(direction.multiply(-distFocale)).x-4, (int)position.add(direction.multiply(-distFocale)).y-4, 8, 8);
			g.fillOval((int)position.add(direction.multiply(distFocale)).x-4, (int)position.add(direction.multiply(distFocale)).y-4, 8, 8);
		}
	}
}
