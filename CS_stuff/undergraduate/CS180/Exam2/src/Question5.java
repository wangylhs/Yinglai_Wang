import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Question5 implements ActionListener, MouseListener{

	JFrame f;
	JPanel p;
	JPanel center;
	JButton[] b;
	JButton print;
	JTextField t;
	String text = "";
	static int n = 3;
	static String[] label = new String[n*n];
	int j=1;
	public Question5() {
		createGUI(n, label);
	}

	public void createGUI(int x, String[] l) {
		f = new JFrame("CS180");
		f.setSize(500, 500);
		f.setLayout(new BorderLayout());
//		createPanelp();
		createTextField();
		createPanelcenter();
		createButton();
		f.add(t,BorderLayout.NORTH);
		f.add(center,BorderLayout.CENTER);
		f.add(print,BorderLayout.SOUTH);
		f.setVisible(true);
		f.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

	}
/*	public void createPanelp(){
		p = new JPanel(new GridLayout(3,1));
		createTextField();
		createPanelcenter();
		createButton();
		p.add(t);
		p.add(center);
		p.add(print);
	}
	*/
	public void createPanelcenter(){
		center = new JPanel(new GridLayout(n,n));

		b = new JButton[n*n];
		for (int i = 0; i < n*n; i++) {
			label[i] = Integer.toString(j);
			b[i] = new JButton(label[i]);
			j++;
			b[i].addActionListener(this);
			b[i].addMouseListener(this);
			center.add(b[i]);
		}
	}
	public void createButton(){
		print = new JButton("Print");
		print.addActionListener(this);
	}
	public void createTextField(){
		t = new JTextField("Numerals typed are displayed here.");
	}

	public void actionPerformed(ActionEvent e) {
		Object s = e.getSource();
		for (int i = 0; i < n*n; i++) {
			if (s.equals(b[i])) {
				text = text + label[i];
				t.setText(text);
			}
		}
		if(s.equals(print)){
			System.out.println(t.getText());
			t.setText("Numerals typed are displayed here.");
		}
	}

	public void mouseEntered(MouseEvent e) {
		Object s = e.getSource();
		for (int i = 0; i < n*n; i++) {
			if (s.equals(b[i])) {
				System.out.println("Mouse enters button " + label[i]);
			}
		}
	}

	public void mouseExited(MouseEvent e) {
		Object s = e.getSource();
		for (int i = 0; i < n*n; i++) {
			if (s.equals(b[i])) {
				System.out.println("Mouse exited button " + label[i]);
			}
		}
	}

	public void mousePressed(MouseEvent e) {

	}

	public void mouseReleased(MouseEvent e) {

	}

	public void mouseClicked(MouseEvent e) {

	}

	public static void main(String[] args) {

		new Question5();
	}
}
