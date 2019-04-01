import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.util.ArrayList;

/**
 * Fenetre représente la classe JFrame abstraite générique d'une fenêtre.
 * Autrement dit, elle reprend tous les points commun entre une Simulation
 * et un Editeur.
 */

public abstract class Fenetre extends JFrame {
	// Largeur de la fenêtre
	public static int WIDTH;
	// Hauteur de la fenêtre
	public static int HEIGHT;
	
	// Liste des objets présents dans l'environnement
	public ArrayList<Objet> objets;
	
	public MainPanel mainPanel;
	
	// Permet d'activer l'affichage avancé des objets
    public boolean advancedDisplay = false;
	
	public Fenetre() {
		super();
		setLayout(null);
		setLocationRelativeTo(null);
		setResizable(true);
		setExtendedState(MAXIMIZED_BOTH);
		
        objets = new ArrayList<Objet>();
		
		mainPanel = new MainPanel(this);
		
	}
	
	// Ajout d'un objet l'environnement
	public void add(Objet o) {
		objets.add(o);
	}
	
	// Suppression d'un objet de l'environnement
	public void remove(Objet o) {
		objets.remove(o);
	}
	
	// Remise à zéro de l'environnement
	public void reset() {
		objets.clear();
	}
	
	public abstract void clic(MouseEvent e);
}
