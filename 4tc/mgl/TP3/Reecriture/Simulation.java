import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;
import java.awt.event.*;

/**
 * Simulation est la classe principale d'une simulation.
 * Permet d'ajouter des objets à la simulation courante, et
 * de les manipuler.
 * Actualise l'affichage afin de tracer les rayons.
 */

public class Simulation extends Fenetre implements ActionListener{
	// Indice de l'environnement
	public static double indiceEnvironnement = 1.0;
	
	// Objet actuellement sélectionné par l'utilisateur
	public Objet objSelected;
	
    public PropertiesPanel proprietes;
    
    // Timer de rafraichissement de l'écran
    public Timer timer;
    public static final int REFRESH_DELAY = 100;
    public boolean hasToRefresh = true;
    
	public Simulation() {
		super();
		setTitle("Simulation de systeme optique");
		
		proprietes = new PropertiesPanel(this);
		
		setLayout(new BorderLayout());
		getContentPane().add(mainPanel, BorderLayout.CENTER);
		getContentPane().add(proprietes, BorderLayout.EAST);
		
		timer = new Timer(REFRESH_DELAY, this);
		timer.start();
		
		setVisible(true);
		
		WIDTH = getWidth();
		HEIGHT = getHeight();
	}
	
	public static void main(String[] args) {
		new Simulation();
	}
	
	// Gestion du clic : Sélection d'un objet à proximité
	public void clic (MouseEvent e){
        if(objets.isEmpty()){
            objSelected = null;
        } else {
            double dmin = objets.get(0).position.substract(new Vecteur(e.getX(), e.getY())).norme();
            for( Objet n : objets){
                double d =  n.position.substract(new Vecteur(e.getX(), e.getY())).norme();
                if (d<dmin){
                    dmin = d;
                    objSelected = n;
                }
            }
        }
        refresh();
    }
    
    // Réactualisation si nécessaire de tout l'affichage
    public void actionPerformed(ActionEvent e) {
		if (hasToRefresh) {
			hasToRefresh = false;
			proprietes.refreshObjPanel(objSelected);
			refreshSources();
			repaint();
		}
	}
	
	// Traçage des rayons optiques
	public void refreshSources() {
		for (Objet o : objets) {
			if (o instanceof Source) {
				((Source)o).refresh(objets.toArray(new Objet[0]));
			}
		}
	}
    
    // Force le rafraichissement de l'écran
    public void refresh(){
		hasToRefresh = true;
    }
    
    // Ajout d'un objet
    public void add(Objet o) {
		super.add(o);
		objSelected = o;
	}
	
	// Suppression d'un objet
	public void remove(Objet o) {
		super.remove(o);
		if (objSelected == o) {
			objSelected = null;
		}
		refresh();
		proprietes.refreshObjectSelector();
	}
	
	// Remise à zéro
	public void reset() {
		super.reset();
		objSelected = null;
		refresh();
	}
}
