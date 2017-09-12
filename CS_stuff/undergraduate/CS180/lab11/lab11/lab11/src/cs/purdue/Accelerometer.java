package cs.purdue;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;

public class Accelerometer implements SensorEventListener {

	static float x,y,z;
	
	@Override
	public void onAccuracyChanged(Sensor arg0, int arg1) {
	}

	@Override
	public void onSensorChanged(SensorEvent event) {
		x = event.values[0];
		y = event.values[1];
		z = event.values[2];
		try{Thread.sleep(20);}catch(Exception e){}
	}

}
