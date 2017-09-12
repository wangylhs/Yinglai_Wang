import java.awt.GridLayout;
import java.awt.event.*;
import javax.swing.*;

public class ConcExercise implements ActionListener {
	JFrame f;
	JTextField t;
	JButton start;
	static boolean flag = false;
	
	public ConcExercise(){
		f = new JFrame("Rec13");
		t = new JTextField();
		start = new JButton("START");
		start.addActionListener(this);
		f.setSize(500,500);
		f.setLayout(new GridLayout(1,2));
		f.add(t);
		f.add(start);
		f.setVisible(true);
	}
	
	public void update(int x){
		t.setText(Integer.toString(x));
	}
	
	public void actionPerformed(ActionEvent e){
		Object s = e.getSource();
		if(s.equals(start)){
			flag = true;
		}
	}
	
	public static void main(String[] args){
		ConcExercise ce = new ConcExercise();
		int n = 100;
		MyThread mt = new MyThread(ce, n);
		
		while(!flag){
			//try{
		//		Thread.sleep(10);
			//}catch(Exception e){}
		}
		mt.start();
		try{
			mt.join();
		}catch(Exception e){}
	}
}
