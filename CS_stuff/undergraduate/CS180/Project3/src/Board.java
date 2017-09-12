import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Image;

import javax.swing.JButton;
import javax.swing.JPanel;

/**
 * @author jfranklin773
 * 
 */
public class Board extends JPanel {
  
  private int[][] state;
  public final static int EMPTY = 0;
  public final static int RED = 1;
  public final static int BLACK = 2;
  public final static int BLACK_KING = 3;
  public final static int RED_KING = 4;
  public final static int HIGHLIGHT = 5;

  public Board() {
    state = new int[8][8];
    setSize(400, 400);
  }
  
  public void paint(Graphics g){

    for(int y=0;y<8;y++){
      for(int x=0;x<8;x++){
        if(x%2 == y%2){
           g.setColor(Color.DARK_GRAY);
        }
        else{
           g.setColor(Color.GRAY);

        }
        g.fillRect(x*50,y*50,50,50);
        
        switch(state[x][y]){
          case EMPTY: break;
          case RED: 
            g.setColor(Color.RED);
            g.fillOval(x*50,y*50,50,50);
            break;
          case BLACK:
            g.setColor(Color.BLACK);
            g.fillOval(x*50,y*50,50,50);
            break;
          case BLACK_KING:
            g.setColor(Color.BLACK);
            g.fillOval(x*50,y*50,50,50);
            g.setColor(Color.WHITE);
            g.drawString("K",x*50+25,y*50+25);
            break;
          case RED_KING:
            g.setColor(Color.RED);
            g.fillOval(x*50,y*50,45,45);
            g.setColor(Color.WHITE);
            g.drawString("K",x*50+25,y*50+25);
            break;
          case HIGHLIGHT:
            g.setColor(Color.YELLOW);
            g.drawOval(x*50,y*50,50,50);
            break;
          default:
            break;
        }

      }
    }
  }
  
  public void setState(int x,int y, int s){
    state[x][y]=s;
  }
  
  public int getState(int x,int y){
    return state[x][y];
  }
  
  
  
}
