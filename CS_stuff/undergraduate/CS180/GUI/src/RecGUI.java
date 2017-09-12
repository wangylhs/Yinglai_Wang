import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class RecGUI implements ActionListener, MouseListener{
  JFrame f;
  JPanel p;
  JButton a, b, reset;
  JLabel l;
  JTextField t;
  int counter = 0;
  
  public RecGUI(){
    createFrame();
  }
  public void createFrame(){
    f = new JFrame("GUI");
    f.setSize(700,500);
    createPanel();
    f.add(p);
    f.setVisible(true);
    f.setBackground(Color.WHITE);
  }
  public void createPanel(){
    p = new JPanel(new BorderLayout());
    createButton();
    p.add(reset,BorderLayout.NORTH);
    p.add(a,BorderLayout.WEST);
    p.add(b,BorderLayout.EAST);
    createLabel();
    p.add(l,BorderLayout.SOUTH);
    createTextField();
    p.add(t,BorderLayout.CENTER);
  }
  public void createButton(){
    a = new JButton("Plus 5");
    a.addActionListener(this);
    a.addMouseListener(this);
    b = new JButton("Plus 7");
    b.addActionListener(this);
    b.addMouseListener(this);
    reset = new JButton("Reset");
    reset.addActionListener(this);
    reset.addMouseListener(this);
  }
  public void createLabel(){
    l = new JLabel("This is boring.");
  }
  public void createTextField(){
    t = new JTextField("Welcom! Your count is 0.");
  }
  public void actionPerformed(ActionEvent e){
    Object s = e.getSource();
    if(s.equals(a)){
      counter = counter+5;
      String c = Integer.toString(counter);
      String result = "Your count is "+c;
      t.setText(result);
    }
    if(s.equals(b)){
      counter = counter+7;
      String c = Integer.toString(counter);
      String result = "Your count is "+c;
      t.setText(result);
    }
    if(s.equals(reset)){
    	counter = 0;
    	String result = "Your count is 0.";
    	t.setText(result);
    }
  }
  public void mouseEntered(MouseEvent e){
	  Object m = e.getSource();
	  if(m.equals(a)){
		  a.setForeground(Color.BLUE);
	  }
	  if(m.equals(b)){
		  b.setForeground(Color.BLUE);
	  }
	  if(m.equals(reset)){
		  reset.setForeground(Color.BLUE);
	  }
  }
  public void mouseExited(MouseEvent e){
	  Object m = e.getSource();
	  if(m.equals(a)){
		  a.setForeground(Color.RED);
	  }
	  if(m.equals(b)){
		  b.setForeground(Color.RED);
	  }
	  if(m.equals(reset)){
		  reset.setForeground(Color.RED);
	  }
  }
  public void mousePressed(MouseEvent e){
	  
  }
  public void mouseReleased(MouseEvent e){
	  
  }
  public void mouseClicked(MouseEvent e){
	  
  }
  public static void main(String[] args){
    new RecGUI();
  }
}