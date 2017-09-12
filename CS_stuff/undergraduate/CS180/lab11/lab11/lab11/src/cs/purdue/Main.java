package cs.purdue;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.Toast;

public class Main extends Activity {
    /** Called when the activity is first created. */
	
	private SensorManager sensorManager;
	private Sensor sensor;
	private Accelerometer accel;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);        
        setContentView(new CanvasView(this));
        
        accel = new Accelerometer();
        
		sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		sensor = sensorManager.getSensorList(Sensor.TYPE_ACCELEROMETER).get(0);
 		Toast.makeText(Main.this, Lab11.user_name, Toast.LENGTH_LONG).show();

    }
    
	@Override
	protected void onResume() {
		super.onResume();
		sensorManager.registerListener(accel, sensor,
				SensorManager.SENSOR_DELAY_GAME);
	}
	
	@Override
	protected void onStop() {
		sensorManager.unregisterListener(accel);
		super.onStop();
	}
	
}