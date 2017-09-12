import java.util.Arrays;
import java.util.Scanner;
import java.io.*;

public class Q3 {
	public static void main(String[] args){
		Scanner in = null;
		try{
		in = new Scanner(new File("src/name.txt"));
		}catch(Exception e){}
		String[] names = new String[10];
		int n=0;
		String name = null;
		
		while(in.hasNextLine()){
			name = in.nextLine();
			try{
				names[n] = name;
			}catch(ArrayIndexOutOfBoundsException e){
				names = Arrays.copyOfRange(names, 0, names.length*2);
				names[n] = name;
			}
			n++;
			Arrays.sort(names, 0, n);
			
			for(int i=0; i<n; i++){
				System.out.println(names[i]);
			}
		}
	}
}
