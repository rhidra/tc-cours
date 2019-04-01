import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

/**
 * EditPropertiesPanel représente le panneau de propriétés utilisé dans l'éditeur.
 * C'est l'équivalent au PropertiesPanel utilisé dans la Simulation.
 * Intégre les fonctionnalités de l'éditeur :
 * - Mode ajout et mode de suppression de point
 * - Changement du nom de l'objet
 * - Changement de l'indice de l'objet
 * - Sauvegarde
 */

public class EditPropertiesPanel extends JPanel {
	public Editeur editeur;
	public JButton modeAjout;
	public JButton modeSuppr;
	public JLabel labelNom;
	public JTextField nom;
	public JSlider indice;
	public JButton save;
	
	public EditPropertiesPanel(Editeur editeur) {
		super();
		this.editeur = editeur;
		setBackground(PropertiesPanel.BACKGROUND_COLOR);
		
		// Bouton pour passer en mode Ajout
		modeAjout = new JButton("Mode Ajout");
		modeAjout.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				editeur.modeAjout = true;
			}
		});
		
		// Bouton pour passer en mode suppression de point
		modeSuppr = new JButton("Mode Suppr");
		modeSuppr.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				editeur.modeAjout = false;
			}
		});
		
		// Boîte de réglage du nom de l'objet
		labelNom = new JLabel("Nom : ");
		nom = new JTextField();
		
		// Slider de l'indice
		indice = new JSlider(JSlider.HORIZONTAL, 100, 200, 150);
		
		// Bouton de sauvegarde
		save = new JButton("Sauvegarder");
		save.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (nom.getText().isEmpty()) {
					labelNom.setForeground(Color.red);
				} else {
					labelNom.setForeground(Color.black);
					editeur.save(nom.getText(), indice.getValue()/100.);
				}
			}
		});
		
		// Placement de l'interface
		Box modes = Box.createHorizontalBox();
		modes.add(modeAjout);
		modes.add(modeSuppr);
		
		Box boxNom = Box.createHorizontalBox();
		boxNom.add(labelNom);
		boxNom.add(nom);
		
		Box b = Box.createVerticalBox();
		b.add(modes);
		b.add(Box.createVerticalStrut(10));
		b.add(boxNom);
		b.add(Box.createVerticalStrut(10));
		b.add(indice);
		b.add(Box.createVerticalStrut(10));
		b.add(save);
		b.add(Box.createVerticalStrut(20));
		
		JLabel lt = new JLabel("L'origine de l'objet est au centre de l'ecran.");
		lt.setPreferredSize(lt.getMaximumSize());
		b.add(lt);
		
		add(b);
	}
}
