
public class Rec1 {
	
	public int Fib(int n){
	
		if(n==0){
			return 0;
		}
		if(n==1){
			return 1;
		}else{
			return Fib(n-1)+Fib(n-2);
		}
	}
	
	public static void main(String[] args){
		Rec1 f = new Rec1();
		System.out.println(f.Fib(3));
		
	}
}
