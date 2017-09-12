import java.util.*;
public class Maximum {
	public static void main(String[] args){
		int a,b,c;
		Scanner s = new Scanner(System.in);
		System.out.println("Please enter three integer numbers separately: ");
		a = s.nextInt();
		b = s.nextInt();
		c = s.nextInt();
		
		if(a<b){
			a=b;
		}
		if(a<c){
			a=c;
		}
		System.out.println("The maximum number is: "+a);
		
	}

}
