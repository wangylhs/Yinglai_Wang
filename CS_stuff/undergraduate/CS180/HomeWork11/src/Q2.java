public class Q2{
	public static void main(String[] args){
		try{
			Thread.sleep(1000);
		}/*catch(Exception e){
			System.out.println("Exception Occurred!");
		}*/catch(InterruptedException e){
			System.out.println("Woke up early!");
		}
	}
}
