
public class Sum2 extends Thread{
	int [] a;
    int sum;
    String evenOdd; // Indicates whether to sum even or odd indexed elements
    long delay=5; // Delay for accessing each element in seconds.
    
    public Sum2(int [] a, String evenOdd){
        this.a=a;
        this.evenOdd=evenOdd;
    }// End of constructor
    
    public void run(){
        int start, increment=2;
        if(evenOdd.equals("even")){
            start=0;  
        }else{
            start=1;  
        }// End of start index setting.
        
        sum=0;// Initlialize sum to 0.
       
        long lastAccess=System.currentTimeMillis();
        for(int i=start; i<a.length; i=i+increment){
            long currentTime=System.currentTimeMillis();
            while((currentTime-lastAccess)<delay*1000){
                currentTime=System.currentTimeMillis();
            };
            System.out.println("5 seconds!");
            sum=sum+a[i];
            lastAccess=System.currentTimeMillis();
        }// End of summation loop.
    }// End of run()
    
    public int getSum(){
        return sum;
    }// End of getSum()
}
