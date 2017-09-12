import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

import org.antlr.v4.runtime.tree.ParseTree;

public class GenIR {
    LinkedList<IRNode> IR;
    
    int label;
    int regCount;
    int paraCount;
    int localCount;
    SymbolTable symbolTable;
    SymbolTableList stl;
    Map<String, String> m;
    IRNode predecessor;
    Map<String, String> global;
    //   public IRNode successor;
    
    public GenIR(ParseTree AST, SymbolTableList stl) {
        // System.out.println("in genIR:  " + AST.getChildCount());
        IR = new LinkedList<IRNode>();
        regCount = 1;
        paraCount = 1;
        localCount = 1;
        label = Micro.label;
        predecessor=null;
        //   successor = null;
        global = new HashMap<String, String>();;
        m = new HashMap<String, String>();
        this.stl = stl;
        this.symbolTable = stl.getSymbolTable().get(
                                                    stl.searchTable(AST.getChild(2).getText()));
        // mapping local variables
        
        for(int i=0;i<stl.getSymbolTable().get(0).size();i++){
            //			System.out.println(stl.getSymbolTable().get(0).getSymbol(i).getName()+"   "+stl.getSymbolTable().get(0).getSymbol(i).getType());
            m.put(stl.getSymbolTable().get(0).getSymbol(i).getName(), stl.getSymbolTable().get(0).getSymbol(i).getName());
            global.put(stl.getSymbolTable().get(0).getSymbol(i).getName(), stl.getSymbolTable().get(0).getSymbol(i).getType());
        }
        
        for (int i = 1; i <= symbolTable.countNumLocal(); i++) {
            m.put(symbolTable.getSymbol(i + symbolTable.countNumPara() - 1)
                  .getName(), "$L" + i);
            
        }
        // mapping parameters
        for (int i = 1; i <= symbolTable.countNumPara(); i++) {
            m.put(symbolTable.getSymbol(i - 1).getName(), "$P" + i);
        }
        // System.out.println(m);
        
        genIR(AST);
        
        if (!(IR.getLast().opCode == IRNode.IROp.RET)) {
            IRNode n = new IRNode();
            n.opCode = IRNode.IROp.RET;
            n.op1 = "";
            n.op2 = "";
            n.result = "";
            IR.add(n);
            addPreSuc(predecessor, n);
            predecessor=null;
        }
        Micro.label = label;
        
    }
    
    public void genIR(ParseTree AST) {
        IRNode n = new IRNode();
        if (AST.getChild(2).getText().equals("main")) {
            // map arguments and local variables
            n = new IRNode();
            n.opCode = IRNode.IROp.LABEL;
            n.op1 = "";
            n.op2 = "";
            n.result = "main";
            IR.add(n);
            addPreSuc(predecessor, n);
            n = new IRNode();
            n.opCode = IRNode.IROp.LINK;
            n.op1 = "";
            n.op2 = "";
            n.result = "";
            IR.add(n);
            addPreSuc(predecessor, n);
            // local variables mapping
            
            // System.out.println("*********   "
            // + AST.getChild(6).getChild(1).getText());
            AST = AST.getChild(6).getChild(1);
            for (int i = 0; i < AST.getChildCount(); i++){
                genStatement(AST.getChild(i));
            }
        } else {
            
            n = new IRNode();
            n.opCode = IRNode.IROp.LABEL;
            n.op1 = "";
            n.op2 = "";
            n.result = AST.getChild(2).getText();
            IR.add(n);
            addPreSuc(predecessor, n);
            n = new IRNode();
            n.opCode = IRNode.IROp.LINK;
            n.op1 = "";
            n.op2 = "";
            n.result = "";
            IR.add(n);
            addPreSuc(predecessor, n);
            
            AST = AST.getChild(7).getChild(1);
            for (int i = 0; i < AST.getChildCount(); i++){
                genStatement(AST.getChild(i));
            }
        }
    }
    
