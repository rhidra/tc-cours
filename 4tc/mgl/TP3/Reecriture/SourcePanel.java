import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;

/**
 * SourcePanel représente l'interface des propriétés,
 * ajoutée à l'interface toujours présente, lors de la 
 * sélection d'une Source.
 * Il est possible d'y changer la couleur des rayons d'une
 * Source, ainsi que le nombre de rayons à tracer.
 */

public class SourcePanel extends ObjPanel {
	public Source objSelect = null;
	
	// Bouton pour changer la couleur des rayons
    public JButton colorChooser = new JButton("Changer la couleur des rayons...");
    
    // Boîte pour changer le nombre de rayons à afficher
    public JSpinner nbRayons = new JSpinner();
    
    public SourcePanel (Source source, Simulation simul) {
        super(source,simul);
        objSelect = source;
        
        nbRayons.setValue(source.departRayon.length);
        add(getBox());
        
        // Un clic sur le bouton lance une boîte de dialogue pour choisir une couleur.
        colorChooser.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				Color newColor = JColorChooser.showDialog(sim, "Choisissez une couleur pour les rayons", Color.black);
				if (objSelect != null) {
					objSelect.couleur = newColor;
					updateProprietes();
				}
			}
		});
		
        nbRayons.addChangeListener(this);
    }
    
    // Met l'affichage des différents components en place
    public Box getBox() {
		Box b = super.getBox();
		
		JLabel ln = new JLabel("Nombre de rayons : ");
		Box bn = Box.createHorizontalBox();
		bn.add(ln); bn.add(nbRayons); b.add(bn);
		b.add(Box.createVerticalStrut(10));
		b.add(colorChooser);
		b.add(Box.createVerticalStrut(10));
		
		return b;
	}
    
    public void stateChanged(ChangeEvent e) {
		updateProprietes();
	}
	
	public void updateProprietes() {
		objSelect.setNbrRayons((int)nbRayons.getValue());
		super.updateProprietes();
	}
}

