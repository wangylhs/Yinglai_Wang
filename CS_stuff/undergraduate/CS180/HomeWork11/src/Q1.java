
public class Q1 {
	static int count = 0;
	public int Fibonacci(int n){
		count++;
		if(n==1||n==2){
			//count++;
			return 1;
		}else{
			//count++;
			return Fibonacci(n-1)+Fibonacci(n-2);
		}
	}
	
	public static void main(String[] args){
		Q1 f = new Q1();
		f.Fibonacci(20);
		System.out.println(count);
	}
}
