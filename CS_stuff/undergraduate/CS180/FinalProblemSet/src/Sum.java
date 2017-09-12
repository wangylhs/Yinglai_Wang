
public class Sum extends Thread{
	int[] array;
	String s;
	int sum = 0;
	long delay = 5;
	
	public Sum(int[] a, String s){
		array = a;
		this.s = s;
	}
	public void run(){
		int start;
		if(s.equals("even")){
			start = 0;
		}else{
			start = 1;
		}
		long lastAccess = System.currentTimeMillis();	
		for(int i=start; i<array.length;i+=2){
			long currenttime = System.currentTimeMillis();
			while((currenttime-lastAccess)<delay*1000){
				currenttime = System.currentTimeMillis();
			}
			System.out.println("5 seconds!");
			sum = sum + array[i];
			lastAccess = System.currentTimeMillis();
		}
		
	}
	public int getSum(){
		return sum;
	}
}
