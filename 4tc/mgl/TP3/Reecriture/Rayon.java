import java.util.ArrayList;
import java.awt.*;
import java.io.*;

/**
 * Rayon représente un rayon élémentaire caractérisé par
 * un début et une fin. La fin d'un rayon peut-être l'intersection de ce dernier avec un élément.
 * Inclue toutes les méthodes utiles pour tracer des rayons.
 */

public class Rayon {
	public Vecteur start;
	public Vecteur end;

	// Indice du milieu dans lequel évolue le rayon
	public double indiceMilieu;

	// La puissance correspond à l'intensité lors de l'affichage.
	// puissance = 1 -> Rayon intense ||| puissance = 0 -> Rayon invisible
	public double puissance = 1;

	// La longueur maximale d'un rayon correspond à la diagonale de l'écran, le carré permet de rajouter une marge supplémentaire.
	public static int LONGUEUR_MAX = 2*Simulation.WIDTH*Simulation.HEIGHT;

	public Rayon(Vecteur start, Vecteur end, double indice, double puissance) {
		this.start = start;
		this.end = end;
		this.indiceMilieu = indice;
		this.puissance = puissance;
	}

	public Rayon() {
		this.start = new Vecteur(0,0);
		this.end = new Vecteur(1,0);
	}

	/**
	 * Renvoie le rayon correspondant aux conditions de position et de direction donné
	 * dont la fin se situe à l'infini.
	 * @param src Point de départ du rayon.
	 * @param dir Direction de départ du rayon.
	 * @return Le rayon projeté à l'infini.
	 */
	 public static Rayon rayonInfini(Vecteur src, Vecteur dir, double indice, double puissance) {
		 Rayon r = new Rayon(src, dir.multiply(LONGUEUR_MAX).add(src), indice, puissance);
		 System.out.println(dir.multiply(LONGUEUR_MAX).add(src));
		 return r;
	 }

     public void dessine(Graphics g) {
		 g.setColor(new Color(g.getColor().getRed(), g.getColor().getGreen(), g.getColor().getBlue(), (int)(255*puissance)));
         g.drawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y);
     }

	 public Objet intersecte(Objet o) {
		Vecteur endOld = this.end;
		this.end = o.intersection(this);

		if (!endOld.equals(this.end))
			return o;

		if (this.start.equals(this.end))
			this.end = endOld;

		return null;
	 }

     public String toString() {
		 return "Rayon:[debut="+start+";fin="+end+";indice="+indiceMilieu+";power="+puissance+"]";
	 }
}
