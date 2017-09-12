
public class Problem1 {
	
	
	public static void main(String[] args){
		System.out.println(GCD(5,8));
	}
	
	public static int GCD(int x, int y){
		if(y==0){
			return x;
		}else{
			return GCD(y,x%y);
		}
	}
}
