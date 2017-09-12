


import javax.swing.*;
import java.awt.event.*;


public class Gui136 {
	public static void main(String[] args){
		JFrame soundCheck = new JFrame("Sound Check");
		JPanel soundPanel = new JPanel();
		JButton chirpButton = new JButton("Birdy");
		JButton barkButton = new JButton("Doggy");
		JButton exitButton = new JButton("Exit");
		final JTextField message = new JTextField("Listen to Nature!");
		soundPanel.add(barkButton);
		soundPanel.add(chirpButton);
		soundPanel.add(message);
		soundPanel.add(exitButton);
		soundCheck.add(soundPanel);
		soundCheck.setSize(200,125);
		soundCheck.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		soundCheck.setVisible(true);
		
		chirpButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				message.setText("Chirp requested.");
			}
		});
		barkButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				message.setText("Bark requested.");
			}
		});
		exitButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println("Exit");
				System.exit(0);
			}
		});
		
	}

}
