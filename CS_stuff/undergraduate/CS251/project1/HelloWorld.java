
public class HelloWorld {
	public static void main(String args[]){
		String word = "HelloWorld";
		while(!StdIn.isEmpty()){
			String line = "";
			int num = StdIn.readInt();
			for(int i=0; i<num; i++){
				int s = StdIn.readInt();
				line += (char)s;
			}
			int time = StdIn.readInt();
			for(int i=0; i<time;i++){
				StdOut.print(word + line + " ");
			}
			StdOut.print("\n");
		}
	}
}
