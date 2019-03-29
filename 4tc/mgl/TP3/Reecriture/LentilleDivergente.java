import java.awt.*;

/**
 * LentilleDivergente représente une lentille convergente classique.
 * Notre modèle prend en compte l'épaisseur d'une lentille, 
 * contrairement à l'hypothèse des lentilles minces dans les conditions de Gauss.
 * Une lentille est définie par un assemblage de points discrets, 
 * qui tend vers l'infini pour une meilleure simulation.
 * De part cela, elle est définie de la même manière que n'importe quel
 * ObjetOptique.
 * Sa distance focale f<0 et sa hauteur permettent de déterminer la position
 * de ses points. La lentille divergente se définie aussi par son épaisseur, constante.
 */
 
public class LentilleDivergente extends ObjetOptique {
    private double distFocale;
    private double hauteur;
    private double epaisseur;
    public static final int echantillonnage = 50;
    
    public LentilleDivergente(Vecteur pos, double f, double h, double epaisseur) {
        // Pour une lentille divergente, f est négatif
        this.distFocale = -Math.abs(f);
        this.position = pos;
        this.indice = 1.5;
        this.hauteur = (h > 2*Math.abs(f)*(indice-1)) ? 2*Math.abs(f)*(indice-1)-1 : h; // On vérifie que h < hmax = R
        this.epaisseur = epaisseur;
        this.nom = "Lentille Divergente";
        
        init();
    }
    
    public LentilleDivergente(LentilleDivergente l) {
        super(l);
        setHauteur((int)l.hauteur);
        this.distFocale = l.distFocale;
        this.nom = "Lentille Divergente";
    }
    
    public LentilleDivergente() {
        super();
        distFocale = 500;
        epaisseur = 5;
        setHauteur(300);
        nom = "Lentille Divergente";
        init();
    }
    
    /**
     * Génère les points de la lentille divergente.
     * On génère la lentille divergente de la même manière que la lentille convergente :
     * On calcule rayon R de courbure de chaque côté, puis on crée les points correspondants.
     * Contrairement à la lentille convergente, un attribut d'épaisseur est présent, 
     * afin de gérer la distance entre les deux cercles à l'axe optique.
     * Idéalement, l'épaisseur est nulle, mais nous pouvons ainsi observer les
     * limites des conditions de Gauss en augmentant l'épaisseur de la lentille.
     * 
     * @param N Echantillonage (Résolution du polygône de la lentille)
     */
    public void init() {
        double r = 2*Math.abs(distFocale)*(indice-1); // Rayon de chaque cercle
		double l = r+epaisseur-Math.sqrt(r*r-hauteur*hauteur/4);
		int N = echantillonnage;
        double pas = Math.abs((l-epaisseur)/N);
        int i = 0;
        points = new Vecteur[N*4];
		// Partie supérieure Droite
		for (double x = -(r+epaisseur-l); i < N; i++, x -= pas) {
			points[i] = new Vecteur(x + r + epaisseur, Math.sqrt(r*r-x*x));
		}
		
		// Partie inférieure droite
		for (double x = - r; i < N*2; i++, x += pas) {
			points[i] = new Vecteur(x + r + epaisseur, - Math.sqrt(r*r-x*x));
		}
		
		// Partie inférieure gauche
		for (double x = r + epaisseur - l; i < N*3; i++, x += pas) {
			points[i] = new Vecteur(x - r - epaisseur, - Math.sqrt(r*r-x*x));
		}
		
		// Partie supèrieure gauche
		for (double x = r; i < N*4; i++, x -= pas) {
			points[i] = new Vecteur(x - r - epaisseur, Math.sqrt(r*r-x*x));
		}
    }
	
	// Dessin de la lentille divergente.
	// En mode avancé, on affiche le nom de la lentille, ainsi que ses points focaux.
	public void dessine(Graphics g, boolean advanced) {
		super.dessine(g, advanced);
		if (advanced) {
			g.setColor(new Color(255-MainPanel.backgroundColor.getRed(), 255-MainPanel.backgroundColor.getGreen(), 255-MainPanel.backgroundColor.getBlue()));
			g.drawLine((int)position.add(direction.multiply(-distFocale)).x, (int)position.add(direction.multiply(-distFocale)).y, 
						(int)position.add(direction.multiply(distFocale)).x, (int)position.add(direction.multiply(distFocale)).y);
			g.drawString("F'", (int)position.add(direction.multiply(-distFocale)).x, (int)position.add(direction.multiply(-distFocale)).y-5);
			g.drawString("F", (int)position.add(direction.multiply(distFocale)).x, (int)position.add(direction.multiply(distFocale)).y+16);
			g.fillOval((int)position.add(direction.multiply(-distFocale)).x-4, (int)position.add(direction.multiply(-distFocale)).y-4, 8, 8);
			g.fillOval((int)position.add(direction.multiply(distFocale)).x-4, (int)position.add(direction.multiply(distFocale)).y-4, 8, 8);
		}
	}
    
    public void setHauteur(int h) {
		hauteur = (h > 4*Math.abs(distFocale)*(indice-1)) ? 4*Math.abs(distFocale)*(indice-1)-1 : h;
	}
	
	public void setDistFocale(double f) {
		distFocale = f;
		setHauteur((int)hauteur);
	}
	
	public int getHauteur() {
		return (int)hauteur;
	}
	
	public int getDistFocale() {
		return (int)distFocale;
	}
	
	public void setIndice(double n) {
		super.setIndice(n);
		setHauteur((int)hauteur);
	}
}
