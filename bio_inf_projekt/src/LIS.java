import java.awt.BorderLayout;
import javax.swing.JFrame;
import javax.swing.JTextArea;
import java.awt.Color;


public class LIS {    // Your class name

 public static void main(String[] args) {
   
   JFrame f = new JFrame("A JFrame");
   f.setSize(250, 250);
   f.setLocation(300,200);
   JTextArea textArea = new JTextArea(10, 40);
   textArea.setBackground(new Color(255, 255, 204));
   f.getContentPane().add(BorderLayout.CENTER, textArea);
   f.setVisible(true);
   
 }
}
