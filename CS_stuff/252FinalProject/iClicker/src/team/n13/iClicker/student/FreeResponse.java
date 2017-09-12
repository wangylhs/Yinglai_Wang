package team.n13.iClicker.student;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import team.n13.iClicker.Login;
import team.n13.iClicker.R;
import android.app.Activity;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.view.GestureDetector.OnGestureListener;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class FreeResponse extends Activity implements OnClickListener, OnGestureListener{
    /** Called when the activity is first created. */

	private GestureDetector gDetector;
	
	private TextView setQuestion, putAnswer;
    private Button submit=null;
	private TextView chkSubmit, showSubmittedAnswer;
	private EditText getAnswer;
	String userAnswer;
	private String question = "";
	public static boolean exit=false;
	public static Activity here;
	
    @SuppressWarnings("deprecation")
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.free_response);
        gDetector = new GestureDetector(this);
        //loading questions
        //
        
		try {
	         Socket skt = new Socket(Login.SERVER_PATH,12345);
	         String data = "student|getquestion\n";
	         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
	         System.out.print("Sending string: " + data + "\n");
	         out.writeChars(data);
	         //reading the return value from server
			 DataInputStream in = new DataInputStream(skt.getInputStream());
			 
		     System.out.print("Received string: ");
		     
		     question="";
		     char temp;
	         while ( (temp = in.readChar()) != '\n' ){
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
        
        setQuestion = (TextView)findViewById(R.id.tvFreeResQuestion);
        setQuestion.setText(question);
        putAnswer = (TextView)findViewById(R.id.tvPutAnswer);
        putAnswer.setText(R.string.putAnswer);
        getAnswer = (EditText)findViewById(R.id.etFreeResAnswer);
        showSubmittedAnswer = (TextView)findViewById(R.id.tvAnswerSubmitted);
        chkSubmit=(TextView)findViewById(R.id.tvShowTick);
        submit=(Button)findViewById(R.id.bSubmit);
        submit.setText(R.string.submit);
        
        submit.setOnClickListener(this);
        
        here=this;
    }

	public void onClick(View v) {
		// TODO Auto-generated method stub
		if(v==submit){
			userAnswer=getAnswer.getText().toString();
			showSubmittedAnswer.setText(userAnswer);
			chkSubmit.setText("✓");
			try {
		         Socket skt = new Socket(Login.SERVER_PATH,12345);
		         System.out.print("Client has connected!\n");
		         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
		         System.out.print("Sending string: '" + "SUBMIT" + "'\n");
		         out.writeChars("student|submit|"+Login.userLogin+"|"+Login.userPass+"|" + userAnswer + "\n");
		         out.close();
		         skt.close();
		      }
		      catch(Exception e) {
		         System.out.print("Whoops! It didn't work!\n");
		      }
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
			Toast display = Toast.makeText(FreeResponse.this,"This is the last question.", Toast.LENGTH_SHORT);
			display.show();
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