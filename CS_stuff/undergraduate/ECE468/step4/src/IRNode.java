import java.util.ArrayList;

public class IRNode {
    
    public enum IROp {
        ADDI,
        ADDF,
        SUBI,
        SUBF,
        MULTI,
        MULTF,
        DIVI,
        DIVF,
        STOREI,
        STOREF,
        GT,
        GE,
        LT,
        LE,
        NE,
        EQ,
        JUMP,
        LABEL,
        READI,
        READF,
        WRITEI,
        WRITEF,
        WRITES,
        JSR,
        PUSH,
        POP,
        RET,
        LINK
    }
    
    public IROp opCode;
    public String op1;
    public String op2;
    public String result;
    public boolean isFloat;
    public ArrayList<IRNode> predecessor;
    public ArrayList<IRNode> successor;
    public ArrayList<String> gen;
    public ArrayList<String> kill;
    public ArrayList<String> in;
    public ArrayList<String> out;
    
    public IRNode(){
        opCode=null;
        op1=null;
        op2=null;
        result=null;
        isFloat=false;
        predecessor=new ArrayList<IRNode>();
        successor=new ArrayList<IRNode>();
        gen=new ArrayList<String>();
        kill=new ArrayList<String>();
        in=new ArrayList<String>();
        out=new ArrayList<String>();
    }
    
    public void printIRNode(){
        System.out.println("; " + opCode + " "+ op1 + " " + op2	+ " " + result);
        for(int i=0;i<predecessor.size();i++){
            if(predecessor.get(i)!=null)
                System.out.println(";      predecessor   "+predecessor.get(i).opCode.toString()+" "+predecessor.get(i).op1+" "+predecessor.get(i).op2+" "+predecessor.get(i).result);
        }
        for(int i=0;i<successor.size();i++){
            if(successor.get(i)!=null)
                System.out.println(";      successor   "+successor.get(i).opCode.toString()+" "+successor.get(i).op1+" "+successor.get(i).op2+" "+successor.get(i).result);
        }
        System.out.print(";      gen");
        for(int i=0;i<gen.size();i++){
            if(gen.get(i)!=null)
                System.out.print("     "+gen.get(i));
        }
        System.out.println();
        System.out.print(";      kill");
        for(int i=0;i<kill.size();i++){
            if(kill.get(i)!=null)
                System.out.print("     "+kill.get(i));
        }
        System.out.println();
        
        System.out.print(";      in");
        for(int i=0;i<in.size();i++){
            if(in.get(i)!=null)
                System.out.print("     "+in.get(i));
        }
        System.out.println();
        System.out.print(";      out");
        for(int i=0;i<out.size();i++){
            if(out.get(i)!=null)
                System.out.print("     "+out.get(i));
        }
        System.out.println();
    }
    
    public void addGen(String str){
        if(str==null || str.matches("[0-9]+") || str.matches("[+-]?[0-9]+\\.?[0-9]+")){
            return;
        }
        
        this.gen.add(str);
    }
    
    public void addKill(String str){
        if(str==null || str.matches("[0-9]+") || str.matches("[+-]?[0-9]+\\.?[0-9]+")){
            return;
        }
        
        this.kill.add(str);
    }
}