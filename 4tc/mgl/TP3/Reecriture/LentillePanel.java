import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;

/**
 * LentillePanel représente l'interface des propriétés,
 * ajoutée à l'interface toujours présente, lors de la 
 * sélection d'une LentilleConvergente ou une LentilleDivergente.
 * Il est possible d'y changer la hauteur ou la distance focale
 * de la lentille.
 */

public class LentillePanel extends ObjOptPanel {
	Objet objSelect = null;
    JSpinner distanceFocale = new JSpinner();
    JSpinner h = new JSpinner();
    
    public LentillePanel (LentilleDivergente lentille, Simulation simul) {
        super(lentille,simul, 1);
        objSelect = lentille;
        distanceFocale.setValue((int)((LentilleDivergente)objSelect).getDistFocale());
        h.setValue((int)((LentilleDivergente)objSelect).getHauteur());
        
        add(getBox());
        
        distanceFocale.addChangeListener(this);
        h.addChangeListener(this);
    }    

    public LentillePanel (LentilleConvergente lentille, Simulation simul) {
        super(lentille,simul, 1);
        objSelect = lentille;
        distanceFocale.setValue((int)((LentilleConvergente)objSelect).getDistFocale());
        h.setValue((int)((LentilleConvergente)objSelect).getHauteur());
        
        add(getBox());
        
        distanceFocale.addChangeListener(this);
        h.addChangeListener(this);
    }    

	// Met en place l'interface
	public Box getBox() {
		Box b = super.getBox();
		
		JLabel lf = new JLabel("Distance focale : ");
		JLabel lh = new JLabel("Hauteur : ");
		
		Box bf = Box.createHorizontalBox();
		Box bh = Box.createHorizontalBox();
		bf.add(lf); bf.add(distanceFocale); b.add(bf);
		b.add(Box.createVerticalStrut(10));
		bh.add(lh); bh.add(h); b.add(bh);
		b.add(Box.createVerticalStrut(10));
		
		return b;
	}
    
    public void stateChanged(ChangeEvent e) {
		updateProprietes();
	}
    
    // Met à jour les propriétés de la lentille associée
    public void updateProprietes() {
        if (objSelect instanceof LentilleConvergente) {
			LentilleConvergente lent = (LentilleConvergente)objSelect;
            lent.setHauteur((int) h.getValue());
            h.setValue(lent.getHauteur());
            lent.setDistFocale((int) distanceFocale.getValue());
            lent.init();
        }
        if (objSelect instanceof LentilleDivergente) {
			LentilleDivergente lent = (LentilleDivergente) objSelect;
            lent.setHauteur((int) h.getValue());
            h.setValue(lent.getHauteur());
            lent.setDistFocale((int) distanceFocale.getValue());
            lent.init();
        }        
        
        super.updateProprietes();
	}


}

