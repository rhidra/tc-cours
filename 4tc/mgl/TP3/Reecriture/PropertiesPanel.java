import java.awt.* ;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.util.ArrayList;

/**
 * PropertiesPanel représente le panneau des propriétés dans une Simulation.
 * Il est possible d'y régler tous les paramètres élémentaires d'une simulation.
 * Cette classe intégre un panel de type ObjPanel, qui est modifier en fonction de l'objet séléctionné.
 */

public class PropertiesPanel extends  JPanel implements ActionListener {
	public static final Color BACKGROUND_COLOR = new Color(204,204,204);
	
    public JButton add;
    public JButton reset;
    public JComboBox objectToAdd;
    public JComboBox objectSelector;
    public JCheckBox advancedDisplay;
    public JCheckBox grid;
    public JButton backgroundColorChooser;
    public ObjPanel objPanel;
    public LentillePanel lentillePanel;
    public EcranPanel ecranPanel;
    public SourcePanel sourcePanel;
    public Simulation sim;
    public Objet objSelected = null;
    public boolean modifyingObjSelector = false;
    public boolean hasToRefresh = false;
    
    public PropertiesPanel (Simulation simulation) {
        super();
        sim=simulation;
        this.setBounds(0,0,400,400);
        this.setBackground(BACKGROUND_COLOR);
        
        // Bouton d'ajout d'un objet
        add = new JButton("Ajouter");
        
        // Bouton de reset
        reset = new JButton("Reset");
        
        // Checkbox pour activer l'affichage avancé
        advancedDisplay = new JCheckBox("Affichage avance");
        advancedDisplay.setSelected(false);
        advancedDisplay.setBackground(BACKGROUND_COLOR);
        advancedDisplay.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				sim.advancedDisplay = advancedDisplay.isSelected();
				sim.refresh();
			}
		});
		
		// Checkbox pour activer l'affichage de la grille
		grid = new JCheckBox("Afficher grille");
        grid.setSelected(false);
        grid.setBackground(BACKGROUND_COLOR);
        grid.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				sim.mainPanel.completeGrid = grid.isSelected();
				sim.refresh();
			}
		});
        
        // Bouton pour changer le background
        backgroundColorChooser = new JButton("Changer la couleur du fond ...");
        backgroundColorChooser.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				MainPanel.backgroundColor = JColorChooser.showDialog(sim, "Choisissez une couleur pour le fond", Color.white);
				sim.refresh();
			}
		});
        
        // Menu déroulant
        objectToAdd = new JComboBox(getObjectToAdd());
        objectSelector = new JComboBox();
        
        objPanel = null;
        
        refreshDisplay();
        
		add.addActionListener(this);
		reset.addActionListener(this);
		objectSelector.addActionListener(this);
    }
    
    // Gestion des évènements
    public void actionPerformed(ActionEvent e) {
        if (e.getSource()== add){
			// Ajout de l'objet séléctionné dans le menu déroulant.
			try {
				if (!objectToAdd.getSelectedItem().getClass().equals(new ObjetOptique().getClass())) {
					Objet o = (Objet)objectToAdd.getSelectedItem().getClass().newInstance();
					o.position.x = sim.getWidth()/2;
					o.position.y = sim.getHeight()/2-1;
					sim.add(o);
					refreshObjectSelector();
					sim.refresh();
				} else {
					ObjetOptique o = new ObjetOptique((ObjetOptique)objectToAdd.getSelectedItem());
					o.position.x = sim.getWidth()/2;
					o.position.y = sim.getHeight()/2;
					sim.add(o);
					refreshObjectSelector();
					sim.refresh();
				}
			} catch (Exception err) {
				err.printStackTrace();
			}
        } else if (e.getSource() == reset){
            // Remise à zéro
            sim.reset();
            refreshObjectSelector();
            sim.refresh();
        } else if (e.getSource() == objectSelector && !modifyingObjSelector) {
			// Sélecteur d'objet
			sim.objSelected = (Objet)objectSelector.getSelectedItem();
			refreshObjPanel(sim.objSelected);
		}
    }
    
    // Mise à jour du sélecteur d'objet
    public void refreshObjectSelector() {
		modifyingObjSelector = true;
		objectSelector.removeAllItems();
		for (Objet o : sim.objets) {
			objectSelector.addItem(o);
		}
		objectSelector.setSelectedItem(sim.objSelected);
		modifyingObjSelector = false;
	}
    
    // Appelé depuis le refresh du simulation pour changer le type de panel qu'on va devoir afficher
    public void refreshObjPanel (Objet objSelect){
		if (objSelect != objSelected || hasToRefresh) {
			hasToRefresh = false;
			objSelected = objSelect;
			if (objSelect instanceof Source) {
				objPanel = new SourcePanel((Source)objSelect, sim);
			} else if (objSelect instanceof LentilleConvergente) {
				objPanel = new LentillePanel((LentilleConvergente)objSelect, sim);
			} else if (objSelect instanceof LentilleDivergente) {
				objPanel = new LentillePanel((LentilleDivergente)objSelect, sim);
			} else if (objSelect instanceof Ecran) {
				objPanel = new EcranPanel(objSelect, sim);
			} else if (objSelect == null) {
				objPanel = null;
			} else if (objSelect instanceof ObjetOptique) {
				objPanel = new ObjOptPanel((ObjetOptique)objSelect, sim);
			} else if (objSelect instanceof Miroir) {
				objPanel = new EcranPanel(objSelect, sim);
			} else if (objSelect == null) {
				objPanel = null;
			}
			
			refreshDisplay();
		}
    }    
    
    // Met en place l'interface
    public void refreshDisplay() {
        Box global = Box.createVerticalBox();
        Box ajout = Box.createHorizontalBox();
        ajout.add(objectToAdd);
        ajout.add(add);
        JLabel la = new JLabel("Selectionnez un objet a ajouter :");
        global.add(la);
        global.add(ajout);
		global.add(Box.createVerticalStrut(10));
        JLabel ls = new JLabel("Objet selectionne :");
        global.add(ls);
        global.add(objectSelector);
		global.add(Box.createVerticalStrut(10));
        global.add(reset);
		global.add(Box.createVerticalStrut(20));
        removeAll();
        if (objPanel != null) {
			setLayout(new BorderLayout());
			add(global, BorderLayout.NORTH);
			add(objPanel, BorderLayout.CENTER);
		} else {
			setLayout(new BorderLayout());
			add(global, BorderLayout.NORTH);
		}
		
		Box bas = Box.createVerticalBox();
		bas.add(grid);
		bas.add(advancedDisplay);
		bas.add(backgroundColorChooser);
		add(bas, BorderLayout.SOUTH);
		sim.repaint();
		sim.revalidate();
	}
    
    // Récupère tous les objets personnalisés enregistrés avec l'éditeur sur le disque.
    // Tous les objets sont présents dans le dossier obj avec l'extension .opt.
    public Objet [] getObjectToAdd () {
		System.out.println("Lecture du disque ...");
        File f = new File("obj/");
        String[] files = f.list();
        if (files == null)
			files = new String[0];
		
		// Ajout des objets élémentaires
        ArrayList<Objet> obj = new ArrayList<Objet>();
        obj.add(new Ecran());
        obj.add(new Miroir());
        obj.add(new LentilleConvergente());
        obj.add(new LentilleDivergente());
        obj.add(new Source());
        
        try {
            for (int i = 0; i < files.length; i++) {
				if (files[i].contains(".opt")) {
					System.out.println("Lecture du fichier : "+files[i]);
					ObjectInputStream ois = new ObjectInputStream(new FileInputStream("obj/"+files[i]));
					ObjetOptique o = (ObjetOptique)ois.readObject();
					o.nom = files[i].substring(0, files[i].length()-4);
					System.out.println("Chargement d'un objet : "+o+" indice="+o.indice+" avec "+o.points.length+" points.");
					obj.add(o);
				}
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            System.exit(0);
        }
        
        return obj.toArray(new Objet[0]);
	}
    
}

