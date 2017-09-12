import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JFrame;

 
public class BC extends JFrame{
  public BarChart bc;
  private int[] values;
  private String[] items;
  private String title;
  private int ID;
  private JFrame f;
  private Boolean isCLosed;
  public BC(int id){
    values = new int[5];
    items = new String[5];
    title="Quiz Sample";
    f = new JFrame();
    ID=id;
    isCLosed=false;
    f.pack();
    f.setSize(1400,800 );
     DateFormat dateFormat = new SimpleDateFormat("MM / dd / yyyy   HH:mm:ss");
    Date date = new Date();
    f.setTitle("I-Clicker          "+dateFormat.format(date));
    for(int i=0;i<5;i++){
      items[i]=String.format("%c",'A'+i);
    }
    getData();
    bc=new BarChart(values, items, title);
    f.getContentPane().add(bc);
    f.setVisible(true);
    WindowAdapter wndCloser=new WindowAdapter(){
     public void windowClosing(WindowEvent e){
    		isCLosed=true;
    		f.setVisible(false);
    	}
    };
    f.addWindowListener(wndCloser);
  }
  
  private void getData(){
  try{
           Socket socket = new Socket("sslab14.cs.purdue.edu",12345);
           DataInputStream input = new DataInputStream(socket.getInputStream());
           DataOutputStream output = new DataOutputStream(socket.getOutputStream());
           output.writeChars(String.format("admin|answercount|%d\n",ID));
           values[0]=input.readInt();
           values[1]=input.readInt();
           values[2]=input.readInt();
           values[3]=input.readInt();
           values[4]=input.readInt();
           input.close();
           output.close();
           socket.close();}
           catch(Exception e){}
  
}
  
  public void update(){
     SimpleDateFormat dateFormat;
      Date date;
    dateFormat = new SimpleDateFormat("MM / dd / yyyy   HH:mm:ss");
    date = new Date();
  while(!isCLosed){
     try {
      Thread.sleep(500);
      }
       catch(Exception e){}
     f.setTitle("I-Clicker          "+dateFormat.format(date)); 
     try{
       Socket socket = new Socket("sslab14.cs.purdue.edu",12345);
       DataInputStream input = new DataInputStream(socket.getInputStream());
       DataOutputStream output = new DataOutputStream(socket.getOutputStream());
       output.writeChars(String.format("admin|answercount|%d\n",ID));
       values[0]=input.readInt();
       values[1]=input.readInt();
       values[2]=input.readInt();
       values[3]=input.readInt();
       values[4]=input.readInt();
     
       socket.close();}
       catch(Exception e){}
     bc=new BarChart(values, items, title);
     f.getContentPane().add(bc);
     f.invalidate();
     f.validate();
  }
 } 
  public static void main(String[]argv){
   BC ba=new BC(2);
   ba.update();
  }
}