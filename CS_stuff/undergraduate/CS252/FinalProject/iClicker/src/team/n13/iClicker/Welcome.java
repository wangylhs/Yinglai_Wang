package team.n13.iClicker;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

// Welcome page
public class Welcome extends Activity {
    /** Called when the activity is first created. */
	 public static Button invisible=null;
	 public static Activity here;

	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        here=this;
        Timer timer = new Timer();
		TimerTask task = new TimerTask() {
		   @Override
		   public void run() {
			   Welcome.here.finish();
			   Intent intent=new Intent();
			   intent.setClass(Welcome.this, Login.class);
			   startActivity(intent);
			   overridePendingTransition(R.anim.fade, R.anim.hold);
		  }
		};
	        
		timer.schedule(task,1000 * 2);// start TimerTask after 3 seconds	
	}
}