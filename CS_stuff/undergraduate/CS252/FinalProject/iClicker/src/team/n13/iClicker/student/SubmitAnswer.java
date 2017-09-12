package team.n13.iClicker.student;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import team.n13.iClicker.Login;
import team.n13.iClicker.R;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.GestureDetector.OnGestureListener;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
//import android.widget.Toast;

public class SubmitAnswer extends Activity implements OnClickListener, OnGestureListener{
    /** Called when the activity is first created. */

	private GestureDetector gDetector;
	
	private TextView setQuestion;
    private Button answer_A=null;
	private Button answer_B=null;
	private Button answer_C=null;
	private Button answer_D=null;
	private Button answer_E=null;
	private TextView chkA, chkB, chkC, chkD, chkE;
	public static boolean exit=false;
	public static Activity here;
    private String question="";
	
    @SuppressWarnings("deprecation")
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.submit_answer);
        gDetector = new GestureDetector(this);
        //loading
		try {
	         Socket skt = new Socket(Login.SERVER_PATH,12345);
	         String data = "student|getquestion\n";
	         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
	         System.out.print("Sending string: " + data + "\n");
	         out.writeChars(data);
	         //reading the return value from server
			 DataInputStream in = new DataInputStream(skt.getInputStream());
			 
		     System.out.print("Received string: ");

	    	 char temp;
	         while ( (temp = in.readChar()) != '|' ){
	        	 question += temp; // Read one line and output it
	         }

	         System.out.printf("%s\n", question);
		     out.close();
		     in.close();
		     skt.close();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//Toast.makeText(getBaseContext(),"This question is: "+question, Toast.LENGTH_SHORT).show(); 
		
		 if(question!= null && (question.indexOf("A.") == -1 || question.indexOf("B.") == -1)){
			 	Intent intent=new Intent();
				intent.setClass(SubmitAnswer.this,team.n13.iClicker.student.FreeResponse.class);
				startActivity(intent);
		 }
        
        setQuestion = (TextView)findViewById(R.id.tvQuestion);
        if(!question.equals(null))
        	setQuestion.setText(question);
        else
        	setQuestion.setText("");
        chkA=(TextView)findViewById(R.id.tvA);
        answer_A=(Button)findViewById(R.id.answer_A);
        chkB=(TextView)findViewById(R.id.tvB);
        answer_B=(Button)findViewById(R.id.answer_B);
        chkC=(TextView)findViewById(R.id.tvC);
        answer_C=(Button)findViewById(R.id.answer_C);
        chkD=(TextView)findViewById(R.id.tvD);
        answer_D=(Button)findViewById(R.id.answer_D);
        chkE=(TextView)findViewById(R.id.tvE);
        answer_E=(Button)findViewById(R.id.answer_E);
        answer_A.setText(R.string.answer_A);
        answer_B.setText(R.string.answer_B);
        answer_C.setText(R.string.answer_C);
        answer_D.setText(R.string.answer_D);
        answer_E.setText(R.string.answer_E);
        
        answer_A.setOnClickListener(this);
        answer_B.setOnClickListener(this);
        answer_C.setOnClickListener(this);
        answer_D.setOnClickListener(this);
        answer_E.setOnClickListener(this);
        
        here=this;
    }
    public boolean onKeyDown(int keyCode, KeyEvent event)  {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            System.exit(0);
        }

        return super.onKeyDown(keyCode, event);
    }

	public void onClick(View v) {
		// TODO Auto-generated method stub
		//Intent intent=new Intent();
		if(v==answer_A){
			chkA.setText("✓");
			chkB.setText("");
			chkC.setText("");
			chkD.setText("");
			chkE.setText("");
			try {
		         Socket skt = new Socket(Login.SERVER_PATH,12345);
		         System.out.print("Server has connected!\n");
		         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
		         System.out.print("Sending string: '" + "A" + "'\n");
		         out.writeChars("student|submit|"+Login.userLogin+"|"+Login.userPass+"|A\n");
		         out.close();
		         skt.close();
		      }
		      catch(Exception e) {
		         System.out.print("Whoops! It didn't work!\n");
		      }
			//Toast.makeText(getBaseContext(),getString(R.string.answer_A), Toast.LENGTH_SHORT).show(); 
		}
		else if(v==answer_B){
			chkA.setText("");
			chkB.setText("✓");
			chkC.setText("");
			chkD.setText("");
			chkE.setText("");
			try {
		         Socket skt = new Socket(Login.SERVER_PATH,12345);
		         System.out.print("Client has connected!\n");
		         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
		         System.out.print("Sending string: '" + "B" + "'\n");
		         out.writeChars("student|submit|"+Login.userLogin+"|"+Login.userPass+"|B\n");
		         out.close();
		         skt.close();
		      }
		      catch(Exception e) {
		         System.out.print("Whoops! It didn't work!\n");
		      }
			//Toast.makeText(getBaseContext(),getString(R.string.answer_B), Toast.LENGTH_SHORT).show(); 
		}
		else if(v==answer_C){
			chkA.setText("");
			chkB.setText("");
			chkC.setText("✓");
			chkD.setText("");
			chkE.setText("");
			try {
		         Socket skt = new Socket(Login.SERVER_PATH,12345);
		         System.out.print("Client has connected!\n");
		         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
		         System.out.print("Sending string: '" + "C" + "'\n");
		         out.writeChars("student|submit|"+Login.userLogin+"|"+Login.userPass+"|C\n");
		         out.close();
		         skt.close();
		      }
		      catch(Exception e) {
		         System.out.print("Whoops! It didn't work!\n");
		      }
			//Toast.makeText(getBaseContext(),getString(R.string.answer_C), Toast.LENGTH_SHORT).show(); 
		}
		else if(v==answer_D){
			chkA.setText("");
			chkB.setText("");
			chkC.setText("");
			chkD.setText("✓");
			chkE.setText("");
			try {
		         Socket skt = new Socket(Login.SERVER_PATH,12345);
		         System.out.print("Client has connected!\n");
		         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
		         System.out.print("Sending string: '" + "D" + "'\n");
		         out.writeChars("student|submit|"+Login.userLogin+"|"+Login.userPass+"|D\n");
		         out.close();
		         skt.close();
		      }
		      catch(Exception e) {
		         System.out.print("Whoops! It didn't work!\n");
		      }
			//Toast.makeText(getBaseContext(),getString(R.string.answer_D), Toast.LENGTH_SHORT).show();
		}
		else if(v==answer_E){
			chkA.setText("");
			chkB.setText("");
			chkC.setText("");
			chkD.setText("");
			chkE.setText("✓");
			try {
		         Socket skt = new Socket(Login.SERVER_PATH,12345);
		         System.out.print("Client has connected!\n");
		         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
		         System.out.print("Sending string: '" + "E" + "'\n");
		         out.writeChars("student|submit|"+Login.userLogin+"|"+Login.userPass+"|E\n");
		         out.close();
		         skt.close();
		      }
		      catch(Exception e) {
		         System.out.print("Whoops! It didn't work!\n");
		      }
			//Toast.makeText(getBaseContext(),getString(R.string.answer_E), Toast.LENGTH_SHORT).show(); 
		}
	}
	@Override
	public boolean onDown(MotionEvent e) {
		// TODO Auto-generated method stub
		return false;
	}
	@Override
	public boolean onFling(MotionEvent start, MotionEvent finish, float velocityX,
			float velocityY) {
		// TODO Auto-generated method stub
        if (start.getRawY() > finish.getRawY()) {
			try {
		         Socket skt = new Socket(Login.SERVER_PATH,12345);
		         String data = "student|getquestion\n";
		         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
		         System.out.print("Sending string: " + data + "\n");
		         out.writeChars(data);
		         //reading the return value from server
				 DataInputStream in = new DataInputStream(skt.getInputStream());
				 
			     System.out.print("Received string: ");
			     
			     String old_question = question;
			     question="";
		    	 char temp;
		         while ( (temp = in.readChar()) != '|' ){
		        	 question += temp; // Read one line and output it
		         }
		         
		         if(!question.equals(old_question)){
		        	 setQuestion.setText(question);
		 			 chkA.setText("");
					 chkB.setText("");
					 chkC.setText("");
					 chkD.setText("");
					 chkE.setText("");
		         }

		         System.out.printf("%s\n", question);
			     out.close();
			     in.close();
			     skt.close();
			} catch (UnknownHostException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			 if(!question.equals(null) && (question.indexOf("A.") == -1 || question.indexOf("B.") == -1)){
				 	Intent intent=new Intent();
					intent.setClass(SubmitAnswer.this,team.n13.iClicker.student.FreeResponse.class);
				 	here.finish();
					startActivity(intent);
			 }
        }
        return true;
	}
	@Override
	public void onLongPress(MotionEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX,
			float distanceY) {
		// TODO Auto-generated method stub
		return false;
	}
	@Override
	public void onShowPress(MotionEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public boolean onSingleTapUp(MotionEvent e) {
		// TODO Auto-generated method stub
		return false;
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent me) {
	return gDetector.onTouchEvent(me);
	}
}