    public void genStatement(ParseTree AST) {
        // System.out.println("in genStatement:  " + AST.getText());
        // check argument
        
        if (AST.getText().startsWith("WRITE")) {
            ParseTree last = AST;
            while (AST.getChildCount() != 0) {
                last = AST;
                AST = AST.getChild(0);
            }
            AST = last;
            // System.out.println(AST.getChild(0).getText());
            if (AST.getChild(0).getText().equals("WRITE")) {
                IRNode n;
                // /System.out.println("-----------  "+AST.getChild(2).getText());
                for (int i = 0; i < AST.getChild(2).getChildCount(); i++) {
                    if (!AST.getChild(2).getChild(i).getText().equals(",")) {
                        n = new IRNode();
                        boolean isFloat = isFloatSymbol(AST.getChild(2)
                                                        .getChild(i).getText());
                        // System.out.println(AST.getChild(0).getText());
                        
                        n.opCode = (isFloat) ? (IRNode.IROp.WRITEF)
                        : (IRNode.IROp.WRITEI);
                        n.op1 = "";
                        n.op2 = "";
                        
                        if (m.containsKey(AST.getChild(2).getChild(i).getText()))
                            n.result = m.get(AST.getChild(2).getChild(i)
                                             .getText());
                        else {
                            n.opCode = IRNode.IROp.WRITES;
                            n.result = AST.getChild(2).getChild(i).getText();
                        }
                        
                        if(global.containsKey(n.result)){
                            if(global.get(n.result).equals("STRING")){
                                n.opCode = IRNode.IROp.WRITES;
                            }
                        }
                        
                        n.addGen(n.result);
                        IR.add(n);
                        addPreSuc(predecessor, n);
                    }
                }
            }
        } else if (AST.getText().startsWith("READ")) {
            ParseTree last = AST;
            while (AST.getChildCount() != 0) {
                last = AST;
                AST = AST.getChild(0);
            }
            AST = last;
            // System.out.println(AST.getChild(0).getText());
            if (AST.getChild(0).getText().equals("READ")) {
                IRNode n;
                // /System.out.println("-----------  "+AST.getChild(2).getText());
                for (int i = 0; i < AST.getChild(2).getChildCount(); i++) {
                    if (!AST.getChild(2).getChild(i).getText().equals(",")) {
                        n = new IRNode();
                        boolean isFloat = isFloatSymbol(AST.getChild(2)
                                                        .getChild(i).getText());
                        // System.out.println(AST.getChild(0).getText());
                        n.opCode = (isFloat) ? (IRNode.IROp.READF)
                        : (IRNode.IROp.READI);
                        n.op1 = "";
                        n.op2 = "";
                        if (m.containsKey(AST.getChild(2).getChild(i).getText()))
                            n.result = m.get(AST.getChild(2).getChild(i)
                                             .getText());
                        else
                            n.result = AST.getChild(2).getChild(i).getText();
                        n.addKill(n.result);
                        IR.add(n);
                        addPreSuc(predecessor, n);
                    }
                }
            }
        } else if (AST.getText().startsWith("IF")) {
            // System.out.println("In the IF statement" + AST.getText());
            AST = AST.getChild(0);
            int iflabel = label;
            genCheckStatement(AST.getChild(2), iflabel);
            IRNode temp = predecessor;
            iflabel += 1;
            int jumplabel = iflabel + 1;
            label += 2;
            
            IRNode endNode = new IRNode();
            endNode.opCode = IRNode.IROp.LABEL;
            endNode.op1 = "";
            endNode.op2 = "";
            endNode.result = "label" + jumplabel;
            for (int i = 0; i < AST.getChild(5).getChildCount(); i++) {
                genStatement(AST.getChild(5).getChild(i));
            }
            // jmp
            IRNode temp2 = predecessor;
            IRNode ifNode = new IRNode();
            ifNode.opCode = IRNode.IROp.LABEL;
            ifNode.op1 = "";
            ifNode.op2 = "";
            ifNode.result = "label" + iflabel;
            
            addPreSuc(temp, ifNode);
            IRNode n = new IRNode();
            n.opCode = IRNode.IROp.JUMP;
            n.op1 = "";
            n.op2 = "";
            n.result = "label" + jumplabel;
            IR.add(n);
            addPreSuc(temp2, n);
            addPreSuc(n, endNode);
            
            // label
            IR.add(ifNode);
            predecessor=ifNode;
            // check for ELSIF
            if (AST.getChild(6).getText().startsWith("ELSE")) {
                
                elseif(AST.getChild(6), jumplabel, endNode);
            }
            // check for ENDIF
            if (AST.getChild(7).getText().startsWith("ENDIF")) {
                
                IR.add(endNode);
                addPreSuc(predecessor, endNode);
                
            }
        } else if (AST.getText().startsWith("WHILE")) {
            
            // just create a label
            IRNode doNode = new IRNode();
            label++;
            doNode.opCode = IRNode.IROp.LABEL;
            doNode.op1 = "";
            doNode.op2 = "";
            doNode.result = "label" + label;
            int dolabel = label;
            IR.add(doNode);
            addPreSuc(predecessor, doNode);
            label++;
            // check the function
            for (int i = 0; i < AST.getChild(0).getChild(2).getChildCount(); i++) {
                genStatement(AST.getChild(0).getChild(2).getChild(i));
            }
            // generate the check statement
            genCheckStatement(AST.getChild(0).getChild(5), dolabel);
            IRNode temp = predecessor;
            // add jmp
            IRNode n = new IRNode();
            n.opCode = IRNode.IROp.JUMP;
            n.op1 = "";
            n.op2 = "";
            n.result = "label" + dolabel;
            IR.add(n);
            addPreSuc(predecessor, n);
            addPreSuc(predecessor, doNode);
            // add label
            n = new IRNode();
            dolabel++;
            n.opCode = IRNode.IROp.LABEL;
            n.op1 = "";
            n.op2 = "";
            n.result = "label" + dolabel;
            IR.add(n);
            addPreSuc(temp, n);
        } else if (AST.getText().contains(":=")) {
            ParseTree last = AST;
            while (AST.getChildCount() != 0) {
                last = AST;
                AST = AST.getChild(0);
            }
            AST = last.getParent();
            
            if (AST.getChildCount() == 3) {
                genAssignmentStatement(AST);
            }
        } else if (AST.getText().contains("RETURN")) {
            
            IRNode n;
            if (AST.getChild(0).getChild(0).getChild(1).getText()
                .matches("[0-9]+")) {
                n = new IRNode();
                n.opCode = IRNode.IROp.STOREI;
                n.op1 = AST.getChild(0).getChild(0).getChild(1).getText();
                n.op2 = "";
                String result = genTempReg();
                n.result = result;
                n.addGen(n.op1);
                n.addKill(n.result);
                IR.add(n);
                addPreSuc(predecessor, n);
                n = new IRNode();
                n.opCode = IRNode.IROp.STOREI;
                n.op1 = result;
                n.op2 = "";
                n.result = "$R";
                n.addGen(n.op1);
                n.addKill(n.result);
                IR.add(n);
                addPreSuc(predecessor, n);
            } else {
                
                boolean isFloat = isFloatSymbol(AST.getChild(0).getChild(0)
                                                .getChild(1).getChild(0).getText());
                n = new IRNode();
                n.opCode = (isFloat) ? (IRNode.IROp.STOREF)
                : (IRNode.IROp.STOREI);
                n.op1 = genExpression(AST.getChild(0).getChild(0).getChild(1),
                                      isFloat);
                n.op2 = "";
                n.result = "$R";
                n.addGen(n.op1);
                n.addKill(n.result);
                IR.add(n);
                addPreSuc(predecessor, n);
            }
            n = new IRNode();
            n.opCode = IRNode.IROp.RET;
            n.op1 = "";
            n.op2 = "";
            n.result = "";
            IR.add(n);
            addPreSuc(predecessor, n);
            predecessor=null;
        }
        
    }
    
