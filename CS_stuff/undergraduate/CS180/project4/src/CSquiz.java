 /**
  * 
  *     name     *   cs login  *  section number 
  *              *             *
  * Yinglai Wang *   wang1105  *     011
  * He Chen      *   chen730   *     004
  */
 
 import javax.swing.*;
 import java.awt.*;
 import java.awt.event.*;
 import java.io.*;
 import java.util.*;
 
 public class CSquiz implements ActionListener {
  JFrame f, flogin;
  JPanel p, buttonPanel, answerPanel, optionPanel, nextPanel, loginPanel,
    loginPanel2, questionPanel;
  JTextField tname;
  JPasswordField tpass;
  JLabel lquestion, la, lb, lc, ld, lname, lpass;
  JButton a, b, c, d, next, loginOk, loginCancel;
  JMenuBar mb = new JMenuBar();
  JMenu user = new JMenu("User");
  JMenu start = new JMenu("Start");
  JMenu turnin = new JMenu("Turnin");
  JMenuItem newUser = new JMenuItem("New User");
  JMenuItem login = new JMenuItem("Log In");
  JMenuItem logout = new JMenuItem("Log Out");
  JMenuItem startQuiz = new JMenuItem("Start Quiz");
  JMenuItem quizTurnin = new JMenuItem("Turn in");
  boolean tmp = false;
  String[] arrayL;
  int line = 0;
  int random;
  int[] s = new int[3];
  String s1 = null;
  String s2 = null;
  int grade = 0;
  String choose = "";
  String choice = "";
  String[] answer;
  int tt = 1;
  int index = -1;
  String[][] userData;
 
  public CSquiz() {
   createFrame();
   createQuestionArray();
   createRandom();
   createAnswer();
   createLogin();
   user.add(newUser);
   user.add(login);
   user.add(logout);
   start.add(startQuiz);
   turnin.add(quizTurnin);
   logout.setEnabled(false);
   start.setEnabled(false);
   turnin.setEnabled(false);
   next.setEnabled(false);
   a.setEnabled(false);
   b.setEnabled(false);
   c.setEnabled(false);
   d.setEnabled(false);
   newUser.addActionListener(this);
   user.addActionListener(this);
   start.addActionListener(this);
   turnin.addActionListener(this);
   login.addActionListener(this);
   logout.addActionListener(this);
   startQuiz.addActionListener(this);
   quizTurnin.addActionListener(this);
   next.addActionListener(this);
  }
 
  public void actionPerformed(ActionEvent e) {
   Object o = e.getSource();
   if (o.equals(newUser)) {
       boolean tmpnew = false;
    String frameTitle = "New User";
    String enterName = "Please enter a user name:";
    String enterPassword = "Please enter your password:";
    String password;
    int Ucount=0;
    
    String name = JOptionPane.showInputDialog(null, enterName,
      frameTitle, JOptionPane.QUESTION_MESSAGE);
    if (name == null) {
     return;
    }
    if (name.equals("")) {
     JOptionPane.showMessageDialog(null,
       "You didn't enter your name!", "Error",
       JOptionPane.ERROR_MESSAGE);
     return;
    }
 
    File Userdata = new File("UserData.txt");
    // create File
    if (!Userdata.exists()) {
     PrintWriter print = null;
     try {
      print = new PrintWriter(Userdata);
     } catch (Exception e1) {
     }
     print.print("");
     print.close();
    }
    //check if the user name has already exists
    createUserData();
    Scanner check = null;
    try {
     check = new Scanner(Userdata);
 
    } catch (Exception e1) {
     JOptionPane.showMessageDialog(null,
       "User database can not be found!", "Error",
       JOptionPane.ERROR_MESSAGE);
     return;
    }
        while (check.hasNextLine() && Ucount < userData.length) {
     if (name.equals(userData[Ucount][0])) {
       tmpnew = true;
      JOptionPane.showMessageDialog(null,
             "The user name exists in database!", "Error",
             JOptionPane.ERROR_MESSAGE);
      break;
     }
     Ucount++;
    }
   
        if(tmpnew == false){
    password = JOptionPane.showInputDialog(null, enterPassword,
      "PASSWORD", JOptionPane.QUESTION_MESSAGE);
 
    if (password == null) {
     return;
    }
    if (password.equals("")) {
     JOptionPane.showMessageDialog(null,
       "You didn't enter your password!", "Error",
       JOptionPane.ERROR_MESSAGE);
     return;
    }
 
    Random r = new Random();
    String rnum = Integer.toString(r.nextInt(10))
      + Integer.toString(r.nextInt(10));
    String hashpass = Integer.toString((password + rnum).hashCode());
 
    try {
     FileWriter writer = new FileWriter("UserData.txt", true);
     writer.write(name + "," + rnum + "," + hashpass + "\n");
     JOptionPane.showMessageDialog(null,
       "You have successfully created your account!",
       "Complete", JOptionPane.INFORMATION_MESSAGE);
     writer.close();
    } catch (IOException e1) {
     e1.printStackTrace();
    }
    rnum = null;
        }
   }
   else if (o.equals(login)) {
    flogin.setVisible(true);
    createUserData();
   }
 
   else if (o.equals(logout)) {
    JOptionPane.showMessageDialog(null,
      "You have successfully logged out!", "Log out",
      JOptionPane.INFORMATION_MESSAGE);
    login.setEnabled(true);
    newUser.setEnabled(true);
    logout.setEnabled(false);
    start.setEnabled(false);
    turnin.setEnabled(false);
    // Clear window
    lquestion.setText(null);
    la.setText(null);
    lb.setText(null);
    lc.setText(null);
    ld.setText(null);
    next.setEnabled(false);
    a.setEnabled(false);
    b.setEnabled(false);
    c.setEnabled(false);
    d.setEnabled(false);
    tt = 1;
    grade = 0;
    choice = "";
    s1 = null;
    s2 = null;
    tmp = false;
    createRandom();
    tname.setText(null);
    tpass.setText(null);
   }
   else if (o.equals(startQuiz)) {
     
         String text, ftext = "";
    File g = new File("Grade.txt");
    
    //create grade file if it does not exists
        if (!g.exists()) {
     PrintWriter print = null;
     try {
      print = new PrintWriter(g);
     } catch (Exception e1) {
     }
     print.print("");
     print.close();
    }
    
    Scanner in = null;
    try {
     in = new Scanner(g);
    } catch (Exception e1) {
     JOptionPane.showMessageDialog(null,
       "Grade File does not exists!", "Error",
       JOptionPane.ERROR_MESSAGE);
    }
    while (in.hasNextLine()) {
     text = in.nextLine();
     ftext = ftext + text;
    }
    index = ftext.indexOf(s1);
     
     
     
    turnin.setEnabled(true);
    start.setEnabled(false);
    next.setEnabled(true);
    a.setEnabled(true);
    b.setEnabled(true);
    c.setEnabled(true);
    d.setEnabled(true);
    // Question display
    if (index >= 0) {
      turnin.setEnabled(false);
     JOptionPane.showMessageDialog(null,
       "Sorry! Your answer have already turned in!", "Error",
       JOptionPane.ERROR_MESSAGE);
    } else {
     lquestion.setText(arrayL[s[0] * 5]);
     la.setText(arrayL[s[0] * 5 + 1]);
     lb.setText(arrayL[s[0] * 5 + 2]);
     lc.setText(arrayL[s[0] * 5 + 3]);
     ld.setText(arrayL[s[0] * 5 + 4]);
    }
   }
   else if (o.equals(next)) {
    lquestion.setText(arrayL[s[tt] * 5]);
    la.setText(arrayL[s[tt] * 5 + 1]);
    lb.setText(arrayL[s[tt] * 5 + 2]);
    lc.setText(arrayL[s[tt] * 5 + 3]);
    ld.setText(arrayL[s[tt] * 5 + 4]);
 
    if (tt == 2) {
     next.setEnabled(false);
    }
    if (choice.equals(answer[s[tt - 1]])) {
     grade += 1;
     System.out.println(grade);
    }
    tt++;
    choice = "";
   }
 
   if (o.equals(a)) {
    choice = "a";
   }
   if (o.equals(b)) {
    choice = "b";
   }
   if (o.equals(c)) {
    choice = "c";
   }
   if (o.equals(d)) {
    choice = "d";
   }
   if (o.equals(quizTurnin)) {
    start.setEnabled(true);
    turnin.setEnabled(false);
 
    lquestion.setText(null);
    la.setText(null);
    lb.setText(null);
    lc.setText(null);
    ld.setText(null);
    tt = 1;
    createRandom();
    // Save user's grade......
    if (choice.equals(answer[s[2]])) {
     grade += 1;
     System.out.println(grade);
    }
    next.setEnabled(false);
    a.setEnabled(false);
    b.setEnabled(false);
    c.setEnabled(false);
    d.setEnabled(false);
    File Grade = new File("Grade.txt");
 
    if (!Grade.exists()) {
     PrintWriter Gp = null;
     try {
      Gp = new PrintWriter(Grade);
     } catch (Exception e1) {
     }
     Gp.print("");
     Gp.close();
    }
    try {
     FileWriter writer = new FileWriter("Grade.txt", true);
     writer.write(s1 + " " + grade + "\n");
     writer.close();
    } catch (IOException e1) {
     e1.printStackTrace();
    }
    JOptionPane.showMessageDialog(null, "Your grade: " + grade
      + " out of 3.", "Turn in", JOptionPane.INFORMATION_MESSAGE);
    grade = 0;
    choice = "";
 
   }
 
   if (o.equals(loginCancel)) {
    flogin.setVisible(false);
   }
 
   if (o.equals(loginOk)) {
    s1 = tname.getText();
    s2 = String.valueOf(tpass.getPassword());
    String s3 = "empty";
    int Ucount = 0;
    File file = new File("UserData.txt");
    
    if(!file.exists()){
      PrintWriter bo = null;
      try{
        bo = new PrintWriter(file);
      }catch(Exception e1){}
    }
    Scanner s = null;
    try {
     s = new Scanner(file);
    } catch (Exception e1) {
    }
    
    
    while (s.hasNextLine() && Ucount < userData.length) {
     if (s1.equals(userData[Ucount][0])) {
      s3 = Integer.toString((s2 + userData[Ucount][1]).hashCode());
      if (s3.equals(userData[Ucount][2])) {
       tmp = true;
       login.setEnabled(false);
       newUser.setEnabled(false);
       logout.setEnabled(true);
       start.setEnabled(true);
       JOptionPane.showMessageDialog(null,
         "You have successfully logged in!", "Welcome",
         JOptionPane.INFORMATION_MESSAGE);
       flogin.setVisible(false);
      }

      break;
     }
     Ucount++;
    }
   
    if(tmp == false) {
     JOptionPane.showMessageDialog(null,
       "Wrong User Name or Wrong Password!", "Error",
       JOptionPane.ERROR_MESSAGE);
     return;
    }
 
    // check whether this user have took the quiz
    String text, ftext = "";
    File g = new File("Grade.txt");
    
    //create grade file if it does not exists
        if (!g.exists()) {
     PrintWriter print = null;
     try {
      print = new PrintWriter(g);
     } catch (Exception e1) {
     }
     print.print("");
     print.close();
    }
    
    Scanner in = null;
    try {
     in = new Scanner(g);
    } catch (Exception e1) {
     JOptionPane.showMessageDialog(null,
       "Grade File does not exists!", "Error",
       JOptionPane.ERROR_MESSAGE);
    }
    while (in.hasNextLine()) {
     text = in.nextLine();
     ftext = ftext + text;
    }
    index = ftext.indexOf(s1);
   }
  }
 
  public void createQuestionArray() {
   File question = new File("Questions.txt");
   Scanner in = null;
   try {
    in = new Scanner(question);
    while (in.hasNext()) {
     in.nextLine();
     line++;
    }
    arrayL = new String[line];
    in = new Scanner(new File("Questions.txt"));
    for (int i = 0; i < line; i++) {
     arrayL[i] = in.nextLine();
    }
   } catch (Exception e) {
    JOptionPane.showMessageDialog(null,
      "QuestionFile does not exists!", "Error",
      JOptionPane.ERROR_MESSAGE);
    System.exit(0);
   }
  }
 
  public void createRandom() {
   int newLine = line / 5;
   Random r = new Random();
   int flag = r.nextInt(newLine - 1);
   s[0] = flag;
   flag = r.nextInt(newLine - 1);
   while (flag == s[0]) {
    flag = r.nextInt(newLine - 1);
   }
   s[1] = flag;
   flag = r.nextInt(newLine - 1);
   while (flag == s[0] | flag == s[1]) {
    flag = r.nextInt(newLine - 1);
   }
   s[2] = flag;
  }
 
  public void createAnswer() {
   Scanner in = null;
   int count = 0;
   File ans = new File("Sol.txt");
   try {
    in = new Scanner(ans);
    while (in.hasNext()) {
     in.nextLine();
     count++;
    }
    in = new Scanner(new File("Sol.txt"));
    answer = new String[count];
    for (int i = 0; i < count; i++) {
     answer[i] = in.nextLine();
    }
   } catch (Exception e) {
    JOptionPane.showMessageDialog(null,
      "QuestionFile does not exists!", "Error",
      JOptionPane.ERROR_MESSAGE);
    System.exit(0);
   }
  }
 
  public void createUserData() {
   int userNum1 = 0;
   File file1 = new File("UserData.txt");
   
   if(!file1.exists()){
      PrintWriter bo = null;
      try{
        bo = new PrintWriter(file1);
      }catch(Exception e1){}
    }
   
   Scanner sc = null;
   try {
    sc = new Scanner(file1);
   } catch (Exception e1) {
   }
   while (sc.hasNext()) {
    sc.nextLine();
    userNum1++;
   }
   userData = new String[userNum1][3];
   int userNum = 0;
   File file = new File("UserData.txt");
   Scanner s = null;
   try {
    s = new Scanner(file);
   } catch (Exception e1) {
   }
   while (s.hasNext()) {
    userData[userNum] = s.nextLine().split(",");
    userNum++;
   }
  }
 
  public void createLogin() {
   flogin = new JFrame("Login");
   flogin.setSize(200, 110);
   flogin.setResizable(false);
   flogin.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
   flogin.setLayout(new BorderLayout());
   loginPanel = new JPanel(new GridLayout(2, 2));
   tname = new JTextField();
   tpass = new JPasswordField();
   loginPanel.add(lname);
   loginPanel.add(tname);
   loginPanel.add(lpass);
   loginPanel.add(tpass);
   flogin.add(loginPanel, BorderLayout.NORTH);
   loginPanel2 = new JPanel();
   loginPanel2.add(loginOk);
   loginOk.addActionListener(this);
   loginPanel2.add(loginCancel);
   loginCancel.addActionListener(this);
   flogin.add(loginPanel2, BorderLayout.SOUTH);
   flogin.setVisible(false);
  }
 
  public void createFrame() {
   f = new JFrame("CS Quiz System");
   mb.add(user);
   mb.add(start);
   mb.add(turnin);
   f.setJMenuBar(mb);
   createMasterPanel();
   f.add(p);
   f.setSize(500, 500);
   f.setResizable(true);
   f.setVisible(true);
   f.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
  }
 
  public void createMasterPanel() {
 
   createLabel();
   createButton();
   createLabel();
   lquestion = new JLabel();
   buttonPanel = new JPanel(new GridLayout(4, 1));
   nextPanel = new JPanel();
   nextPanel.add(next);
 
   buttonPanel = new JPanel(new GridLayout(4, 1));
   buttonPanel.add(a);
   buttonPanel.add(b);
   buttonPanel.add(c);
   buttonPanel.add(d);
 
   answerPanel = new JPanel(new GridLayout(4, 1));
   answerPanel.add(la);
   answerPanel.add(lb);
   answerPanel.add(lc);
   answerPanel.add(ld);
 
   optionPanel = new JPanel(new GridLayout(1, 2));
   optionPanel.add(buttonPanel);
   optionPanel.add(answerPanel);
 
   p = new JPanel(new BorderLayout());
   p.add(lquestion, BorderLayout.NORTH);
   p.add(optionPanel, BorderLayout.CENTER);
   p.add(nextPanel, BorderLayout.SOUTH);
  }
 
  public void createLabel() {
 
   la = new JLabel();
   lb = new JLabel();
   lc = new JLabel();
   ld = new JLabel();
   lname = new JLabel("USER:");
   lpass = new JLabel("PASSWORD:");
  }
 
  public void createButton() {
   a = new JButton("A");
   a.addActionListener(this);
   b = new JButton("B");
   b.addActionListener(this);
   c = new JButton("C");
   c.addActionListener(this);
   d = new JButton("D");
   d.addActionListener(this);
   next = new JButton("Next");
   loginOk = new JButton("OK");
   loginCancel = new JButton("Cancel");
  }
 
  public static void main(String[] args) {
   new CSquiz();
  }
 }
