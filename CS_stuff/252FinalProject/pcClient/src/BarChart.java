import java.util.*;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.Image;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.lang.Object;
import java.net.Socket;
import java.io.InputStream;
import java.io.FilterInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

 
public class BarChart extends JPanel{
  public int[] values;
  public String[] items;
  public String title;
  public BarChart(int[] v, String[] i, String t) {
    values = v;
    items = i;
    title = t;
  }
  
  
  public void paintComponent(Graphics g) {
    super.paintComponent(g);
    if (values == null || values.length == 0)
      return;
    int minValue = 0;
    int maxValue = 0;
    for (int i = 0; i < values.length; i++) {
      if (minValue > values[i])
        minValue = values[i];
      if (maxValue < values[i])
        maxValue = values[i];
    }
    
    Dimension d = getSize();
    int clientWidth = d.width;
    int clientHeight = d.height;
    int barWidth = clientWidth / values.length-120;
    
    Font titleFont = new Font("PLAIN", Font.BOLD, 40);
    FontMetrics titleFontMetrics = g.getFontMetrics(titleFont);
    Font TMRFont=new Font("SansSerif", Font.BOLD, 18);
    Font labelFont = new Font("SansSerif", Font.PLAIN, 40);
    FontMetrics labelFontMetrics = g.getFontMetrics(labelFont);
    int titleWidth = titleFontMetrics.stringWidth(title);
    int y = titleFontMetrics.getAscent();
    int x = (clientWidth - titleWidth) / 2;
    g.setColor(Color.black);
    g.fillRect(0,0,1400,800);
    g.setColor(Color.white);
    g.setFont(titleFont);
    g.drawString(title, x, y);
    g.setFont(labelFont);
    int top = titleFontMetrics.getHeight()+65;
    int bottom = labelFontMetrics.getHeight()+35;
    double scale;
    if(maxValue!=0){
     scale = (clientHeight - top - bottom) / (maxValue - minValue);}
    else{scale = (clientHeight - top - bottom);}
    y = clientHeight - labelFontMetrics.getDescent();
    g.setColor(Color.white);
    for (int i = 0; i < values.length; i++) {
      int valueX = i * barWidth+1;
      int valueY = top;
      int height = (int) (values[i] * scale);
      if (values[i] >= 0)
        valueY += (int) ((maxValue - values[i]) * scale);
      else {
        valueY += (int) (maxValue * scale);
        height = -height;
      }
      switch(i){
        case 0: g.setColor(Color.red); break;
        case 1: g.setColor(Color.yellow);break;
        case 2: g.setColor(Color.green);break;
        case 3: g.setColor(Color.blue);break;
        case 4: g.setColor(Color.pink);break;
      }
      if(values[i]>0){
      g.fillRect(valueX+190+i*55, valueY, barWidth- 2, 690-valueY);
      g.setColor(Color.black);
      g.drawRect(valueX+190+i*55, valueY, barWidth- 2, 690-valueY);
      }
      g.setColor(Color.white);
      int labelWidth = labelFontMetrics.stringWidth(items[i]);
      int countX=valueX+190+i*55;
      g.drawString(String.format("%d",values[i]),countX+65,valueY-5);
      x = i * barWidth + (barWidth - labelWidth) / 2;
      g.drawString(items[i], countX+69, y-10);
    }
  }
  
  public static void main(String[] argv) {
    int[] values = new int[5];
    String[] names = new String[5];
    //need to communicate with server
    String title;
    JFrame f = new JFrame();
    f.pack();
    f.setSize(1400,800 );
     DateFormat dateFormat = new SimpleDateFormat("MM / dd / yyyy   HH:mm:ss");
    Date date = new Date();
    f.setTitle("I-Clicker          "+dateFormat.format(date));
    //need to communicate with server to get values
    for(int i=0;i<5;i++){
      names[i]=String.format("%c",'A'+i);
    }
    title="Sample Quiz";
    try{
           Socket socket = new Socket("borg16.cs.purdue.edu",12345);
           DataInputStream input = new DataInputStream(socket.getInputStream());
           DataOutputStream output = new DataOutputStream(socket.getOutputStream());
           output.writeChars("admin|answercount|2\n");
           values[0]=input.readInt();
           values[1]=input.readInt();
           values[2]=input.readInt();
           values[3]=input.readInt();
           values[4]=input.readInt();
           input.close();
           output.close();
           socket.close();}
           catch(Exception e){}
    //
    BarChart BC=new BarChart(values, names, title);
    f.getContentPane().add(BC);
  
  
    f.setVisible(true);
    while(true){
      dateFormat = new SimpleDateFormat("MM / dd / yyyy   HH:mm:ss");
      date = new Date();
       f.setTitle("I-Clicker          "+dateFormat.format(date));
       try {
      Thread.currentThread().sleep(500);
      } 
       catch(InterruptedException e) {}
           try{
           Socket socket = new Socket("borg16.cs.purdue.edu",12345);
           DataInputStream input = new DataInputStream(socket.getInputStream());
           DataOutputStream output = new DataOutputStream(socket.getOutputStream());
           output.writeChars("admin|answercount|2\n");
           values[0]=input.readInt();;
           values[1]=input.readInt();
           values[2]=input.readInt();
           values[3]=input.readInt();
           values[4]=input.readInt();
           input.close();
           output.close();
           socket.close();}
           catch(Exception e){}
       BC=new BarChart(values, names, title);
       f.getContentPane().add(BC);
       
       f.setVisible(true);
    }
 }
}