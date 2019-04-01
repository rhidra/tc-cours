import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;

/**
 * Editeur est la classe principale du module éditeur du programme.
 * Permet de créer un objet en ajoutant des points à un ObjetOptique
 * en fonction de la position du clic.
 * Gère toute la boucle du module, la plupart des évènements,
 * ainsi que la sauvegarde des objets sur le disque dur.
 */

public class Editeur extends Fenetre {
	// Objet édité par l'utilisateur
	// C'est aussi le seul objet présent dans l'environement.
	public ObjetOptique obj;
	
	// Panneau des propriétés associé avec l'éditeur
	public EditPropertiesPanel propertiesPanel;
	
	// Permet de différencier mode Ajout et mode Suppression de point.
	public boolean modeAjout = true;
	
	public Editeur() {
		super();
		setTitle("Editeur d'objet optique");
		
		obj = new ObjetOptique();
		add(obj);
		
		propertiesPanel = new EditPropertiesPanel(this);
		
		setLayout(new BorderLayout());
		getContentPane().add(mainPanel, BorderLayout.CENTER);
		getContentPane().add(propertiesPanel, BorderLayout.EAST);
		
		setVisible(true);
	}
	
	// Action lors d'un clic sur la fenêtre de l'environnement
	public void clic(MouseEvent e) {
		if (modeAjout) {
			obj.addPoint(new Vecteur(e.getX(), e.getY()));
		} else {
			obj.deleteClosestPoint(new Vecteur(e.getX(), e.getY()));
		}
		
		repaint();
	}
	
	// Sauvegarde de l'objet édité
	// Tous les objets sont enregistrés dans le dossier obj et utilisent l'extension .opt.
	public void save(String nom, double indice) {
		obj.indice = indice;
		obj.nom = nom;
		// Déplacement de l'origine de l'objet au centre de la fenêtre
		obj.translate(new Vecteur(-getWidth()/2, -getHeight()/2));
		
		// Sérialization du l'objet
		ObjectOutputStream oos = null;
		try {
			oos = new ObjectOutputStream(new FileOutputStream("obj/"+nom+".opt"));
			oos.writeObject(obj);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (oos != null) {
					oos.flush();
					oos.close();
				}
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
		
		// Replacement de l'origine
		obj.translate(new Vecteur(getWidth()/2, getHeight()/2));
	}
	
	public static void main(String[] args) {
		new Editeur();
	}
}
