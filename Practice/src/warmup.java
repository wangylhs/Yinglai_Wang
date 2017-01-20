import java.util.Scanner;


public class warmup {
	
	static int convertFromBase(String num, int base){
		if(base<2 || base>10 && base!=16) return -1;
		int value=0;
		for(int i=num.length()-1;i>=0;i--){
			int digit = digitToValue(num.charAt(i));
			if(digit<0 || digit>base) return -1;
			int exp = num.length()-1-i;
			value += digit*Math.pow(base, exp);
		}
		return value;
	}
	
	static int digitToValue(char c){
		if(c=='0' || c=='1') return c-48;
		if(c>='A' && c<='F') return c-55;
		return -1;
	}
	
	static boolean IsUniqueChar(String str){
		//determine if a string has all unique characters
		if(str.length()>128) return false;
		boolean[] mark = new boolean[128];
		for(int i=0;i<str.length();i++){
			if(mark[str.charAt(i)]) return false;
			mark[str.charAt(i)]=true;
		}
		return true;
	}
	
	static boolean CheckPermutation(String str1, String str2){
		//check if one is permutation of the other
		if(str1.length()!=str2.length()) return false;
		int[] mark = new int[128];
		for(int i=0; i<str1.length(); i++){
			mark[str1.charAt(i)]++;
		}
		for(int i=0; i<str2.length(); i++){
			mark[str2.charAt(i)]--;
			if(mark[str2.charAt(i)]<0) return false;
		}
		return true;
	}
	
	static char[] replaceSpaces(char[] str, int truelength){
		//replace white space with %20
		int ct=0;
		int index;
		for(int i=0;i<truelength;i++){
			if(str[i]==' ') ct++;
		}
		index=truelength+ct*2;
		if(truelength<str.length) str[truelength]='\0';
		for(int i=truelength-1;i>=0;i--){
			if(str[i]==' '){
				str[index-1]='0';
				str[index-2]='2';
				str[index-3]='%';
				index=index-3;
			}else{
				str[index-1]=str[i];
				index--;
			}
		}
		return str;
	}
	
	static int checkIntExp(int input){
		
		int max=(int) Math.sqrt(input);
		int min=1;
		for(int i=min;i<=max;i++){
			for(int j=2;j<100;j++){
				if(Math.pow(i, j)>input) break;
				if(Math.pow(i, j)==input) return 1;
			}
		}
		return 0;
	}
	
	public static void main(String args[]){
		//System.out.println(convertFromBase("101",2));
		//System.out.println(IsUniqueChar("habjdf"));
		//System.out.println(CheckPermutation("abcakn","aabknn"));
		//char[] temp = "Mr John Smith      ".toCharArray();
		//System.out.println(replaceSpaces(temp,13));
		Scanner s = new Scanner(System.in);
		System.out.println("Input test case numbers T");
		int T = s.nextInt();
		int[] input= new int[T];
		for(int i=0;i<T;i++){
			System.out.println("Input test case: ");
			input[i]=s.nextInt();
		}
		System.out.println("Output:");
		for(int i=0;i<T;i++){
			System.out.println(checkIntExp(input[i]));
		}
	}
}
