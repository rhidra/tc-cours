import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

/**
 * Menu simple, indépendant du programme, permettant d'accéder à l'Editeur ou à une Simulation.
 * La fenêtre ne se ferme pas, permettant à l'utilisateur d'éviter
 * de relancer le programme s'il souhaite changer de mode.
 */

public class Menu extends JFrame implements ActionListener {
	private final int WIDTH = 600;
	private final int HEIGHT = 250;
	
	private JButton simulation = null;
	private JButton editeur = null;
	
	public static void main(String[] args) {
		Menu menu = new Menu();
	}
	
	public Menu() {
		super("Simulateur optique");
		setLayout(null);
		setSize(WIDTH,HEIGHT);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);
		
		JLabel label = new JLabel("<html><p style=\"text-align:center; font-size:120%\">Ceci est un logiciel de simulation de ph\u00e9nom\u00e8nes optique.<br/> Choississez votre mode :</p></html>");
		label.setSize(label.getPreferredSize());
		label.setLocation(WIDTH/2 - label.getWidth()/2, 0);
		
		int buttonWidth = 50;
		
		simulation = new JButton("Simulation");
		simulation.setBounds(0, label.getHeight()+20, getWidth(), buttonWidth);
		
		editeur = new JButton("\u00c9diteur d'objet optique");
		editeur.setBounds(0, label.getHeight()+20+simulation.getHeight()+15, getWidth(), buttonWidth);
		
		add(label);
		add(simulation);
		add(editeur);
		
		simulation.addActionListener(this);
		editeur.addActionListener(this);
		
		setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == simulation) {
			new Simulation();
		} else if (e.getSource() == editeur) {
			new Editeur();
		}
	}
}
