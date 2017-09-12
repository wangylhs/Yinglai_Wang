import java.net.*;
import java.io.*;

public class fsclient {
	public static void main(String args[]) throws Exception{
		if(args.length!=4){
			System.out.println("usage: <IP address> <Port number> <file-path> <filename>");
			System.exit(0);
		}
		String line;
		File f = new File(args[3]);
		PrintWriter pw = null;
		try {
			pw = new PrintWriter(new FileWriter(args[3]));
			Socket skt = new Socket(args[0], Integer.parseInt(args[1]));
			BufferedReader in = new BufferedReader(new InputStreamReader(skt.getInputStream()));
			PrintWriter out = new PrintWriter(skt.getOutputStream(), true);
			System.out.print("Sending request: '" + args[2] + "'\n");
			out.print(args[2]);
			out.flush();
			while((line = in.readLine())!=null){
				if(line.contains("INVALID REQUEST") && line.length()==15){
                    in.close();
                    pw.close();
                    skt.close();
                    System.out.println("INVALID REQUEST");
                    System.exit(0);
                }else{
                    pw.println(line);
                }
				//System.out.println(newline);
			}
			System.out.println("Download completed.");
			in.close();
			pw.close();
			skt.close();
		}
		catch(Exception e) {
			System.out.print("Whoops! It didn't work!\n");
		}


	}
    

}
