import java.awt.Polygon;
import java.io.Serializable;
import java.awt.*;

/**
 * ObjetOptique quelconque, uniquement défini
 * par un assemblage de points, ainsi qu'un indice de réfraction.
 * Grâce à l'éditeur, il est possible de sauvegarder
 * des ObjetOptiques sur l'ordinateur. 
 * Pour cela, la classe implémente l'interface Serializable.
 */

public class ObjetOptique extends Objet implements Serializable {
	// Attribut nécessaire pour la sérialisation
	private static final long serialVersionUID = 42L;
	
    public final Color color = new Color(17, 194, 238);
    public Vecteur[] points;
    protected double indice;
    
    public ObjetOptique(Vecteur[] points) {
        this.points = new Vecteur[points.length];
        
        for (int i = 0; i < points.length; i++) {
            this.points[i] = points[i];
        }
    }
    
    public ObjetOptique() {
        points = new Vecteur[0];
        indice = 1.5;
    }
    
    public ObjetOptique(ObjetOptique o) {
        super(o);
        indice = o.indice;
        points = new Vecteur[o.points.length];
        for (int i = 0; i < o.points.length; i++) {
            points[i] = new Vecteur(o.points[i]);
        }
    }
    
    // Renvoie un objet de type Polygon utile pour l'affichage.
    public Polygon getPolygon() {
		int[] x = new int[points.length];
		int[] y = new int[points.length];
		for (int i = 0; i < x.length; i++) {
			x[i] = (int)points[i].rotation(-direction.getAngle()).x + (int)position.x;
			y[i] = (int)points[i].rotation(-direction.getAngle()).y + (int)position.y;
		}
		
		return new Polygon(x, y, x.length);
	}
	
	// Ajoute un point au polygône
	public void addPoint(Vecteur p) {
		Vecteur[] pts = new Vecteur[points.length+1];
		for (int i = 0; i < points.length; i++) {
			pts[i] = points[i];
		}
		pts[pts.length-1] = p;
		points = pts;
	}
	
	// Translate tous les points d'un objet par un certain vecteur.
	// Méthode destructive.
	public void translate(Vecteur t) {
		for (int i = 0; i < points.length; i++) {
			points[i] = points[i].add(t);
		}
	}
	
	// Dessine l'objet optique.
	// Le mode avancé affiche le centre, ainsi que le nom de l'objet.
	public void dessine(Graphics g, boolean advanced) {
		g.setColor(color);
		Polygon p = getPolygon();
        g.drawPolygon(p);
        g.setColor(new Color(color.getRed(), color.getGreen(), color.getBlue(), (int)(255*indice/2.1)));
        g.fillPolygon(p);
        
		if (advanced) {
			g.setColor(new Color(255-MainPanel.backgroundColor.getRed(), 255-MainPanel.backgroundColor.getGreen(), 255-MainPanel.backgroundColor.getBlue()));
			g.fillOval((int)position.x-4, (int)position.y-3, 7, 7);
			g.drawString(nom, (int)position.x-g.getFontMetrics().stringWidth(nom)/2, (int)position.y-10);
		}
	}
	
    // Teste l'intersection avec un rayon
	public Vecteur intersection(Rayon r) {
		for (int i = 0; i < points.length-1; i++) {
			Vecteur endOld = r.end;
			Vecteur a = points[i].rotation(-direction.getAngle()).add(position);
			Vecteur b = points[i+1].rotation(-direction.getAngle()).add(position);
			r.end = intersectionLigne(a, b, r.start, r.end);
		}
		
	    return intersectionLigne(points[points.length-1].rotation(-direction.getAngle()).add(position), 
				points[0].rotation(-direction.getAngle()).add(position), r.start, r.end);
	}
	
    // Teste l'intersection de deux lignes, et renvoiele point d'intersection.
	public Vecteur intersectionLigne(Vecteur a, Vecteur b, Vecteur x, Vecteur y) {
		Vecteur s1 = new Vecteur(b.x - a.x, b.y - a.y);
		Vecteur s2 = new Vecteur(y.x - x.x, y.y - x.y);
	
		double s = (-s1.y * (a.x - x.x) + s1.x * (a.y - x.y)) / (-s2.x * s1.y + s1.x * s2.y);
		double t = ( s2.x * (a.y - x.y) - s2.y * (a.x - x.x)) / (-s2.x * s1.y + s1.x * s2.y);
	
		if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
			return new Vecteur(a.x + (t * s1.x), a.y + (t * s1.y));
		}
		
		return y;
	}
	
	// Renvoie la normale associée à l'objet optique pour le point p.
	// Si p n'est pas sur le bord de l'objet, on renvoie la normale pour le segment le plus proche.
	public Vecteur getNormale(Vecteur p) {
		boolean b = false;
		double epsilon = 0.001;
		Vecteur pl1 = null;
		Vecteur pl2 = null;
		
		while (!b) {
			for (int i = 0; i < points.length-1; i++) {
				if (isPointOnLigne(points[i].rotation(direction.getAngle()).add(position), 
				points[i+1].rotation(-direction.getAngle()).add(position), p, epsilon)) {
					b = true;
					pl1 = points[i].rotation(-direction.getAngle()).add(position);
					pl2 = points[i+1].rotation(-direction.getAngle()).add(position);
					i = points.length;
				}
			}
			if (!b && isPointOnLigne(points[points.length-1].rotation(-direction.getAngle()).add(position), 
			points[0].rotation(-direction.getAngle()).add(position), p, epsilon)) {
				b = true;
				pl1 = points[points.length-1].rotation(-direction.getAngle()).add(position);
				pl2 = points[0].rotation(-direction.getAngle()).add(position);
			}
			epsilon *= 10;
		}
		
		return pl1.substract(pl2).rotationHoraire();		
	}
	
	// Teste si un point est présent sur une ligne, avec une certaine tolérance.
	public boolean isPointOnLigne(Vecteur lA, Vecteur lB, Vecteur p, double epsilon) {
		double a = (lB.y - lA.y) / (lB.x - lA.x);
		double b = lA.y - a * lA.x;
		if ( Math.abs(p.y - (a*p.x+b)) < epsilon) {
			return true;
		}

		return false;
	}
	
	// Supprime le point le plus proche du point p.
	public void deleteClosestPoint(Vecteur p) {
		int index = 0;
		double dmin = p.distance(points[0].rotation(-direction.getAngle()).add(position));
		for (int i = 0; i < points.length; i++) {
			if (p.distance(points[i].rotation(-direction.getAngle()).add(position)) < dmin) {
				dmin = p.distance(points[i].rotation(-direction.getAngle()).add(position));
				index = i;
			}
		}
		System.out.println("Suppression du point "+index);
		removePoint(index);
	}
	
	// Supprime le point dont l'index est donné en paramètre.
	public void removePoint(int index) {
		Vecteur[] pts = new Vecteur[points.length-1];
		
		System.out.println("Points avant");
		for (Vecteur p : points)
			System.out.println(p);
		System.out.println("Points apres");
		
		int j = 0;
		for (int i = 0; i < points.length; i++) {
			if (i != index) {
				pts[j] = new Vecteur(points[i]);
				System.out.println("Point "+j+" = "+pts[j]);
				j++;
			}
		}
		
		points = pts;
	}
	
	public void setIndice(double n) {
		indice = n;
	}
	
	public double getIndice() {
		return indice;
	}
}
