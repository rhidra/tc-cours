import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/** Small class that provides a way to compute
the proportion of clics on a button */
class RsercerCounter {
    private int me = 0, all = 0;
    public void itsMe() {
        me++;
        all++;
        System.out.println("it's me="+me+" and all="+all);
    }
    public void notMe() {
        all++;
        System.out.println("all="+all);
    }
    public double getRatio() {
        return me / (double) all;
    }
}

/** window listener that displays the computed ratio on closing */
class OnCloseListener extends WindowAdapter implements WindowListener {
    public RsercerCounter rsercer;

    public OnCloseListener(RsercerCounter rsercer) {
	    this.rsercer = rsercer;
    }

    @Override
    public void windowClosing(WindowEvent e) {
        System.out.println(rsercer.getRatio());
    }
}

/** Main class that counts the proportion of clics on the "rse" button */
public class Counter implements Runnable {

    @Override
    public void run() {

        JFrame f = new JFrame("Counter");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    	RsercerCounter rsercer = new RsercerCounter();
        f.addWindowListener(new OnCloseListener(rsercer));

    	JPanel panel = new JPanel(new GridLayout(0,2));
    	Map<JButton,String> names = new HashMap<JButton,String>();
    	names.put(new JButton("ldu"), "ldubois");
    	names.put(new JButton("rse"), "rsercer");
    	names.put(new JButton("jpe"), "jpetit");
    	names.put(new JButton("bre"), "brenard");
    	for (JButton b: names.keySet()) {
    	    panel.add(b);
    	}

        f.getContentPane().add(panel);
        f.pack();
        f.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater( new Counter() );
    }
}
