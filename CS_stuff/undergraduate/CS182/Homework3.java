import java.math.BigInteger;

public class Homework3 {
	static BigInteger fact(int inN) {
		int n = inN;
		BigInteger result = new BigInteger("1");
		while (n>1) {
			result = result.multiply(new BigInteger(String.valueOf(n)));
			n = n - 1;
		}
		
		return result;
	}
	
	static BigInteger C(int inN, int inK) {
		int n = inN;
		int k = inK;
		int nMinusK = n - k;
		BigInteger result = new BigInteger("1");
		result = fact(n).divide(fact(k));
		result = result.divide(fact(nMinusK));
		return result;
	}
	
	static double logBase2(BigInteger in) {
		String str = in.toString();
		double logTwo = Math.log10(2);
		double logValue = Double.MIN_VALUE;
		double inputToLog = -1;
		if (str.charAt(0) != 0) {
			//process
			int length = str.length();
			if (length == 1) {
				inputToLog = new Double(str).doubleValue();
				logValue = Math.log10(inputToLog) / logTwo;
			} else if (length > 1) {
				String firstPart = str.substring(0,1);
				int upperIndex;
				if (length - 1 > 16) {
					upperIndex = 17;
				} else {
					upperIndex = length;
				}
				String secondPart = str.substring(1, upperIndex);
				int exponent = length - 1;
				inputToLog = new Double(firstPart + "." + secondPart).doubleValue();
				logValue = Math.log10(inputToLog) / logTwo + exponent / logTwo;
			} else {
				System.out.println("Should not be here.");
			}
		}
		return logValue;
	}
	
	public static void main(String args[]) {
		BigInteger c;
		for(int n=1; n<=500; n++){
			double out = 0;
			for(int k=1; k<=n; k++){
				c = C(n, k);
				double log = logBase2(c);
				double result = c.doubleValue();
				double power = Math.pow(2, n);
				out += (result * log) / power;
				
			}
			System.out.println(n + "\t" + out);
		}
	}
}






