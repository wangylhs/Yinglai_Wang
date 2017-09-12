package cs.purdue;

import android.content.Context;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class CanvasView extends SurfaceView implements SurfaceHolder.Callback {
	
	CanvasThread thread;

	public CanvasView(Context context) {
		super(context);
		getHolder().addCallback(this);
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,int height) {
		Lab11.width=height;
		Lab11.height=width;
		thread.running=true;
		thread.start();
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		thread = new CanvasThread(holder);
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		thread.running=false;
	}

}
