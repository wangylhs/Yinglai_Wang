
public class Problem1 {
	public int GCD(int x, int y){
		if(y==0){
			return x;
		}else{
			return GCD(y, x%y);
		}
	}
	public static void main(String[] args){
		Problem1 g = new Problem1();
		System.out.println(g.GCD(4, 7));
	}
}
