import java.util.*;


public class IRToTiny {
	
	
	LinkedList<TinyNode> varList;
	LinkedList<TinyNode> strList;
	LinkedList<TinyNode> codeList;
	
	LinkedList<Integer> tVar;
	int rVar;
	
	public IRToTiny(){
		varList = new LinkedList<TinyNode>();
		strList = new LinkedList<TinyNode>();
		codeList = new LinkedList<TinyNode>();
		tVar = new LinkedList<Integer>();
		tVar.add(0);
		rVar=-1;
	}
	
	public void irToTiny(LinkedList<IRNode> irNodeList, ArrayList<SymbolTable> symbolTable){
		//LinkedList<TinyNode> tiny = new LinkedList<TinyNode>();
		
		//add var && str list
		for(int i=0;i<symbolTable.size();i++){
			for(int j=0;j<symbolTable.get(i).symbolTable.size();j++){
				if(symbolTable.get(i).symbolTable.get(j).getType().equals("STRING")){
					strList.add(new TinyNode(TinyNode.TinyOp.str, symbolTable.get(i).symbolTable.get(j).getName(),symbolTable.get(i).symbolTable.get(j).getValue()));
				}
				else{
					varList.add(new TinyNode(TinyNode.TinyOp.var, symbolTable.get(i).symbolTable.get(j).getName(),""));
				}
			}
		}
		
		for(int i=0;i<irNodeList.size();i++){
			addTinyCode(irNodeList.get(i));
		}
		codeList.add(new TinyNode(TinyNode.TinyOp.sys_halt));
		
		printTinyList();
	}
	
	
	public String transArg(String arg){
		String tinyArg;
		
		if(arg==null){
//			System.out.print(rVar+"    "+"        "+tVar.getLast()+"     ");
			int inttemp=tVar.getLast()+1;
			tinyArg="r"+inttemp;
			rVar++;
//			System.out.println(arg+"    "+tinyArg+"       "+rVar);
		}
		else if(arg.startsWith("$T")){
			int num = Integer.parseInt(arg.substring(2));
			if(tVar.size()>num){
				tinyArg="r"+tVar.get(num);
			}
			else{
				tVar.add(num+rVar);
				int inttemp=num+rVar;
				tinyArg="r"+inttemp;
			}
		}
		else{
			tinyArg=arg;
		}
		
		return tinyArg;
	}
	
	
	public void addTinyCode(IRNode irnode){
		
		switch(irnode.opCode){
			//ADDI OP1 OP2 RESULT (Integer Add)
			case ADDI: 
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), transArg(irnode.result)));
				codeList.add(new TinyNode(TinyNode.TinyOp.addi, transArg(irnode.op2), transArg(irnode.result)));
				break;
			//ADDF OP1 OP2 RESULT (Floating Point Add)
			case ADDF:
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), transArg(irnode.result)));
				codeList.add(new TinyNode(TinyNode.TinyOp.addr, transArg(irnode.op2), transArg(irnode.result)));
				break;
			//SUBI OP1 OP2 RESULT (Integer Subtract)
			case SUBI:
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), transArg(irnode.result)));
				codeList.add(new TinyNode(TinyNode.TinyOp.subi, transArg(irnode.op2), transArg(irnode.result)));
				break;
			//SUBF OP1 OP2 RESULT (Floating Point Subtract: RESULT = OP1/OP2)
			case SUBF:
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), transArg(irnode.result)));
				codeList.add(new TinyNode(TinyNode.TinyOp.subr, transArg(irnode.op2), transArg(irnode.result)));
				break;
			//MULTI OP1 OP2 RESULT (Integer Multiplication)
			case MULTI:
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), transArg(irnode.result)));
				codeList.add(new TinyNode(TinyNode.TinyOp.muli, transArg(irnode.op2), transArg(irnode.result)));
				break;
			//MULTF OP1 OP2 RESULT (Floating Point Multiplication)
			case MULTF:
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), transArg(irnode.result)));
				codeList.add(new TinyNode(TinyNode.TinyOp.mulr, transArg(irnode.op2), transArg(irnode.result)));
				break;
			//DIVI OP1 OP2 RESULT (Integer Division)
			case DIVI:
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), transArg(irnode.result)));
				codeList.add(new TinyNode(TinyNode.TinyOp.divi, transArg(irnode.op2), transArg(irnode.result)));
				break;
			//DIVF OP1 OP2 RESULT (Floating Point Division: RESULT = OP1/OP2)
			case DIVF:
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), transArg(irnode.result)));
				codeList.add(new TinyNode(TinyNode.TinyOp.divr, transArg(irnode.op2), transArg(irnode.result)));
				break;
			//STOREI OP1 RESULT (Integer Store, Store OP1 to RESULT)
			case STOREI:
			//STOREF OP1 RESULT (FP Store)
			case STOREF:
				if((!irnode.op1.contains("T")) && (!irnode.result.contains("T"))){
					String temp=transArg(null);
					codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), temp));
					codeList.add(new TinyNode(TinyNode.TinyOp.move, temp, transArg(irnode.result)));
				}
				else{
					codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(irnode.op1), transArg(irnode.result)));
				}
				break;
			//GT OP1 OP2 LABEL (If OP1 > OP2 Goto LABEL)
			case GT:
				compare(irnode.op1, irnode.op2, TinyNode.TinyOp.jgt);
				codeList.add(new TinyNode(TinyNode.TinyOp.jgt, transArg(irnode.result)));
				break;
			//GE OP1 OP2 LABEL (If OP1 >= OP2 Goto LABEL)
			case GE:
				compare(irnode.op1, irnode.op2, TinyNode.TinyOp.jge);
				codeList.add(new TinyNode(TinyNode.TinyOp.jge, transArg(irnode.result)));
				break;
			//LT OP1 OP2 LABEL (If OP1 < OP2 Goto LABEL)
			case LT:
				compare(irnode.op1, irnode.op2, TinyNode.TinyOp.jlt);
				codeList.add(new TinyNode(TinyNode.TinyOp.jlt, transArg(irnode.result)));
				break;
			//LE OP1 OP2 LABEL (If OP1 <= OP2 Goto LABEL)
			case LE:
				compare(irnode.op1, irnode.op2, TinyNode.TinyOp.jle);
				codeList.add(new TinyNode(TinyNode.TinyOp.jle, transArg(irnode.result)));
				break;
			//NE OP1 OP2 LABEL (If OP1 != OP2 Goto LABEL)
			case NE:
				compare(irnode.op1, irnode.op2, TinyNode.TinyOp.jne);
				codeList.add(new TinyNode(TinyNode.TinyOp.jne, transArg(irnode.result)));
				break;
			//EQ OP1 OP2 LABEL (If OP1 = OP2 Goto LABEL)
			case EQ:
				compare(irnode.op1, irnode.op2, TinyNode.TinyOp.jeq);
				codeList.add(new TinyNode(TinyNode.TinyOp.jeq, transArg(irnode.result)));
				break;
			//JUMP LABEL (Direct Jump)
			case JUMP:
			//LABEL STRING (set a STRING Label)
				codeList.add(new TinyNode(TinyNode.TinyOp.jmp, transArg(irnode.result)));
				break;
			case LABEL:
				codeList.add(new TinyNode(TinyNode.TinyOp.label, transArg(irnode.result)));
				break;
			//READI RESULT
			case READI:
				codeList.add(new TinyNode(TinyNode.TinyOp.sys_readi, transArg(irnode.result)));
				break;
			//READF RESULT
			case READF:
				codeList.add(new TinyNode(TinyNode.TinyOp.sys_readr, transArg(irnode.result)));
				break;
			//WRITEI RESULT
			case WRITEI:
				codeList.add(new TinyNode(TinyNode.TinyOp.sys_writei, transArg(irnode.result)));
				break;
			//WRITEF RESULT
			case WRITEF:
				codeList.add(new TinyNode(TinyNode.TinyOp.sys_writer, transArg(irnode.result)));
				break;
		}
	}

	public void printTinyList(){
		System.out.println(";tiny code");
		for(int i=0;i<varList.size();i++){
			System.out.println(varList.get(i).getOp()+" "+varList.get(i).getArg1());
		}
		for(int i=0;i<strList.size();i++){
			System.out.println(strList.get(i).getOp()+" "+strList.get(i).getArg1()+" "+strList.get(i).getArg2());
		}
		
		for(int i=0;i<codeList.size();i++){
			System.out.print(codeList.get(i).getOp());
			if(codeList.get(i).getArg1()!=null){
				System.out.print(" "+codeList.get(i).getArg1());
			}
			if(codeList.get(i).getArg2()!=null){
				System.out.print(" "+codeList.get(i).getArg2());
			}
			System.out.println();
		}
	}
	
	public void compare(String op1, String op2, TinyNode.TinyOp cmp){
		if(cmp == TinyNode.TinyOp.jge || cmp == TinyNode.TinyOp.jgt){
			if((!op1.contains("T")) && (!op2.contains("T"))){
				String temp=transArg(null);
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(op2), temp));
				codeList.add(new TinyNode(TinyNode.TinyOp.cmpr, transArg(op1), temp));
			}
			else{
				codeList.add(new TinyNode(TinyNode.TinyOp.cmpr, transArg(op1), transArg(op2)));
			}
		}
		else{
			if((!op1.contains("T")) && (!op2.contains("T"))){
				String temp=transArg(null);
				codeList.add(new TinyNode(TinyNode.TinyOp.move, transArg(op1), temp));
				codeList.add(new TinyNode(TinyNode.TinyOp.cmpr, transArg(op2), temp));
			}
			else{
				codeList.add(new TinyNode(TinyNode.TinyOp.cmpr, transArg(op1), transArg(op2)));
			}
		}
	}
}