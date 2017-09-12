import java.util.ArrayList;
import java.util.LinkedList;


public class Liveness {
    
    public LinkedList<IRNode> IR;
    SymbolTable globalVar;
    
    public Liveness(LinkedList<IRNode> IR, SymbolTable globalVar){
        this.IR = IR;
        this.globalVar=globalVar;
    }
    
    public void liveness() {
        ArrayList<String> temp=new ArrayList<String>();
        for (int i = IR.size()-1; i >= 0; i--) {
            //if RET, do recursive to update liveness
            if(IR.get(i).opCode==IRNode.IROp.RET){
                //	System.out.println("RET!!");
                /*	for(int j=0;j<globalVar.size();j++){
                 IR.get(i).out.add(globalVar.getSymbol(j).getName());
                 }*/
                inAndOut(IR.get(i), 0);
            }
            
        }
    }
    
    public void inAndOut(IRNode irNode, int dowhile){
        
        
        //irNode.printIRNode();
        for(int j=0;j<irNode.out.size();j++){
            if(!irNode.in.contains(irNode.out.get(j))){
                //				System.out.println(irNode.out.get(j));
                irNode.in.add(irNode.out.get(j));
            }
        }
        
        for(int j=0;j<irNode.gen.size();j++){
            if(!irNode.in.contains(irNode.gen.get(j))){
                irNode.in.add(irNode.gen.get(j));
            }
        }
        
        for(int j=0;j<irNode.kill.size();j++){
            if(irNode.in.contains(irNode.kill.get(j))){
                irNode.in.remove(irNode.kill.get(j));
            }
        }
        
        
        if(dowhile>=2){
            
            return;
        }
        for(int i=0;i<irNode.predecessor.size();i++){
            
            //if(irNode.out!=null){
            if(irNode.predecessor.get(i)!=null){
                for(int j=0;j<irNode.in.size();j++){
                    if(!irNode.predecessor.get(i).out.contains(irNode.in.get(j))){
                        irNode.predecessor.get(i).out.add(irNode.in.get(j));
                    }
                }
                
                //	System.out.println("DO WHILE?    "+IR.indexOf(irNode.predecessor.get(i))+"   "+IR.indexOf(irNode));
                if(IR.indexOf(irNode.predecessor.get(i))>IR.indexOf(irNode)){
                    inAndOut(irNode.predecessor.get(i), dowhile+1);
                }
                else{
                    inAndOut(irNode.predecessor.get(i), dowhile);
                    
                }
                
            }
            else{
                //				System.out.println("NO PREDECESSOR");
                //				irNode.printIRNode();
                //				System.out.println("NO PREDECESSOR------------");
            }
        }
        
    }
    
}
