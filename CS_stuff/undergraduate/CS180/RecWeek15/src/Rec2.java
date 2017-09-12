
public class Rec2 {
	public int GCD(int x, int y){
		if(y==0){
			return x;
		}else{
			return GCD(y, x%y);
		}
	}
	public static void main(String[] args){
		Rec2 g = new Rec2();
		System.out.println(g.GCD(4, 8));
	}
}
