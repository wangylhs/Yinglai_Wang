import java.io.*;
import java.util.*;


public class WB extends Thread {
	private double avgTemperature;
	private double [] temperatures;
	private int numOfTempsRead;
	String filename;
	int delay;
	long threadStartTime;
	int fileReadTrials;
	File file;
	Scanner in;
	
	public WB(String filename, int delay) {
		// set filename and delay
		this.filename = filename;
		this.delay = delay;
		file = null; in = null;
		fileReadTrials = 0;
		
		temperatures = new double[6];
		avgTemperature = 0;
		numOfTempsRead = 0;
	}

	public void run(){
		
		// get the initial time
		threadStartTime = System.currentTimeMillis();
		//System.out.println("Started the thread @ " + threadStartTime);
		while( (System.currentTimeMillis() - threadStartTime) < 60000 && (fileReadTrials < 3) && (numOfTempsRead<6) ){
		
			//System.out.println("in while @ " + threadStartTime);
			// step 1 - open the file
			try{
				file = new File(filename);
				in = new Scanner(file);
			}catch(FileNotFoundException e){
				System.out.println("File " + file.getName() + " not found!");
			}
			if( in != null){
				if( in.hasNext() ){
					temperatures[numOfTempsRead] = in.nextDouble(); // read the temperature
				} else{
					fileReadTrials++; // unsuccessful file reads
				}
				
				// step 2 - close the file and print the temp				
				in.close();
			}
			
			System.out.println("Temperature is: " + temperatures[numOfTempsRead]);
			numOfTempsRead++;
			
			// step3 - delay 10 sec
			long waitStart = System.currentTimeMillis();
			while( (System.currentTimeMillis() - waitStart) < (1000 * this.delay) ){ /* wait */ }
		}
		
		// step 5
		for(int i=0; i < numOfTempsRead; i++){
			avgTemperature += temperatures[i];
		}
		avgTemperature /= numOfTempsRead;
	}
	
	public double getAverageTemp(){
		if(this.isAlive()){
			return -1;	
		}else{
			return avgTemperature;
		}
	}
}
