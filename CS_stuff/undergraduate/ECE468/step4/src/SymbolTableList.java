import java.util.ArrayList;
import java.util.Stack;

import org.antlr.v4.runtime.Token;


public class SymbolTableList {
    
    ArrayList<SymbolTable> symbolTable;
    boolean error;
    String errorMsg;
    boolean isPara;
    
    public SymbolTableList(MicroLexer lexer){
        symbolTable = new ArrayList<SymbolTable>();
        Stack<SymbolTable> tempST = new Stack<SymbolTable>();
        Token temp = null;
        int blockCT = 1;
        error = false;
        isPara=false;
        while ((temp = lexer.nextToken()).getText() != "<EOF>" && (!error)) {
            //                System.out.println(temp.getType()+"    "+temp.getText());
            switch (isDecl(temp)) {
                    //global
                case 1: SymbolTable st = new SymbolTable("GLOBAL");
                    symbolTable.add(st);
                    tempST.push(st);
                    break;
                    //variable declaration
                case 2: Symbol newS = null;
                    String type = temp.getText();
                    //	                		System.out.println(temp.getType()+"    "+temp.getText());
                    while ((temp = lexer.nextToken()).getText() != "<EOF>" && (isDecl(temp)!=6 && isDecl(temp)!=10)){
                        //	                			System.out.println(temp.getType()+"    "+temp.getText());
                        if(isDecl(temp)==5){
                            if(newS!=null){
                                tempST.peek().addSymbol(newS);
                            }
                            if(tempST.peek().hasSymbol(temp.getText())){
                                error=true;
                                errorMsg="DECLARATION ERROR "+temp.getText();
                                break;
                            }
                            else{
                                newS = new Symbol(temp.getText(), type, "", isPara);
                            }
                        }
                        if(isDecl(temp)==7){
                            newS.setValue(temp.getText());
                        }
                    }
                    //System.out.println(temp.getType()+"aaaaa"+temp.getText());
                    if(isDecl(temp)==10 && isPara){
                        isPara=false;
                    }
                    tempST.peek().addSymbol(newS);
                    break;
                    //new function
                case 3: while ((temp = lexer.nextToken()).getText() != "<EOF>" && isDecl(temp)!=5);
                    st = new SymbolTable(temp.getText());
                    symbolTable.add(st);
                    tempST.push(st);
                    isPara=true;
                    break;
                    //pop
                case 4: tempST.pop();
                    break;
                    //if/while
                case 8: st = new SymbolTable("BLOCK "+blockCT);
                    symbolTable.add(st);
                    tempST.push(st);
                    blockCT++;
                    break;
                    //else
                case 9: tempST.pop();
                    st = new SymbolTable("BLOCK "+blockCT);
                    symbolTable.add(st);
                    tempST.push(st);
                    blockCT++;
                    break;
                case 10:
                    if(isPara){
                        //System.out.println("here");
                        isPara=false;
                    }
                    break;
                default: break;
            }
        }
        //        if(!error){
        //        	printSymbolTable(symbolTable);
        //        }
    }
    
    public void printSymbolTable(){
        if(!error){
            for(int i=0;i<symbolTable.size();i++){
                System.out.println("Table"+i);
                symbolTable.get(i).printTable();
            }
        }
        else{
            System.out.println(errorMsg);
        }
    }
    
    public int searchTable(String name){
        int i;
        for(i=0;i<symbolTable.size();i++){
            if(symbolTable.get(i).name.equals(name)){
                return i;
            }
        }
        return -1;
    }
    
    public ArrayList<SymbolTable> getSymbolTable(){
        return symbolTable;
    }
    
    public int isDecl(Token token){
        //PROGRAM
        if(token.getType()==4){
            return 1;
        }
        //Variable declaration INT/FLOAT/STRING
        else if (token.getType() == 30 | token.getType() == 24 | token.getType() == 14 ){
            return 2;
        }
        //FUNCTION
        else if (token.getType() == 22){
            return 3;
        }
        //END/ENDIF/ENDWHILE
        else if (token.getType() == 8 || token.getType() == 12 || token.getType() == 31){
            return 4;
        }
        //id
        else if (token.getType() == 39){
            return 5;
        }
        //;/)
        else if(token.getType() == 21){
            return 6;
        }
        //value of variable(float/string/int literal)
        else if(token.getType() == 33 || token.getType() == 34 || token.getType() ==32){
            return 7;
        }
        //if/while
        else if(token.getType() == 15 || token.getType() == 19){
            return 8;
        }
        //else
        else if(token.getType() == 11){
            return 9;
        }
        //)
        else if(token.getType() == 17)
            return 10;
        //else
        else{
            return 0;
        }
    }
}