    public void genCheckStatement(ParseTree AST, int currentlabel) {
        boolean tempboolean;
        if (AST.getText().equals("TRUE")) {
            // create 1 and 1 compare
            String temp1, temp2;
            IRNode n = new IRNode();
            n.opCode = IRNode.IROp.STOREI;
            n.op1 = "1";
            n.op2 = "";
            temp1 = genTempReg();
            n.result = temp1;
            n.addGen(n.op1);
            n.addKill(n.result);
            IR.add(n);
            addPreSuc(predecessor, n);
            n = new IRNode();
            n.opCode = IRNode.IROp.STOREI;
            n.op1 = "1";
            n.op2 = "";
            temp2 = genTempReg();
            n.result = temp2;
            n.addGen(n.op1);
            n.addKill(n.result);
            IR.add(n);
            addPreSuc(predecessor, n);
            n = new IRNode();
            n.opCode = IRNode.IROp.NE;
            n.op1 = temp1;
            n.op2 = temp2;
            currentlabel++;
            n.result = "label" + currentlabel;
            n.addGen(n.op1);
            n.addGen(n.op2);
            IR.add(n);
            addPreSuc(predecessor, n);
            return;
        }
        IRNode n2 = new IRNode();
        if (AST.getText().contains("!="))
            n2.opCode = IRNode.IROp.EQ;
        else if (AST.getText().contains(">="))
            n2.opCode = IRNode.IROp.LT;
        else if (AST.getText().contains(">"))
            n2.opCode = IRNode.IROp.LE;
        else if (AST.getText().contains("<="))
            n2.opCode = IRNode.IROp.GT;
        else if (AST.getText().contains("<"))
            n2.opCode = IRNode.IROp.GE;
        else if (AST.getText().contains("="))
            n2.opCode = IRNode.IROp.NE;
        else {
            
        }
        String temp = genTempReg();
        
        if (AST.getChild(0).getText().matches("[A-Za-z]*")) {
            if (m.containsKey(AST.getChild(0).getText()))
                n2.op1 = m.get(AST.getChild(0).getText());
            else
                n2.op1 = AST.getChild(0).getText();
            
            if (AST.getChild(2).getChild(0).getChild(0).getChild(0)
                .getChildCount() == 1) {
                
                IRNode store = new IRNode();
                
                if(isFloatSymbol(AST.getChild(2).getText())){
                    store.opCode = IRNode.IROp.STOREF;
                    tempboolean = true;
                }
                else {
                    store.opCode = IRNode.IROp.STOREI;
                    tempboolean = false;
                }
                if (m.containsKey(AST.getChild(2).getText()))
                    store.op1 = m.get(AST.getChild(2).getText());
                else
                    store.op1 = AST.getChild(2).getText();
                store.op2 = "";
                store.result = temp;
                store.addGen(store.op1);
                store.addKill(store.result);
                IR.add(store);
                addPreSuc(predecessor, store);
                n2.op2 = temp;
            }
            // there is a subroutine for statement
            else {
                IRNode store = new IRNode();
                boolean isFloat = false;
                if (AST.getChild(2).getText().matches("[0-9]+")) {
                    isFloat = false;
                    store.opCode = IRNode.IROp.STOREI;
                } else {
                    isFloat = true;
                    store.opCode = IRNode.IROp.STOREF;
                }
                tempboolean = isFloat;
                store.opCode = IRNode.IROp.STOREF;
                store.op1 = m.get(AST.getChild(2).getText());
                store.op2 = "";
                store.result = temp;
                n2.op2 = genExpression(AST.getChild(2).getChild(0).getChild(0)
                                       .getChild(0), isFloat);
            }
        } else {
            n2.op2 = AST.getChild(2).getText();
            if (AST.getChild(0).getChildCount() == 1) {
                IRNode store = new IRNode();
                if (AST.getChild(0).getText().matches("[0-9]+\\.[0-9]+")) {
                    store.opCode = IRNode.IROp.STOREI;
                    tempboolean = false;
                } else {
                    tempboolean = true;
                    store.opCode = IRNode.IROp.STOREF;
                }
                store.op1 = m.get(AST.getChild(0).getText());
                store.op2 = "";
                store.result = temp;
                store.addGen(store.op1);
                store.addKill(store.result);
                IR.add(store);
                addPreSuc(predecessor, store);
                n2.op1 = temp;
            } else {
                boolean isFloat = isFloatSymbol(AST.getChild(2).getChild(0)
                                                .getChild(0).getChild(0).getChild(0).getText());
                n2.op2 = genExpression(AST.getChild(2).getChild(0).getChild(0)
                                       .getChild(0), isFloat);
                tempboolean = isFloat;
            }
        }
        currentlabel++;
        if(m.containsKey(n2.op1) && tempboolean==false){
            tempboolean=isFloatSymbol(n2.op1);
        }
        else if(m.containsKey(n2.op2) && tempboolean==false){
            tempboolean=isFloatSymbol(n2.op2);
        }
        n2.isFloat = tempboolean;
        n2.result = "label" + currentlabel;
        n2.addGen(n2.op1);
        n2.addGen(n2.op2);
        IR.add(n2);
        addPreSuc(predecessor, n2);
    }
    
