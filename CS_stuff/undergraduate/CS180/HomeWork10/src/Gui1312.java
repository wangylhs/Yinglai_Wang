import javax.swing.*;


public class Gui1312 {
	JFrame f = new JFrame("HomeWork10");
	JMenuBar mb = new JMenuBar();
	JMenu m = new JMenu("OneMenu");
	JMenuItem mi = new JMenuItem("MenuItem");
	
	public Gui1312(){
		createFrame();
	}
	public void createFrame(){
		f.setJMenuBar(mb);
		mb.add(m);
		m.add(mi);
		f.setSize(200,200);
		f.setResizable(false);
		f.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		f.setVisible(true);
		
	}
	public static void main(String[] args){
		new Gui1312();
	}
}
