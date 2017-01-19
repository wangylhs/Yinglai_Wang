
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
	
	public static void main(String args[]){
		//System.out.println(convertFromBase("101",2));
		//System.out.println(IsUniqueChar("habjdf"));
	}
}
