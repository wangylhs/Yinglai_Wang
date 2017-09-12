/*
 * Simple RSA program
 * p=11, q=13, n=143, e=7, d=103
 * Message to encrypt: M = 112
 * Message to decrypt: C = 7
 * developed by Murtadha Aljubran
 */

import java.math.BigInteger;

public class RSA {
    public static void main(String args[]){
    	BigInteger y,md,M;
    	BigInteger w = BigInteger.valueOf(0);
    	w=BigInteger.valueOf(112).pow(7);
    	y=BigInteger.valueOf(143);
    	md=w.divide(y);
    	M=w.subtract(y.multiply(md));
    	//System.out.printf("Part1 (Encryption) :\n%d\n%d\n%d\n%d\n%d\n",w,y,md,y.multiply(md),M);
    	System.out.printf("Part1 (Encryption) :\n%d\n",M);
    	w=w.pow(103);
    	md=w.divide(y);
    	M=w.subtract(y.multiply(md));
    	//System.out.printf("Confirmation (Decryption) :\n%d\n%d\n%d\n%d\n%d\n",w,y,md,y.multiply(md),M);
    	System.out.printf("Confirmation (Decryption) :\n%d\n",M);
    	System.out.println("-----------------------------------------------------------");
    	w=BigInteger.valueOf(7).pow(103);
    	md=w.divide(y);
    	M=w.subtract(y.multiply(md));
    	//System.out.printf("Part2 (Decryption) :\n%d\n%d\n%d\n%d\n%d\n",w,y,md,y.multiply(md),M);
    	System.out.printf("Part2 (Decryption) :\n%d\n",M);
    	w=w.pow(7);
    	md=w.divide(y);
    	M=w.subtract(y.multiply(md));
    	//System.out.printf("Confirmation (Encryption) :\n%d\n%d\n%d\n%d\n%d\n",w,y,md,y.multiply(md),M);
    	System.out.printf("Confirmation (Encryption) :\n%d\n",M);
    	w=BigInteger.valueOf(6*16*113);
    	md=w.divide(y);
    	M=w.subtract(y.multiply(md));
    	System.out.printf("Confirmation of my result (Manual Decryption) :\n%d\n",M);
    }
}