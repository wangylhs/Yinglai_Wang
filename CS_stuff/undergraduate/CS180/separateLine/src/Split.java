import java.util.Scanner;
public class Split {
	public static void main(String[] args){
	java.lang.String x;
	Scanner s = new Scanner(System.in);
		x = s.nextLine();
		for(int i=0; i<x.length(); i++){
			if(x.charAt(i)!=' '){
				System.out.print(x.charAt(i));
			}
			else
				System.out.println("\n");
		}
				
	}


}
