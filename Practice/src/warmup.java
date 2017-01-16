
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
	
	public static void main(String args[]){
		System.out.println(convertFromBase("101",2));
	}
}
