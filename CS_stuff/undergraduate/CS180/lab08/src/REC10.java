import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Scanner;

public class REC10 implements ActionListener{
	JFrame f;
	JPanel p;
	JButton enter;
	JTextField t;
	JLabel l;
	public static int row, col;
	public static boolean input = false;

  public void createArray(int r, int c){
    String[][] hello = new String[r][c];
    for(int i=0; i<r; i++){
      for (int n=0;n<c;n++){
        hello[i][n]="Hello"+" "+r+" "+c;
    }
    }
  

	    for(int i=0;i<row;i++){
	    	for(int n=0;n<col;n++){
	    		System.out.print(hello[i][n]+" ");
	    	}
	    	System.out.print("\n");
	    }
  }
  
  public void createGUI(){
	  createFrame();
  }
  public void createFrame(){
	  f = new JFrame("Recitation 10");
	  f.setSize(700,500);
	  createPanel();
	  f.add(p);
	  f.setVisible(true);
  }
  public void createPanel(){
	  p = new JPanel(new BorderLayout());
	  createButton();
	  p.add(enter,BorderLayout.SOUTH);
	  createLabel();
	  p.add(l,BorderLayout.NORTH);
	  createTextField();
	  p.add(t,BorderLayout.CENTER);
  }
  public void createButton(){
	  enter = new JButton("ENTER");
	  enter.addActionListener(this);
  }
  public void createLabel(){
	  l = new JLabel("This is an Array Exercise.");
	  l.setFont(new Font("Comic Sans MS", Font.BOLD, 40));
  }
  public void createTextField(){
	  t = new JTextField();
  }
  public void actionPerformed(ActionEvent e){
	  Object s = e.getSource();
	  if(s.equals(enter)){
		  String num = t.getText();
		  Scanner in = new Scanner(num);
		  row = in.nextInt();
		  col = in.nextInt();
		  createArray(row,col);
		  input = true;
	  }
  }
  
  
  public static void main(String[] args){
    REC10 a = new REC10();
    a.createGUI();
    
  }
}