import java.lang.*;
public class TwoDouble{
	public static void main(String[] args){
		double x = Double.parseDouble(args[0]);
		double y = Double.parseDouble(args[1]);
		if((x > 0.0 && x < 1.0)&&(y > 0.0 && y < 1.0))
			System.out.println("true");
		else
			System.out.println("false");
	}
}
