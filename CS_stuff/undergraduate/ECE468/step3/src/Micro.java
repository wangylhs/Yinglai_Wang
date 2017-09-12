import java.util.*;
import java.io.*;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.lang.String;

public class Micro{
    static ArrayList<SymbolTable> symbolTable;
    public Micro(){
    }
    
	public static void main(String[] args) throws IOException{
        
        Micro micro = new Micro();
        MicroLexer lex=null;
        MicroParser parser=null;
        CharStream input=null;
        CommonTokenStream token=null;
        ParseTree tree = null;
        try{
            input = new ANTLRFileStream(args[0]);
            lex = new MicroLexer(input);
            token = new CommonTokenStream(lex);
            input = new ANTLRFileStream(args[0]);
            lex = new MicroLexer(input);
            symbolTable = new ArrayList<SymbolTable>();
            symbolTable = micro.symbolTable(lex);
            
            parser = new MicroParser(token);
            parser.setErrorHandler(new MyErrorStrategy());
            tree = parser.program();
            
		}catch(Exception e){
            //e.printStackTrace();
            System.out.println("file not found");
            System.exit(0);
        }
        //System.out.println("Accepted");
        micro.printSymbolTable(symbolTable);
        
        
    }
    
    
    
    // create symboltables
    public ArrayList<SymbolTable> symbolTable(MicroLexer lexer) {
        ArrayList<SymbolTable> symbolTable = new ArrayList<SymbolTable>();
        Stack<SymbolTable> tempST = new Stack<SymbolTable>();
        Token temp = null;
        int blockCT = 1;
        boolean error = false;
        while ((temp = lexer.nextToken()).getText() != "<EOF>" && (!error)) {
             //System.out.println(temp.getType()+"    "+temp.getText());
            switch (isDecl(temp)) {
                    // global
                case 1:
                    SymbolTable st = new SymbolTable("GLOBAL");
                    symbolTable.add(st);
                    tempST.push(st);
                    break;
                    // variable declaration
                case 2:
                    Symbol newS = null;
                    String type = temp.getText();
                    while ((temp = lexer.nextToken()).getText() != "<EOF>"
                           && isDecl(temp) != 6) {
                        if (isDecl(temp) == 5) {
                            if (newS != null) {
                                tempST.peek().addSymbol(newS);
                            }
                            if (tempST.peek().hasSymbol(temp.getText())) {
                                error = true;
                                System.out.println("DECLARATION ERROR "
                                                   + temp.getText());
                                System.exit(0);
                                break;
                            } else {
                                newS = new Symbol(temp.getText(), type, "");
                            }
                        }
                        if (isDecl(temp) == 7) {
                            newS.setValue(temp.getText());
                        }
                    }
                    tempST.peek().addSymbol(newS);
                    break;
                    //function
                case 3:
                    while ((temp = lexer.nextToken()).getText() != "<EOF>"
                           && isDecl(temp) != 5)
                        ;
                    st = new SymbolTable(temp.getText());
                    symbolTable.add(st);
                    tempST.push(st);
                    break;
                    // pop
                case 4:
                    tempST.pop();
                    break;
                    // if/while/else
                case 8:
                    st = new SymbolTable("BLOCK " + blockCT);
                    symbolTable.add(st);
                    tempST.push(st);
                    blockCT++;
                    break;
                default:
                    break;
            }
        }
        
        return symbolTable;
    }
    
    public void printSymbolTable(ArrayList<SymbolTable> symbolTable) {
        for (int i = 0; i < symbolTable.size(); i++) {
            symbolTable.get(i).printTable();
        }
    }
    
    public int isDecl(Token token) {
        // PROGRAM
        if (token.getType() == 4) {
            return 1;
        }
        // Variable declaration INT/FLOAT/STRING
        else if (token.getType() == 30 | token.getType() == 24
                 | token.getType() == 14) {
            return 2;
        }
        // FUNCTION
        else if (token.getType() == 22) {
            return 3;
        }
        // END/ENDIF/ENDWHILE
        else if (token.getType() == 8 || token.getType() == 12
                 || token.getType() == 31) {
            return 4;
        }
        // id
        
        else if (token.getType() == 39) {
            return 5;
        }
        // ; )
        else if (token.getType() == 21 | token.getType() == 17) {
            return 6;
        }
         
        // value of variable(float/string/int literal)
        else if (token.getType() == 33 || token.getType() == 34
                 || token.getType() == 32) {
            return 7;
        }
        // if/while/else
        else if (token.getType() == 15 || token.getType() == 19 || token.getType() == 11) {
            return 8;
        }
        else {
            return 0;
        }
    }

}