import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class PCclient extends JFrame {
	private JButton start, stop, login, logout, load_question, chart_button,next;
	private JPanel button_panel, left_panel, right_panel, middle_panel, p;
	private JLabel username_label,password_label;
	private JTextField username_text,time_text,quizID_text,questionID_text;
	private JTextField field = new JTextField();
	private JPasswordField password_text;
	private JTextArea question;
	private int qid;

	private int myCurrentQuestion;
	private String username, password, file_path;
	private String[] quiz;

	final static String serverIP = "sslab14.cs.purdue.edu";


	private boolean isLogin;

	public PCclient() {
		super();
		isLogin = false;

		username = null;
		password = null;
		getContentPane().setLayout(new BorderLayout());
		setTitle("iClicker");
		setSize(1000, 800);
		pack();
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		start = new JButton("start");
		next = new JButton("Next");
		next.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				if(myCurrentQuestion != 6){

					question.setText(quiz[myCurrentQuestion]);
					myCurrentQuestion++;
				}


			}
		});
		start.addActionListener(new ActionListener(){

			public void actionPerformed(ActionEvent e) {

				// TODO Auto-generated method stub
				int time = Integer.parseInt(time_text.getText());
				int questionID = Integer.parseInt(questionID_text.getText());
				int quizID = Integer.parseInt(quizID_text.getText());
				qid = questionID;
				try {
					Socket socket = new Socket(serverIP,12345);
					DataOutputStream output = new DataOutputStream(socket.getOutputStream());
					output.writeChars("admin|start|"+questionID+"|"+quizID+"|"+time+"\n");
					socket.close();
					socket = new Socket(serverIP,12345);
					output = new DataOutputStream(socket.getOutputStream());
					output.writeChars("admins|a\n");
					output.writeChars(question.getText()+"\n\n");
					socket.close();
				} catch (UnknownHostException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}

			}

		});


		stop = new JButton("stop");
		stop.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0) {
				try {
					Socket socket = new Socket(serverIP,12345);
					DataOutputStream output = new DataOutputStream(socket.getOutputStream());
					output.writeChars("admin|stop\n");
					socket.close();
				} catch (UnknownHostException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		login = new JButton("login");
		chart_button = new JButton("result");
		chart_button.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent arg0) {
				//if( qid != -1 ){
					Thread t = new Thread(new Runnable(){
						public void run() {
							// TODO Auto-generated method stub
							System.out.println(qid);
							BC ba=new BC(qid);
							ba.update();
						}
					});
					t.start();
				//}
			}
		});
		logout = new JButton("logout");
		username_label = new JLabel("username");
		password_label = new JLabel("password");
		username_text = new JTextField();
		username_text.setPreferredSize(new Dimension(130, 26));

		password_text = new JPasswordField();
		password_text.setPreferredSize(new Dimension(130, 26));

		left_panel = new JPanel();
		left_panel.setLayout(new FlowLayout(FlowLayout.LEFT));
		left_panel.add(start);

		left_panel.add(stop);
		left_panel.add(chart_button);
		right_panel = new JPanel();
		right_panel.setLayout(new FlowLayout(FlowLayout.RIGHT));
		right_panel.add(login);
		right_panel.add(username_label);
		right_panel.add(username_text);
		right_panel.add(password_label);
		right_panel.add(password_text);
		right_panel.add(logout);
		login.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				try {
					username = username_text.getText();
					password = new String(password_text.getPassword());
					Socket socket = new Socket(serverIP, 12345);
					DataInputStream in = new DataInputStream(socket.getInputStream());
					DataOutputStream out = new DataOutputStream(socket.getOutputStream());
					out.writeChars("admin|login|"+username+"|"+password+"\n");
					int result = in.readInt();
					System.out.println(username+"|"+password);
					if( result == 0 ){
						isLogin = true;
						System.out.println("login success");

					}else{
						isLogin = false;
						System.out.println("login fail");
					}
					username_text.setText("");
					password_text.setText("");
					setMode();
					socket.close();
				} catch (UnknownHostException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
		logout.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				isLogin = false;
				setMode();
			}

		});
		class Chooser extends JFrame {

			JFileChooser chooser;
			String fileName;

			public Chooser() {
				chooser = new JFileChooser();
				int r = chooser.showOpenDialog(new JFrame());
				if (r == JFileChooser.APPROVE_OPTION) {
					fileName = chooser.getSelectedFile().getPath();
					File file = new File(fileName);
					file_path = file.getPath();
					// System.out.println(file_path);
					myCurrentQuestion = 0;
					BufferedReader buff = null;
					try {
						String temp = "";
						String text = "";

						buff = new BufferedReader(new FileReader(file_path));

						while ((temp = buff.readLine()) != null) {
							text += temp;
							text += "\n";
						}
						quiz = text.split("\n\n");
						question.setText(quiz[0]);
						myCurrentQuestion++;

					} catch (IOException e) {
						e.printStackTrace();
					} finally {
						try {
							if (buff != null)
								buff.close();
						} catch (IOException ex) {
							ex.printStackTrace();
						}
					}
				}
			}
		}
		load_question = new JButton("browse");
		load_question.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				Chooser frame = new Chooser();
				field.setText(frame.fileName);
				setMode();
			}

		});
		button_panel = new JPanel();
		button_panel.setLayout(new FlowLayout());
		button_panel.add(left_panel);
		button_panel.add(right_panel);
		button_panel.setVisible(true);
		button_panel.setBorder(BorderFactory.createLineBorder(Color.black));

		middle_panel = new JPanel(new BorderLayout());
		question = new JTextArea("--write your question here--");
		question.setPreferredSize(new Dimension(500, 400));
		question.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent evt) {
				int key = evt.getKeyCode();
				if (key == KeyEvent.VK_ENTER) {
					question.setText(question.getText());
				}
			}
		});
		time_text = new JTextField();
		time_text.setPreferredSize(new Dimension(100,26));
		time_text.setText("--seconds--");
		questionID_text = new JTextField();
		questionID_text.setPreferredSize(new Dimension(100,26));
		questionID_text.setText("--questionID--");
		quizID_text = new JTextField();
		quizID_text.setPreferredSize(new Dimension(100,26));
		quizID_text.setText("--quizID--");
		p = new JPanel();
		p.setLayout(new FlowLayout(FlowLayout.CENTER));
		p.add(next);
		p.add(load_question);
		p.add(time_text);
		p.add(questionID_text);
		p.add(quizID_text);
		middle_panel.add(question,BorderLayout.CENTER);
		middle_panel.add(p,BorderLayout.SOUTH);
		middle_panel.setPreferredSize(new Dimension(800, 600));
		add(button_panel, BorderLayout.NORTH);
		add(middle_panel, BorderLayout.SOUTH);
		setMode();
		pack();
	}

	private void setMode(){
		if( isLogin ){
			start.setEnabled(true);
			stop.setEnabled(true);
			load_question.setEnabled(true);
			time_text.setEditable(true);
			questionID_text.setEditable(true);
			quizID_text.setEditable(true);
			chart_button.setEnabled(true);
		}else{
			start.setEnabled(false);
			stop.setEnabled(false);
			load_question.setEnabled(false);
			time_text.setEditable(false);
			questionID_text.setEditable(false);
			quizID_text.setEditable(false);
			chart_button.setEnabled(false);
		}
	}

	public static void main(String[] args) {
		PCclient pc = new PCclient();

	}
}