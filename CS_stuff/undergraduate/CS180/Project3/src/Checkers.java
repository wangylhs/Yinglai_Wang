import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Checkers  extends JApplet implements ActionListener, MouseListener {
	public void init (){
		add(frame);		
	}
	
	
	
	

  
   Board board;
   JFrame frame;
   JPanel masterPanel, subPanelN, subPanelS;
   JLabel gameName, score, turn;
   JButton reset;
   int p1pieces, p2pieces;
   int lastX;
   int lastY;

   boolean redTurn = true;
   public static Checkers checkers_1 = new Checkers();
      
   

    
  /*
   * Constructor
   */
  public Checkers() {
    p1pieces = 12;
    p2pieces = 12;
    //createFrame();
  }
  

	
    
  public static void main(String[] args) {
	
	  
	 //CheckApplet checkapplet = new CheckApplet();
    checkers_1.initializeBoard(); // Initializing the board
    checkers_1.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
  }
  
  public void mouseClicked(MouseEvent e) {
    int x = e.getX() / 50;
    int y = e.getY() / 50;
        

    
    System.out.println("X: " + x + " - Y: " + y);
    
    if(board.getState(x, y)==1 || board.getState(x, y)==2){
      unHighlight();
      Highlight(x, y);
    }
    
    if(board.getState(x, y)==5){
      unHighlight();
      move(x,y);
    }
    
  }
  
  public void unHighlight(){
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        if(board.getState(i, j)==5){
          board.setState(i, j, Board.EMPTY);
        }
      }
    }
    board.repaint();
  }
  
  
  public void Highlight(int x, int y) {
    // Highlight Movable Locations
    
    board.repaint();
    if (board.getState(x, y) != 0) { // If there is a piece at x & y
      if ((board.getState(x, y) == 1) && redTurn) { // If Red
        if (x>=0 && y>=0) {// if not out of bounds
          if(x-1>=0 && y-1>=0){
            if ((board.getState(x - 1, y - 1) == 0)) { // if empty
              board.setState(x - 1, y - 1, Board.HIGHLIGHT);
            }
          }
          if(x-2>=0&&y-2>=0){
            if ((board.getState(x - 2, y - 2) == 0) && (board.getState(x - 1, y - 1) == 2)) {
              board.setState(x - 2, y - 2, Board.HIGHLIGHT);
            }
          }
        }
        if (x <= 7 && y >= 0) {// if not out of bounds
          if(x+1<=7&&y-1>=0){
            if ((board.getState(x + 1, y - 1) == 0)) { // if empty
              board.setState(x + 1, y - 1, Board.HIGHLIGHT);
            }
          }
          if(x+2<=7&&y-2>=0){
            if ((board.getState(x + 2, y - 2) == 0) && (board.getState(x + 1, y - 1) == 2)) {
              board.setState(x + 2, y - 2, Board.HIGHLIGHT);
            }
          }
        }
        
      } else if ((board.getState(x, y) == 2) && !redTurn) { // if Black
        if (x >= 0 && y <= 7) {// if not out of bounds
          if((x-1>=0)&&(y+1<=7)){
            if ((board.getState(x - 1, y + 1) == 0)) {// if empty
              board.setState(x - 1, y + 1, Board.HIGHLIGHT);
            }
          }
          if((x-2>=0)&&(y+2<=7)){
            if ((board.getState(x - 2, y + 2) == 0) && (board.getState(x - 1, y + 1) == 1)) {
              board.setState(x - 2, y + 2, Board.HIGHLIGHT);
            }
          }
        }
        if (x <= 7 && y <= 7) {// if not out of bounds
          if((x+1<=7)&&(y+1<=7)){
            if ((board.getState(x + 1, y + 1) == 0)) {// if empty
              board.setState(x + 1, y + 1, Board.HIGHLIGHT);
            }
          }
          if((x+2<=7)&&(y+2<=7)){
            if ((board.getState(x + 2, y + 2) == 0) && (board.getState(x + 1, y + 1) == 1)) {
              board.setState(x + 2, y + 2, Board.HIGHLIGHT);
            }
          }
        }
      }
    }
    lastX = x;
    lastY = y;
    board.repaint();
  }
  public void move(int x, int y){
    if((board.getState(lastX, lastY)==1)){
      board.setState(x, y, 1);
      board.setState(lastX, lastY, 0);  
      //leftRed
      if((lastX-x==2)&&(lastY-y==2)){
        if(board.getState(lastX-1, lastY-1)==2){
          board.setState(lastX-1, lastY-1, 0);
          p2pieces--;
        }
      }
      //rightRed
      if((lastX-x==-2)&&(lastY-y==2)){
        if(board.getState(lastX+1, lastY-1)==2){
          board.setState(lastX+1, lastY-1, 0);
          p2pieces--;
        }
      }
    }
    if((board.getState(lastX, lastY)==2)){
      board.setState(x,y,2);
      board.setState(lastX, lastY, 0);
      //leftBlack
      if((lastX-x==2)&&(lastY-y==-2)){
        if(board.getState(lastX-1, lastY+1)==1){
          board.setState(lastX-1, lastY+1, 0);
          p1pieces--;
        }
      }
      //rightBlack
      if((lastX-x==-2)&&(lastY-y==-2)){
        if(board.getState(lastX+1, lastY+1)==1){
          board.setState(lastX+1, lastY+1, 0);
          p1pieces--;
        }
      }
    }
    
    if(redTurn){
      redTurn = false;
    }
    else{
      redTurn = true;
    }
    
    if(redTurn){
      checkers_1.setLabels(1, p1pieces, p2pieces);
    }
    
    else{
      checkers_1.setLabels(2, p1pieces, p2pieces);
    }
    board.repaint();
  }
  
  public void mouseEntered(MouseEvent e) {
  }
  
  public void mouseExited(MouseEvent e) {
  }
  
  public void mousePressed(MouseEvent e) {
  }
  
  public void mouseReleased(MouseEvent e) {
  }
  
  /*
   * Creating the Frame & calling other create Methods
   */
  public void createFrame() {
    frame = new JFrame();
    frame.setSize(400, 550);
    createBoard();
    createLabels();
    createButton();
    createPanel();
    frame.add(masterPanel);
    frame.setVisible(true);
  }
  
  
  /*
   * Adding frame to the applet.
   * 
   */
 
  
  /*
   * Creating the Board
   */
  public void createBoard() {
    board = new Board();
    board.addMouseListener(this);
  }
  
  /*
   * Creating Panels & Layout
   */
  public void createPanel() {
    
    // Initializing Panels
    masterPanel = new JPanel(new BorderLayout());
    subPanelN = new JPanel(new BorderLayout());
    subPanelS = new JPanel(new BorderLayout());
    
    // Resizing Panels
    masterPanel.setSize(400, 550);
    subPanelN.setSize(400, 80);
    subPanelS.setSize(400, 30);
    
    // Adding Widgets to Sub-Panels
    subPanelN.add(gameName, BorderLayout.NORTH);
    subPanelN.add(turn, BorderLayout.SOUTH);
    subPanelS.add(score, BorderLayout.NORTH);
    subPanelS.add(reset, BorderLayout.SOUTH);
    
    // Adding subPanels & Board to Master Panel
    masterPanel.add(subPanelN, BorderLayout.NORTH);
    masterPanel.add(board, BorderLayout.CENTER);
    masterPanel.add(subPanelS, BorderLayout.SOUTH);
  }
  
  /*
   * Initialize Button
   */
  public void createButton() {
    reset = new JButton("New Game");
    reset.addActionListener(this);
  }
  
  public void actionPerformed(ActionEvent e) {
    Object click = e.getSource();
    // Just Checking if button works
    if (click.equals(reset)) {
      redTurn = true;
      p1pieces = 12;
      p2pieces = 12;
      checkers_1.setLabels(1, p1pieces, p2pieces);
      checkers_1.removeAllPieces();
      checkers_1.initializeBoard();
      board.repaint();
    }
  }
  
  /*
   * Initializing Labels
   */
  public void createLabels() {
    gameName = new JLabel("Checkers");
    gameName.setFont(new Font("Comic Sans MS", Font.BOLD, 40));
    
    turn = new JLabel("Player 1's Turn");
    turn.setFont(new Font("Serif", Font.BOLD, 14));
    
    score = new JLabel("Player 1 has 12 pieces. Player 2 has 12 pieces.");
    score.setFont(new Font("Serif", Font.BOLD, 14));
  }
  
  /*
   * Initialize Labels with updated values
   */
  public void setLabels(int playerTurn, int p1, int p2) {
    turn.setText("Player " + Integer.toString(playerTurn) + "'s Turn");
    score.setText("Player 1 has " + Integer.toString(p1) + " pieces."
                    + " Player 2 has " + Integer.toString(p2) + " pieces.");
  }
  
  /*
   * Remove all the pieces from the board
   */
  public void removeAllPieces() {
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (board.getState(col, row) != 0) {
          checkers_1.board.setState(col, row, Board.EMPTY);
        }
      }
    }
  }
  
  /*
   * This method initializes the board by placing all the players pieces on
   * the board.
   */
  public void initializeBoard() {
    int row = 0;
    int col = 0;
    
    while (row < 3) {
      if (row == 0 || row == 2) {
        col = 1;
      } else {
        col = 0;
      }
      while (col < 8) {
        board.setState(col, row, Board.BLACK);
        col += 2;
      }
      row++;
    }
    
    row = 5;
    col = 0;
    
    while (row < 8) {
      if (row == 5 || row == 7) {
        col = 0;
      } else {
        col = 1;
      }
      while (col < 8) {
        board.setState(col, row, Board.RED);
        col += 2;
      }
      row++;
    }
  }
}// End of Class