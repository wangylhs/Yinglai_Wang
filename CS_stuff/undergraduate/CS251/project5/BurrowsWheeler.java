import java.util.*;
public class BurrowsWheeler {
	static int size = 0;
	static byte [] buff = new byte[1024];
	static Integer [] indices = null;
	public static void encode(){
		while(!BinaryStdIn.isEmpty()) {
			byte b = BinaryStdIn.readByte();
			if (size>=buff.length) 
				buff = Arrays.copyOf(buff, size * 2);
			buff[size++] = b;
		}
		
		indices = new Integer[size];
		for(int i=0; i<size; i++) 
			indices[i] = new Integer(i);
		
		Arrays.sort(indices, new MyComparator());
		
		for(int i=0; i<size; i++) {
			if (indices[i].equals(0)) {
				BinaryStdOut.write(i);
				break;
			}
		}

		for(int i=0; i<size; i++) {
			BinaryStdOut.write(buff[(size - 1 + indices[i]) % size]);
		}
		BinaryStdOut.flush();
	}

	public static class MyComparator implements Comparator<Integer>{
		public int compare(Integer a, Integer b)
		{
			for(int i=0; i<size; i++) {
				int x = getInt(buff[(i+a) % size]);
				int y = getInt(buff[(i+b) % size]);
				if (x!=y) return x - y;
			}
			return 0;
		}
		public boolean equals(Object a) {return false;}
	}
	public static int getInt(byte b)
	{
		return ( b + 256 ) % 256;
	}
	public static void decode() {
		int [] counts = new int[257];
		int start = BinaryStdIn.readInt();
		while(!BinaryStdIn.isEmpty()) {
			byte b = BinaryStdIn.readByte();
			if (size>=buff.length) 
				buff = Arrays.copyOf(buff, size * 2);
			buff[size++] = b;
			counts[getInt(b) + 1]++;
		}
		
		for(int i=2; i<256; i++)
			counts[i] += counts[i-1];

		indices = new Integer[size];
		for(int i=0; i<size; i++) {
			int b = getInt(buff[i]);
			indices[counts[b]++] = i; 
		}
		start = indices[start];
		for(int i=0; i<size; i++) {
			BinaryStdOut.write(buff[start]);
			start = indices[start];
		}
		BinaryStdOut.flush();
	}

	public static void main(String[] args){
		if      (args[0].equals("-")) encode();
		else if (args[0].equals("+")) decode();
		else throw new RuntimeException("Illegal command line argument");
	}
}