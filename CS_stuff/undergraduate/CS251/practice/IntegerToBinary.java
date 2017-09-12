public class IntegerToBinary{
	public static void main(String[] args){
		String s = "";
		//int N = Integer.parseInt(args[0]);
		for(int n = Integer.parseInt(args[0]); n>0; n =n/2)
			s = (n%2) + s;
		System.out.println(s);
	}
}
