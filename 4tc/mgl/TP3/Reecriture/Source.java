import java.util.ArrayList;
import java.awt.*;

/**
 * Source représente une source physique.
 * Une source émet des rayons dans certaines directions.
 * On peut définir le nombre de rayons émis, ainsi que leur couleur.
 */

public class Source extends Objet {
	// Paramètre d'affichage de la source, sans impact physique
    public final int RAYON = 8;
    public final Color COLOR_SOURCE = Color.pink;

    // Répertorie les directions du départ de chaque rayon de la source
	public Vecteur[] departRayon;

	// Couleur des rayons émis
	public Color couleur;

	// Rayons émis par une même source
	public ArrayList<Rayon> rayons;

	public Source() {
		nom = "Source";
		departRayon = new Vecteur[1];
		departRayon[0] = new Vecteur(1,0);
		rayons = new ArrayList<Rayon>();
		couleur = Color.red;
	}

    public Source(Source s) {
        super(s);
		nom = "Source";
        rayons = new ArrayList<Rayon>(s.rayons);
        couleur = Color.red;
        departRayon = new Vecteur[s.departRayon.length];
        for (int i = 0; i < departRayon.length; i++)
            departRayon[i] = s.departRayon[i];
    }

	// Une source ne peut pas intéragir avec les rayons.
    public Vecteur intersection(Rayon r) {
        return r.end;
    }

	// Modifie le nombre de rayons affichés
	public void setNbrRayons(int nbRayons) {
		if (nbRayons > 0) {
			departRayon = new Vecteur[nbRayons];
			for (int i = 0; i < nbRayons; i++){
				departRayon[i] = Vecteur.angleToVecteur(i*2*Math.PI/nbRayons);	//Angle en radian transformé en vecteur
			}
		}
	}

	// Trace tous les rayons, en fonction de l'environnement passé en paramètre
	public void refresh(Objet[] obj) {
		rayons.clear();
		for (Vecteur v : departRayon) {
            RayTracing rt = new RayTracing();
            rt.src = position;
            rt.direction = v.rotation(direction.angle(new Vecteur(1,0)));
            rt.indice = Simulation.indiceEnvironnement;
            rt.obj = obj;
            rt.currentBounce = 0;
            rt.power = 1;
            Rayon r = RayTracing.tracer(rt);
			rayons.addAll(r);
		}
	}

	// Dessine la source, ainsi que les rayons qui lui sont associés
	public void dessine(Graphics g, boolean advanced) {
        g.setColor(COLOR_SOURCE);
		g.fillOval((int)(position.x - RAYON), (int)(position.y - RAYON), 2*RAYON, 2*RAYON);
        g.setColor(Color.black);
		g.drawOval((int)(position.x - RAYON), (int)(position.y - RAYON), 2*RAYON, 2*RAYON);

		// Dessin des rayons
        for (Rayon r : rayons) {
			g.setColor(couleur);
            r.dessine(g);
        }
	}
}
