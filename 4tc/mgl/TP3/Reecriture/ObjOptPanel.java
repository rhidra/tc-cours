import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;

/**
 * ObjOptPanel représente l'interface des propriétés,
 * ajoutée à l'interface toujours présente, lors de la 
 * sélection d'un ObjetOptique.
 * Il est possible d'y changer l'indice de l'objet.
 */

public class ObjOptPanel extends ObjPanel {
	// L'indice x100 par rapport à la valeur réelle
	JSlider indice =  new JSlider(105, 200, 150);
	
	// Affichage de la valeur sélectionnée
	JLabel valIndice = new JLabel("= 1.5");
		
	public ObjOptPanel (ObjetOptique obj, Simulation simul) {
		super(obj, simul);
		
		indice.setValue((int)(obj.indice*100));
		indice.addChangeListener(this);
		
		add(getBox());
	}
	
	public ObjOptPanel(ObjetOptique obj, Simulation sim, int i) {
		super(obj, sim);
		
		indice.setValue((int)(obj.indice*100));
		indice.setBackground(sim.proprietes.BACKGROUND_COLOR);
		indice.addChangeListener(this);
	}
	
	// Met en place l'interface
	public Box getBox() {
		Box b = super.getBox();
		
		JLabel li = new JLabel("Indice : ");
		Box bi = Box.createHorizontalBox();
		bi.add(li); bi.add(indice); bi.add(valIndice); b.add(bi);
		b.add(Box.createVerticalStrut(10));
		
		return b;
	}
	
	public void actionPerformed (ActionEvent e) {
		updateProprietes();
    }
    
    public void stateChanged(ChangeEvent e) {
		updateProprietes();
	}
    
    // Met à jour les propriétés de l'objet optique
    public void updateProprietes() {
		((ObjetOptique)sim.objSelected).setIndice((int)(indice.getValue())/100.);
		valIndice.setText("= "+((int)indice.getValue())/100.);
				
		super.updateProprietes();
	}
	
}