    public void genAssignmentStatement(ParseTree AST) {
        IRNode n = new IRNode();
        boolean isFloat = isFloatSymbol(AST.getChild(0).getText());
        n.opCode = (isFloat) ? (IRNode.IROp.STOREF) : (IRNode.IROp.STOREI);
        n.result = m.get(AST.getChild(0).getText()); // where to store
        
        AST = AST.getChild(2);
        
        n.op1 = genExpression(AST, isFloat);
        
        n.op2 = "";
        
        n.addGen(n.op1);
        n.addKill(n.result);
        IR.add(n);
        addPreSuc(predecessor, n);
    }
    
    public void elseif(ParseTree AST, int jumplabel, IRNode endNode) {
        label++;
        
        int elselabel = label;
        
        IRNode elseNode = new IRNode();
        elseNode.opCode = IRNode.IROp.LABEL;
        elseNode.op1 = "";
        elseNode.op2 = "";
        elseNode.result = "label" + elselabel;
        
        genCheckStatement(AST.getChild(2), elselabel - 1);
        IRNode temp = predecessor;
        addPreSuc(predecessor, elseNode);
        predecessor=temp;
        
        for (int i = 0; i < AST.getChild(5).getChildCount(); i++) {
            genStatement(AST.getChild(5).getChild(i));
        }
        
        // label++;
        IRNode n = new IRNode();
        n.opCode = IRNode.IROp.JUMP;
        n.op1 = "";
        n.op2 = "";
        n.result = "label" + jumplabel;
        IR.add(n);
        addPreSuc(predecessor, n);
        addPreSuc(n, endNode);
        predecessor = elseNode;
        // label
        IR.add(elseNode);
        
        if (AST.getChildCount() > 6
            && AST.getChild(6).getText().startsWith("ELSE")) {
            elseif(AST.getChild(6), jumplabel, endNode);
        }
    }
    
