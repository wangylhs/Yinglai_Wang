import java.util.*;
public class MoveToFront {
	static int indices[] = new int[256];
	public static int getInt(byte b)
	{
		return ( b + 256 ) % 256;
	}

	public static void encode()
	{
		while(!BinaryStdIn.isEmpty()) {
			int b = getInt(BinaryStdIn.readByte());
			int out = indices[b];
			BinaryStdOut.write((byte)out);
			for(int i=0; i<256; i++) if (indices[i] < out) indices[i]++;
			indices[b] = 0;
		}
		BinaryStdOut.flush();
	}

	public static void decode() 
	{
		while(!BinaryStdIn.isEmpty()) {
			int out = getInt(BinaryStdIn.readByte());
			int b = indices[out];
			BinaryStdOut.write((byte)b);
			for(int i=out; i>0; i--) indices[i] = indices[i-1];
			indices[0] = b;
		}
		BinaryStdOut.flush();
	}

	public static void main(String[] args){
		for(int i=0; i<256; i++) indices[i] = i;
		if      (args[0].equals("-")) encode();
		else if (args[0].equals("+")) decode();
		else throw new RuntimeException("Illegal command line argument");
	}
}
