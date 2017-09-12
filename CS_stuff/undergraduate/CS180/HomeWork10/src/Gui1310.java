
import javax.swing.*;
import java.awt.*;


public class Gui1310 {
	public static void main(String[] args){
		JFrame demo = new JFrame("Flow Layout Demo");
		JPanel buttonPanel = new JPanel(new FlowLayout());
		final int maxButtons = 50;
		JButton buttons[] = new JButton[maxButtons];
		for(int i=0; i<maxButtons; i++){
			buttons[i] = new JButton(Integer.toString(i));
			buttonPanel.add(buttons[i]);
		}
		demo.add(buttonPanel);
//		demo.setSize(300,100);
		demo.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		demo.pack();
		demo.setResizable(false);
		demo.setVisible(true);
	}
}