    public boolean isFloatSymbol(String name) {
        
        // check global symbol table
        for (int i = 0; i < stl.getSymbolTable().get(0).size(); i++) {
            Symbol te = stl.getSymbolTable().get(0).getSymbol(i);
            if (te.getName().equals(name)) {
                // System.out.println(te.getName() + "  " + te.getType());
                if (te.getType().equals("FLOAT"))
                    return true;
                else
                    return false;
            }
        }
        // check local symbol table index is "order"
        for (int i = 0; i < symbolTable.size(); i++) {
            Symbol te = symbolTable.getSymbol(i);
            if (te.getName().equals(name)) {
                // System.out.println(te.getName() + "  " + te.getType());
                if (te.getType().equals("FLOAT"))
                    return true;
                else
                    return false;
            }
        }
        
        //System.out.println("symbol can not be found." + name);
        return false;
    }
    
    public String genExpression(ParseTree AST, boolean isFloat) {
        int table;
        if ((table = checkFunction(AST.getChild(0))) > 0) {
            
            IRNode n;
            LinkedList<IRNode> tempIR = new LinkedList<IRNode>();
            
            for (int i = 0; i < AST.getChild(0).getChild(2).getChildCount(); i += 2) {
                
                n = new IRNode();
                n.opCode = IRNode.IROp.PUSH;
                n.result = genExpression(AST.getChild(0).getChild(2)
                                         .getChild(i), isFloat); // where to store
                
                n.op1 = "";
                n.op2 = "";
                n.addGen(n.result);
                tempIR.add(n);
                
            }
            n = new IRNode();
            n.opCode = IRNode.IROp.PUSH;
            n.result = ""; // where to store
            n.op1 = "";
            n.op2 = "";
            IR.add(n);
            addPreSuc(predecessor, n);
            for (int i = 0; i < tempIR.size(); i++){
                IR.add(tempIR.get(i));
                addPreSuc(predecessor, tempIR.get(i));
            }
            n = new IRNode();
            n.opCode = IRNode.IROp.JSR;
            n.result = AST.getChild(0).getChild(0).getText(); // where to store
            n.op1 = "";
            n.op2 = "";
            /*for(int i=0;i<stl.getSymbolTable().get(0).size();i++){
             n.addGen(stl.getSymbolTable().get(0).getSymbol(i).getName());
             }*/
            IR.add(n);
            addPreSuc(predecessor, n);
            for (int i = 0; i < AST.getChild(0).getChild(2).getChildCount(); i += 2) {
                n = new IRNode();
                n.opCode = IRNode.IROp.POP;
                n.result = "";
                n.op1 = "";
                n.op2 = "";
                IR.add(n);
                addPreSuc(predecessor, n);
            }
            n = new IRNode();
            n.opCode = IRNode.IROp.POP;
            String result = genTempReg();
            n.result = result;
            n.op1 = "";
            n.op2 = "";
            n.addKill(n.result);
            IR.add(n);
            addPreSuc(predecessor, n);
            return result;
        } else if (AST.getChildCount() == 1
                   && AST.getChild(0).getChildCount() == 0) {
            if (AST.getText().matches("[A-Za-z]*")) {
                return m.get(AST.getText());
            } else {
                IRNode n = new IRNode();
                n.opCode = (isFloat) ? (IRNode.IROp.STOREF)
                : (IRNode.IROp.STOREI);
                
                String temp = genTempReg();
                n.result = temp; // where to store
                if (m.containsKey(AST.getText()))
                    n.op1 = m.get(AST.getText());
                else
                    n.op1 = AST.getText();
                n.op2 = "";
                
                n.addGen(n.op1);
                n.addKill(n.result);
                IR.add(n);
                addPreSuc(predecessor, n);
                return temp;
            }
        } else if (AST.getChildCount() == 1) {
            return genExpression(AST.getChild(0), isFloat);
        } else if (AST.getChildCount() > 3) {
            String temp = "";
            
            String tempOp1 = genExpression(AST.getChild(0), isFloat);
            for (int i = 0; i < AST.getChildCount() - 2; i += 2) {
                IRNode n = new IRNode();
                
                n.op1 = tempOp1;
                n.op2 = genExpression(AST.getChild(i + 2), isFloat);
                n.result = genTempReg();
                if(m.containsKey(n.op1) && isFloat==false){
                    isFloat=isFloatSymbol(n.op1);
                }
                else if(m.containsKey(n.op2) && isFloat==false){
                    isFloat=isFloatSymbol(n.op2);
                }
                if (AST.getChild(i + 1).getText().equals("+"))
                    n.opCode = (isFloat) ? (IRNode.IROp.ADDF)
                    : (IRNode.IROp.ADDI);
                else if (AST.getChild(i + 1).getText().equals("-"))
                    n.opCode = (isFloat) ? (IRNode.IROp.SUBF)
                    : (IRNode.IROp.SUBI);
                else if (AST.getChild(i + 1).getText().equals("*"))
                    n.opCode = (isFloat) ? (IRNode.IROp.MULTF)
                    : (IRNode.IROp.MULTI);
                else if (AST.getChild(i + 1).getText().equals("/"))
                    n.opCode = (isFloat) ? (IRNode.IROp.DIVF)
                    : (IRNode.IROp.DIVI);
                //				System.out.println("----------------m"+n.op1);
                temp = n.result;
                n.addGen(n.op1);
                n.addGen(n.op2);
                n.addKill(n.result);
                IR.add(n);
                addPreSuc(predecessor, n);
                tempOp1 = n.result;
                
            }
            return temp;
            
        } else if (AST.getChild(0).getText().equals("(")) {
            return genExpression(AST.getChild(1), isFloat);
            
        } else if (AST.getChild(1).getText().equals("+")) {
            IRNode n = new IRNode();
            
            n.op1 = genExpression(AST.getChild(0), isFloat);
            n.op2 = genExpression(AST.getChild(2), isFloat);
            if(m.containsKey(n.op1) && isFloat==false){
                isFloat=isFloatSymbol(n.op1);
            }
            else if(m.containsKey(n.op2) && isFloat==false){
                isFloat=isFloatSymbol(n.op2);
            }
            
            n.opCode = (isFloat) ? (IRNode.IROp.ADDF) : (IRNode.IROp.ADDI);
            n.result = genTempReg();
            n.addGen(n.op1);
            n.addGen(n.op2);
            n.addKill(n.result);
            IR.add(n);
            addPreSuc(predecessor, n);
            return n.result;
        } else if (AST.getChild(1).getText().equals("*")) {
            IRNode n = new IRNode();
            
            n.op1 = genExpression(AST.getChild(0), isFloat);
            n.op2 = genExpression(AST.getChild(2), isFloat);
            if(m.containsKey(n.op1) && isFloat==false){
                isFloat=isFloatSymbol(n.op1);
            }
            else if(m.containsKey(n.op2) && isFloat==false){
                isFloat=isFloatSymbol(n.op2);
            }
            n.opCode = (isFloat) ? (IRNode.IROp.MULTF) : (IRNode.IROp.MULTI);
            n.result = genTempReg();
            n.addGen(n.op1);
            n.addGen(n.op2);
            n.addKill(n.result);
            IR.add(n);
            addPreSuc(predecessor, n);
            return n.result;
        } else if (AST.getChild(1).getText().equals("-")) {
            IRNode n = new IRNode();
            
            n.op1 = genExpression(AST.getChild(0), isFloat);
            n.op2 = genExpression(AST.getChild(2), isFloat);
            if(m.containsKey(n.op1) && isFloat==false){
                isFloat=isFloatSymbol(n.op1);
            }
            else if(m.containsKey(n.op2) && isFloat==false){
                isFloat=isFloatSymbol(n.op2);
            }
            n.opCode = (isFloat) ? (IRNode.IROp.SUBF) : (IRNode.IROp.SUBI);
            n.result = genTempReg();
            n.addGen(n.op1);
            n.addGen(n.op2);
            n.addKill(n.result);
            IR.add(n);
            addPreSuc(predecessor, n);
            return n.result;
        } else if (AST.getChild(1).getText().equals("/")) {
            
            IRNode n = new IRNode();
            
            n.op1 = genExpression(AST.getChild(0), isFloat);
            n.op2 = genExpression(AST.getChild(2), isFloat);
            if(m.containsKey(n.op1) && isFloat==false){
                isFloat=isFloatSymbol(n.op1);
            }
            else if(m.containsKey(n.op2) && isFloat==false){
                isFloat=isFloatSymbol(n.op2);
            }
            n.opCode = (isFloat) ? (IRNode.IROp.DIVF) : (IRNode.IROp.DIVI);
            n.result = genTempReg();
            n.addGen(n.op1);
            n.addGen(n.op2);
            n.addKill(n.result);
            IR.add(n);
            addPreSuc(predecessor, n);
            return n.result;
        } else {
            // literal or symbol. just return
            if (m.containsKey(AST.getText()))
                return m.get(AST.getText());
            else
                return AST.getText();
        }
        
    }
    
    private int checkFunction(ParseTree child) {
        int table = -1;
        if (child.getChildCount() > 1) {
            table = stl.searchTable(child.getChild(0).getText());
        }
        return table;
    }
    
    public String genTempReg() {
        return "$T" + (regCount++);
    }
    
    public LinkedList<IRNode> getIR() {
        return IR;
    }
    
    public void printtree(ParseTree tree) {
        for (int i = 0; i < tree.getChildCount(); i++) {
            
            System.out.println(tree.getChild(i).getText());
            
        }
    }
    
    public void addPreSuc(IRNode predecessor, IRNode successor){
        if(predecessor!=null){
            predecessor.successor.add(successor);
            successor.predecessor.add(predecessor);
        }
        
        
        this.predecessor=successor;
        
    }
}
