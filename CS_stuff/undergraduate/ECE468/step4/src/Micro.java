import java.util.*;
import java.io.*;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.lang.String;

public class Micro{

    static LinkedList<LinkedList<IRNode>> IR;
    static ArrayList<SymbolTable> symbolTable;
    static public int label;
    
    public Micro(){
    }
    public class Tree{
        String value;
        Tree left, right;
    }
    
	public static void main(String[] args) throws IOException{
        
        IR = new LinkedList<LinkedList<IRNode>>();
        //Micro micro = new Micro();
        MicroLexer lex=null;
        MicroParser parser=null;
        CharStream input=null;
        CommonTokenStream token=null;
        ParseTree tree = null;
        SymbolTableList stl = null;
        try{
            input = new ANTLRFileStream(args[0]);
            lex = new MicroLexer(input);
            stl = new SymbolTableList(lex);
            symbolTable = stl.getSymbolTable();
            
            input = new ANTLRFileStream(args[0]);
            lex = new MicroLexer(input);
            token = new CommonTokenStream(lex);
            parser = new MicroParser(token);
            parser.setErrorHandler(new MyErrorStrategy());
            parser.setBuildParseTree(true);
            tree = parser.program();
            
		}catch(Exception e){
            //e.printStackTrace();
            System.out.println("file not found");
            System.exit(0);
        }
        //System.out.println("Accepted");
        //micro.printSymbolTable(symbolTable);
        
        GenIR genir;
        
        tree = tree.getChild(3).getChild(1);
        
        for (int i = 0; i < tree.getChildCount(); i++) {
            // System.out.println("~~~~~~~~~~   " + tree.getChild(i).getText());
            genir = new GenIR(tree.getChild(i), stl);
            IR.add(genir.getIR());
        }
        
        liveness();
        
        // printtree(tree);
        //	printIRNode();
        
        IRToTiny ir2tiny = new IRToTiny();
        ir2tiny.irToTiny(IR, stl);
        
    }
    
    public static void printIRNode() {
        
        System.out.println(";IR code");
        for (int j = 0; j < IR.size(); j++) {
            for (int i = 0; i < IR.get(j).size(); i++) {
                
                IR.get(j).get(i).printIRNode();
            }
            System.out.println();
            System.out.println();
        }
    }
    
    public static void liveness(){
        for(int i=0;i<IR.size();i++){
            Liveness live = new Liveness(IR.get(i), symbolTable.get(0));
            live.liveness();
        }
    }

}