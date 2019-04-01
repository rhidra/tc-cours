import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;

/**
 * ObjPanel représente l'interface des propriétés,
 * ajoutée à l'interface toujours présente, lors de la 
 * sélection d'un objet quelconque.
 * Il est possible d'y changer la position, l'orientation
 * d'un objet, ainsi que de le supprimer.
 */

public abstract class ObjPanel extends JPanel implements ActionListener, ChangeListener {
	Simulation sim;
	JButton delete = new JButton("Supprimer");
	JSpinner x =  new JSpinner();
	JSpinner y = new JSpinner();
	JSlider direction = new JSlider(JSlider.HORIZONTAL, 0, 360, 0);
	JLabel ldirection = new JLabel("= 0d");
		
	public ObjPanel (Objet obj, Simulation simul) {
		setBackground(PropertiesPanel.BACKGROUND_COLOR);
		x.setValue((int)obj.position.x);
		y.setValue((int)obj.position.y);
		direction.setValue((int)Math.toDegrees(obj.direction.VecteurToAngle()));
		direction.setBackground(simul.proprietes.BACKGROUND_COLOR);
        sim = simul;
        
        x.addChangeListener(this);
        y.addChangeListener(this);
        direction.addChangeListener(this);
        
        delete.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				sim.remove(obj);
			}
		});
	}
	
	// Met en place l'interface
	public Box getBox() {
		JLabel lx = new JLabel("Position x : ");
		JLabel ly = new JLabel("Position y : ");
		JLabel ld = new JLabel("Angle : ");
		
        x.setPreferredSize(x.getMinimumSize());
        y.setPreferredSize(y.getMinimumSize());
		
		Box b = Box.createVerticalBox();
		b.add(delete);
		Box bx = Box.createHorizontalBox();
		Box by = Box.createHorizontalBox();
		Box bd = Box.createHorizontalBox();
		bx.add(lx); bx.add(x); b.add(bx);
		b.add(Box.createVerticalStrut(10));
		by.add(ly); by.add(y); b.add(by);
		b.add(Box.createVerticalStrut(10));
		bd.add(ld); bd.add(direction); bd.add(ldirection); b.add(bd);	
		b.add(Box.createVerticalStrut(10));
		
		return b;
	}
	
	public void actionPerformed (ActionEvent e) {
		updateProprietes();
    }
    
    public void stateChanged(ChangeEvent e) {
		updateProprietes();
	}
    
    // Met en place les propriétés de l'objet
    public void updateProprietes() {
        sim.objSelected.position.x = (int) x.getValue();
        sim.objSelected.position.y = (int) y.getValue();
        sim.objSelected.direction = Vecteur.angleToVecteur(Vecteur.degreToRadian(this.direction.getValue()));
        ldirection.setText("= "+this.direction.getValue()+"d");
        
        sim.refresh();
	}
	
}

