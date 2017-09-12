package cs.purdue;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class CanvasThread extends Thread {
	
	SurfaceHolder h;
	SurfaceView sv;
	static boolean running=true;
	Paint paint;
	Paint background;
	
	public CanvasThread(SurfaceHolder holder){
		h=holder;
		paint = new Paint();
		paint.setColor(Color.BLUE);
		background = new Paint();
		background.setColor(Color.WHITE);
	}
	
	public void run(){
		Lab11.main(null);
		while(running){
			Canvas c = h.lockCanvas();
			c.drawRect(0, 0, c.getWidth(), c.getHeight(), background);
			c.drawCircle(Lab11.y, Lab11.x, 20, paint);
			h.unlockCanvasAndPost(c);
		}
	}

}
