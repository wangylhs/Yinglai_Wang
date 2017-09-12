import java.util.*;

public class MyThread extends Thread{
	ConcExercise ce;
	int n;
	
	public MyThread(ConcExercise ce, int n){
		this.ce = ce;
		this.n = n;
	}
	
	public void run(){
		Random r = new Random();
		
		for(int i=0; i<n; i++){
			ce.t.setText(Integer.toString(r.nextInt(100)));
			try {
				sleep(1000);
			} catch (Exception e) {
				e.printStackTrace();
			}		
		}
		
	}
}
