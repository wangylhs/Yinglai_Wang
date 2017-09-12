
public class WBTest {
	public static void main(String[] args) {
		String filename = "weatherData.txt";
		int delay = 1;
		double avgTemperature;
		

		WB myWB = new WB(filename, delay); // initialize the thread
		myWB.start(); // start the tread
		
		// get the avg temperature
		avgTemperature = myWB.getAverageTemp(); 
		System.out.println("Avg Temp (before join): " + avgTemperature);
		
		// wait until it is done
		try{
			myWB.join(); 
		}catch(Exception e){}
		
		// get the avg temperature
		avgTemperature = myWB.getAverageTemp(); 
		System.out.println("Avg Temp (after join): " + avgTemperature);
		
		// print the result
		if( avgTemperature > 0){
			System.out.println("Average Temperature is: " + avgTemperature);
		}else{
			System.out.println("Average Temperature not available");
		}
	}
}

 