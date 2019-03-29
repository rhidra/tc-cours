import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

/**
 * MainPanel correspond à l'interface utilisée
 * pour afficher l'environnement à l'écran.
 * Fonctionne de la même manière pour une Simulation et pour un Editeur.
 * Affiche aussi une grille lorsque l'utilisateur le souhaite.
 * Rejette les évènements de clics à l'entité appropriée.
 */

public class MainPanel extends JPanel implements MouseListener, MouseMotionListener {
    // Fenetre associée au MainPanel
    protected Fenetre f;
    
    // Affichage de la grille étendue
    public boolean completeGrid = false;
    public static final int NB_LINE_GRID = 20;
    
    // Couleur du fond
    public static Color backgroundColor = Color.white;
    
    // Déplacement d'un objet grâce au clic
    public boolean dragging = false;
    public Vecteur origin = new Vecteur();
    
    // L'attribut sera soit la fenêtre en mode édition, soit la fenêtre simulation
	public MainPanel(Fenetre fen) {
        super();
        f=fen;
        addMouseListener(this);
        addMouseMotionListener(this);
	}
    
    // Dessin de tous les objets de l'environnement, puis de la grille.
    public void paintComponent(Graphics g){
		g.setColor(backgroundColor);
		g.fillRect(0, 0, f.getWidth(), f.getHeight());
        //On parcourt tableau d'objet pour les dessiner
        for (int i=0 ; i<f.objets.size() ; i++){                
            f.objets.get(i).dessine(g, f.advancedDisplay);
        }
        
        drawGrid(g);
    }
    
    // Dessin de la grille
    public void drawGrid(Graphics g) {
		// Couleur inversée par rapport à la couleur d'arrière plan
		g.setColor(new Color(255 - backgroundColor.getRed(), 255 - backgroundColor.getGreen(), 255 - backgroundColor.getBlue()));
		
		if (completeGrid) {
			// Grille étendu
			for (int i = 0; i < NB_LINE_GRID; i++) {
				if (i == NB_LINE_GRID/2) {
					g.setColor(new Color(255 - backgroundColor.getRed(), 255 - backgroundColor.getGreen(), 255 - backgroundColor.getBlue()));
				} else if (i % 2 == 1) {
					g.setColor(new Color(255 - backgroundColor.getRed(), 255 - backgroundColor.getGreen(), 255 - backgroundColor.getBlue(), 128));
				} else {
					g.setColor(new Color(255 - backgroundColor.getRed(), 255 - backgroundColor.getGreen(), 255 - backgroundColor.getBlue(), 64));
				}
				g.drawLine(0, f.getHeight()*i/NB_LINE_GRID, f.getWidth(), f.getHeight()*i/NB_LINE_GRID);
				g.drawLine(f.getWidth()*i/NB_LINE_GRID, 0, f.getWidth()*i/NB_LINE_GRID, f.getHeight());
			}
		} else {
			// Grille réduite
			g.drawLine(0, f.getHeight()/2, f.getWidth(), f.getHeight()/2);
			g.drawLine(f.getWidth()/2, 0, f.getWidth()/2, f.getHeight());
		}
	}
	
	// Lors d'une Simulation, gère le Clic&Drag de la souris.
	// Déplace les objets en temps réel par le mouvement de la souris.
	public void mouseDragged(MouseEvent e) {
		if (f instanceof Simulation) {
			Simulation sim = (Simulation)f;
			if (sim.objSelected != null) {
				Vecteur mouse = new Vecteur(e.getX(), e.getY());
				sim.objSelected.position = sim.objSelected.position.add(mouse.substract(origin));
				sim.proprietes.hasToRefresh = true;
				sim.refresh();
				origin = mouse;
			}
		}
	}
        
    // Début du dragging
	public void mousePressed(MouseEvent e) {
		origin = new Vecteur(e.getX(), e.getY());
		dragging = true;
	}
	// Fin du dragging
	public void mouseReleased(MouseEvent e) {
		dragging = false;
	}
	// Clic simple
	public void mouseClicked(MouseEvent e) {
        f.clic(e);
    }
    public void mouseMoved(MouseEvent e) {}
	public void mouseEntered(MouseEvent e) {}
	public void mouseExited(MouseEvent e) {}
    
}
