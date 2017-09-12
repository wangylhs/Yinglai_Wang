import java.util.*;
import java.io.*;

public class Project2{
	public static void main(String[] args) throws Exception{
//Declared variables 	
		String text;
		String prompt1,prompt2;
//Need user prompt
		System.out.println("Enter name of the input file:");
		Scanner userIn = new Scanner(System.in);
		prompt1 = userIn.nextLine();
		Scanner userOut = new Scanner(System.in);
		System.out.println("Enter name of the output file:");
		prompt2 = userOut.nextLine();
//File in & out
		File input = new File("src/"+prompt1+".html");
		File outPut = new File("src/"+prompt2+".txt");
		Scanner i = null;
		try{
			i = new Scanner(input);
		}catch(Exception e){
			System.out.println("The specified input file does not exist.");
			System.exit(0);
		}
		FileOutputStream putout = new FileOutputStream(outPut);
		PrintWriter out=null;
		try{
			out = new PrintWriter(putout);
		}catch(Exception e){
			System.out.println("The specified output file does not exist.");
			System.exit(0);
		}
//Execute
		while(i.hasNext()){
			int start;
			int end;
			text = i.nextLine();
			text=text.replace("<html>","");
            text=text.replace("</html>","" );
            text=text.replace("<head>","");
            text=text.replace("</head>","" );
            text=text.replace("<body>","" );
            text=text.replace("</body>","" );
            text=text.replace("<h1>","\n");
            text=text.replace("</h1>", "\n"); 
            text=text.replace("</p>","\n\n");
            text=text.replace("<p>","\n");
            text=text.replace("<br>","\n");
            text=text.replace("</a>","");
            //text=text.replaceAll("<a href=.*",a);
			
            start = text.indexOf("<a href");
            if(start>0)
            {
            	end = text.indexOf(">");
            
            	if(end>0){
            		text = text.substring(0,start-1) + " " + text.substring(end+1, text.length());
            	}
            }
          
            
            System.out.println(text);
			out.print(text);
		}

	}
}