import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;

/**
 * EcranPanel représente l'interface des propriétés,
 * ajoutée à l'interface toujours présente, lors de la 
 * sélection d'un objet de type Ecran ou Miroir.
 * Il est possible d'y changer la longueur de l'Ecran ou
 * du Miroir.
 */

public class EcranPanel extends ObjPanel {
	// Boîte pour modifier la longueur du Miroir ou de l'Ecran.
    JSpinner l = new JSpinner();
    
    public EcranPanel (Objet ecran, Simulation simul) {
        super(ecran,simul);
        Objet objSelect = simul.objSelected;
        if (objSelect instanceof Ecran)
            l.setValue((int)((Ecran)objSelect).longueur);
        else if (objSelect instanceof Miroir)
            l.setValue((int)((Miroir)objSelect).longueur);
            
		add(getBox());
		
		l.addChangeListener(this);
    }
    
    // Met l'affichage des différents components en place
    public Box getBox() {
		Box b = super.getBox();
		JLabel ll = new JLabel("Longueur : ");
		Box bl = Box.createHorizontalBox();
		bl.add(ll); bl.add(l); b.add(bl);
		
		return b;
	}
	
	public void stateChanged(ChangeEvent e) {
		updateProprietes();
	}
 
    public void actionPerformed (ActionEvent e) {
		updateProprietes();
    }
    
    public void updateProprietes() {
        if (sim.objSelected instanceof Ecran)
            ((Ecran)sim.objSelected).longueur = (int)l.getValue();
        else if (sim.objSelected instanceof Miroir)
            ((Miroir)sim.objSelected).longueur = (int)l.getValue();
            
        super.updateProprietes();
	}
}

