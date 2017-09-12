import java.util.*;
import java.io.*;
import org.antlr.v4.runtime.*;
import java.lang.String;

public class Micro{
	
	
	public static void main(String[] args){
        MicroLexer lex=null;
        CharStream input=null;
        try{
            input = new ANTLRFileStream(args[0]);
            lex = new MicroLexer(input);
		}catch(Exception e){
            System.out.println("Error");
            System.exit(0);
        }
        Token temp;
        temp=lex.nextToken();
        //System.out.println("----");
        //System.out.println("----"+temp.getText());
        while(temp.getText() != "<EOF>")
        {
            System.out.println("Token Type: " + lex.tokenNames[temp.getType()]);
        
            System.out.println("Value: " + temp.getText());
            temp = lex.nextToken();
            }
        }
}