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
		//check an integer can be expressed as x^y
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
	
	static boolean checkPalindrom(String str){
		//check if given string is a permutation of palindrom
		String s = (str.toLowerCase()).replaceAll(" ", "");
		char[] c = s.toCharArray();
		int[] marker = new int[128];
		for(int i=0; i<s.length();i++){
			marker[c[i]]++;
		}
		int odd_ct=0;
		for(int i : marker){
			if(odd_ct>1) return false;
			if(i%2!=0) odd_ct++;
		}
		return true;
	}
	
	static boolean OneAway(String s1, String s2){
		//check if they are one edit away
		int diff_ct;
		int index1, index2;
		//check for replacement
		if(s1.length()==s2.length()){
			diff_ct=0;
			for(int i=0;i<s1.length();i++){
				if(diff_ct>1) return false;
				if(s1.charAt(i)!=s2.charAt(i)) diff_ct++;
			}
			return true;
		}else if(s1.length()-s2.length()==1){
			//check for remove/insertion
			index1=0;index2=0;
			while(index1<s1.length() && index2<s2.length()){
				if(s1.charAt(index1)!=s2.charAt(index2)){
					if(index1!=index2) return false;
					index1++;
				}else{
					index1++;
					index2++;
				}
			}
			return true;
		
		}else if(s2.length()-s1.length()==1){
			//check for remove/insertion
			index1=0;index2=0;
			while(index1<s1.length() && index2<s2.length()){
				if(s1.charAt(index1)!=s2.charAt(index2)){
					if(index1!=index2) return false;
					index2++;
				}else{
					index1++;
					index2++;
				}
			}
			return true;
		}
		return false;
	}
	
	static String compress(String str){
		//compress string in a simple way "aabbaaccc" -> "a2b2a2c3"
		StringBuilder sb = new StringBuilder();
		int ct=0;
		for(int i=0;i<str.length();i++){
			ct++;
			if(i+1>=str.length() || str.charAt(i+1)!=str.charAt(i)){
				sb.append(str.charAt(i));
				sb.append(ct);
				ct=0;
			}
		}
		return sb.length()<str.length() ?  sb.toString() : str;
		
	}
	
	public static void main(String args[]){
		//System.out.println(convertFromBase("101",2));
		//System.out.println(IsUniqueChar("habjdf"));
		//System.out.println(CheckPermutation("abcakn","aabknn"));
		//char[] temp = "Mr John Smith      ".toCharArray();
		//System.out.println(replaceSpaces(temp,13));
		/*Scanner s = new Scanner(System.in);
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
		*/
		//System.out.println(OneAway("pale","bkle"));
		System.out.println(compress("abca"));
	}
}
