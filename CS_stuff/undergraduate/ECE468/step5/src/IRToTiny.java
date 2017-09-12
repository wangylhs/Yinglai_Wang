import java.util.*;


public class IRToTiny {
	
	
	LinkedList<TinyNode> varList;
	LinkedList<TinyNode> strList;
	LinkedList<TinyNode> codeList;
	
	LinkedList<Integer> tVar;
	int rVar;
	SymbolTableList stl;
	int curLocalVar;
	int curParaVar;
	int NUMREG =4;
	LinkedList<String> globalVar;
	Register[] reg;
	
	public IRToTiny(){
		varList = new LinkedList<TinyNode>();
		strList = new LinkedList<TinyNode>();
		codeList = new LinkedList<TinyNode>();
		tVar = new LinkedList<Integer>();
		tVar.add(0);
		rVar=-1;
		stl=null;
		reg = new Register[4];
		for(int i=0;i<NUMREG;i++){
			reg[i]=new Register();
			reg[i].setIndex(i);
		}
		globalVar = new LinkedList<String> ();
		
	}
	
	public void irToTiny(LinkedList<LinkedList<IRNode>> irnode, SymbolTableList symbolTable){
		//LinkedList<TinyNode> tiny = new LinkedList<TinyNode>();
		stl=symbolTable;
		//add var && str list
		for(int j=0;j<symbolTable.getSymbolTable().get(0).symbolTable.size();j++){
			if(symbolTable.getSymbolTable().get(0).symbolTable.get(j).getType().equals("STRING")){
				strList.add(new TinyNode(TinyNode.TinyOp.str, symbolTable.getSymbolTable().get(0).symbolTable.get(j).getName(),symbolTable.getSymbolTable().get(0).symbolTable.get(j).getValue()));
			}
			else{
				varList.add(new TinyNode(TinyNode.TinyOp.var, symbolTable.getSymbolTable().get(0).symbolTable.get(j).getName(),""));
			}
			globalVar.add(symbolTable.getSymbolTable().get(0).symbolTable.get(j).getName());
		}

		codeList.add(new TinyNode(TinyNode.TinyOp.push));
		codeList.add(new TinyNode(TinyNode.TinyOp.push, "r0"));
		codeList.add(new TinyNode(TinyNode.TinyOp.push, "r1"));
		codeList.add(new TinyNode(TinyNode.TinyOp.push, "r2"));
		codeList.add(new TinyNode(TinyNode.TinyOp.push, "r3"));
		codeList.add(new TinyNode(TinyNode.TinyOp.jsr, "main"));
		codeList.add(new TinyNode(TinyNode.TinyOp.sys_halt));
		for(int i=0;i<irnode.size();i++){
			for(int j=0;j<irnode.get(i).size();j++){
				addTinyCode(irnode.get(i).get(j));
//				System.out.println(irnode.get(i).get(j).opCode.toString());
			}
			rVar=-1;
			tVar.clear();
			tVar.add(0);
		}
		codeList.add(new TinyNode(TinyNode.TinyOp.end));
		
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
			int num = -(curLocalVar+Integer.parseInt(arg.substring(2)));
			tinyArg="$"+num;
		}
		else if(arg.startsWith("$P")){
			int num = Integer.parseInt(arg.substring(2));
			num=6+curParaVar-num;
			tinyArg="$"+num;
		}
		else if(arg.startsWith("$L")){
			int num = Integer.parseInt(arg.substring(2));
			num=-num;
			tinyArg="$"+num;
		}
		else if(arg.startsWith("$R")){
			if(arg.equals("$R")){
				int num=6+curParaVar;
				tinyArg="$"+num;
			}
			else{
				int num = Integer.parseInt(arg.substring(2));
				num=5-num;
				tinyArg="$"+num;
			}
		}
		else{
			tinyArg=arg;
		}
		
		return tinyArg;
	}
	
	
	public void addTinyCode(IRNode irnode){
		irnode.printIRNode();
		
		int rx=-1;
		int ry=-1;
		int rz=-1;
		switch(irnode.opCode){
			//ADDI OP1 OP2 RESULT (Integer Add)
			case ADDI: 
			//ADDF OP1 OP2 RESULT (Floating Point Add)
			case ADDF:
			//SUBI OP1 OP2 RESULT (Integer Subtract)
			case SUBI:
			//SUBF OP1 OP2 RESULT (Floating Point Subtract: RESULT = OP1/OP2)
			case SUBF:
			//MULTI OP1 OP2 RESULT (Integer Multiplication)
			case MULTI:
			//MULTF OP1 OP2 RESULT (Floating Point Multiplication)
			case MULTF:
			//DIVI OP1 OP2 RESULT (Integer Division)
			case DIVI:
			//DIVF OP1 OP2 RESULT (Floating Point Division: RESULT = OP1/OP2)
			case DIVF:
				if(irnode.op1!=null){
					rx=ensure(transArg(irnode.op1), irnode);
				}
				if(irnode.op2!=null){
					ry=ensure(transArg(irnode.op2), irnode);
				}
				
				if(!contain(irnode.out, transArg(irnode.op1))){
					free(rx, irnode);
				}
				
				if(!contain(irnode.out, transArg(irnode.op2))){
					free(ry, irnode);
				}
				
				
				if(irnode.result!=null){
					if(reg[rx].dirty>0){
						free(rx, irnode);
					}
					rz=rx;
					reg[rz].setTime();
					reg[rz].setStr(transArg(irnode.result));
//					rz=allocate(transArg(irnode.result), irnode);
				}
//				if(rx==rz){
				codeList.add(new TinyNode(irnode.opCode, reg[ry].getName(), reg[rz].getName()));
				reg[rz].setDirty(2);

				break;
			//STOREI OP1 RESULT (Integer Store, Store OP1 to RESULT)
			case STOREI:
			//STOREF OP1 RESULT (FP Store)
			case STOREF:
				if(globalVar.indexOf(irnode.result)>=0){
		
					String op1=null;
					String result=null;

						if(irnode.op1!=null){
							rx=ensure(transArg(irnode.op1), irnode);
						}
						op1=reg[rx].getName();
						if(irnode.result!=null){
							rz=ensure(transArg(irnode.result), irnode);
						}
						result=reg[rz].getName();
//					}
//						result=irnode.result;
					codeList.add(new TinyNode(irnode.opCode, op1, irnode.result));
					codeList.add(new TinyNode(irnode.opCode, op1, result));
				}else if(irnode.op1.startsWith("$L") || irnode.op1.startsWith("$P")){	
				
					boolean exist=false;
					if(irnode.op1!=null){
						for(int i=0;i<NUMREG;i++){
							if(reg[i].getStr().equals(transArg(irnode.op1))){
								exist=true;
							}
						}
						rx=ensure(transArg(irnode.op1), irnode);
					}
					if(!exist){
						codeList.add(new TinyNode(irnode.opCode, reg[rx].getStr(), reg[rx].getName()));
					}
					
					if(!irnode.result.equals("$R")){
						if(irnode.result!=null){
							rz=ensure(transArg(irnode.result), irnode);
						}
						codeList.add(new TinyNode(irnode.opCode, reg[rx].getName(), reg[rz].getName()));
						reg[rz].setDirty(2);
					}
					else if(globalVar.indexOf(irnode.result)>=0){
						codeList.add(new TinyNode(irnode.opCode, reg[rx].getName(), irnode.result));
					}else{
						codeList.add(new TinyNode(irnode.opCode, reg[rx].getName(), transArg(irnode.result)));
					}
					
					if(!contain(irnode.out, transArg(irnode.op1))){
						free(rx, irnode);
					}
				}else if(!irnode.op1.matches("[0-9]+") && (!irnode.op1.matches("[+-]?[0-9]+\\.?[0-9]+"))){
					if(irnode.op1!=null){
						rx=ensure(transArg(irnode.op1), irnode);
					}
					
					
					if(!irnode.result.equals("$R")){
						if(irnode.result!=null){
							rz=ensure(transArg(irnode.result), irnode);
						}
						codeList.add(new TinyNode(irnode.opCode, reg[rx].getName(), reg[rz].getName()));
						reg[rz].setDirty(2);
					}
					else{
						codeList.add(new TinyNode(irnode.opCode, reg[rx].getName(), transArg(irnode.result)));
					}
					
					if(!contain(irnode.out, transArg(irnode.op1))){
						free(rx, irnode);
					}
				}
				else{
					if(!irnode.result.equals("$R")){
						if(irnode.result!=null){
							rz=ensure(transArg(irnode.result), irnode);
						}
						codeList.add(new TinyNode(irnode.opCode, irnode.op1, reg[rz].getName()));
						reg[rz].setDirty(2);
					}
					else if(globalVar.indexOf(irnode.result)>=0){
						codeList.add(new TinyNode(irnode.opCode, reg[rx].getName(), irnode.result));
					}else{
						codeList.add(new TinyNode(irnode.opCode, irnode.op1, transArg(irnode.result)));
					}
				}
				if(!contain(irnode.out, transArg(irnode.op1))){
					free(rx, irnode);
				}
				break;
			//GT OP1 OP2 LABEL (If OP1 > OP2 Goto LABEL)
			case GT:
			//GE OP1 OP2 LABEL (If OP1 >= OP2 Goto LABEL)
			case GE:
			//LT OP1 OP2 LABEL (If OP1 < OP2 Goto LABEL)
			case LT:
			//LE OP1 OP2 LABEL (If OP1 <= OP2 Goto LABEL)
			case LE:
			//NE OP1 OP2 LABEL (If OP1 != OP2 Goto LABEL)
			case NE:
			//EQ OP1 OP2 LABEL (If OP1 = OP2 Goto LABEL)
			case EQ:
				compare(irnode.op1, irnode.op2, irnode.opCode, irnode.isFloat, irnode);
			//JUMP LABEL (Direct Jump)
			case JUMP:
			//LABEL STRING (set a STRING Label)
				for(int i=0;i<NUMREG;i++){
//					if(!contain(irnode.out, reg[i].getStr())){
						free(i, irnode);
//					}
				}
				codeList.add(new TinyNode(irnode.opCode, transArg(irnode.result)));
				break;
				
			
			case POP:
			//READI RESULT
			case READI:
			//READF RESULT
			case READF:
				if(globalVar.indexOf(irnode.result)>=0){
					String result=null;
					
					if(globalVar.indexOf(irnode.result)>=0){
						result=irnode.result;
					}
					else{
						if(irnode.result!=null){
							rz=allocate(transArg(irnode.result), irnode);
						}
						result=reg[rz].getName();
						reg[rz].setDirty(2);
						if(!contain(irnode.out,reg[rz].getStr())){
							free(rz, irnode);
						}
					}
					codeList.add(new TinyNode(irnode.opCode, result));
				}
				else if(irnode.result!=null && (!irnode.result.equals(""))){
					rz=allocate(transArg(irnode.result), irnode);
					codeList.add(new TinyNode(irnode.opCode, reg[rz].getName()));
					reg[rz].setDirty(2);
					if(!contain(irnode.out,reg[rz].getStr())){
						free(rz, irnode);
					}
				}
				else{
					codeList.add(new TinyNode(irnode.opCode));
				}
				
				
				break;
			
			//WRITEI RESULT
			case WRITEI:
			//WRITEF RESULT
			case WRITEF:
			//WRITES RESULT
			case WRITES:
				if(irnode.result==null || (irnode.result.equals(""))){
					codeList.add(new TinyNode(irnode.opCode));
				}
				else if(irnode.result.startsWith("$")){
					rz=ensure(transArg(irnode.result), irnode);
//					reg[rz].setDirty(2);
					if(!contain(irnode.out,reg[rz].getStr())){
						free(rz, irnode);
					}
					codeList.add(new TinyNode(irnode.opCode, reg[rz].getName()));
					
				}
				else{
					codeList.add(new TinyNode(irnode.opCode, transArg(irnode.result)));
				}
				break;
			case PUSH:

				if(irnode.result==null || (irnode.result.equals(""))){
					codeList.add(new TinyNode(irnode.opCode));
				}
				else if(irnode.result.startsWith("$")){
					rz=ensure(transArg(irnode.result), irnode);
					reg[rz].setDirty(2);
					if(!contain(irnode.out, transArg(irnode.result))){
						free(rz, irnode);
					}
					codeList.add(new TinyNode(irnode.opCode, reg[rz].getName()));
					
				}
				else{
					codeList.add(new TinyNode(irnode.opCode, transArg(irnode.result)));
				}
				break;
			case LINK:
				codeList.add(new TinyNode(TinyNode.TinyOp.link, Integer.toString(curLocalVar+15)));
				break;
			case RET:
				for(int i=0;i<NUMREG;i++){
					if(!contain(irnode.out, reg[i].getStr())){
						free(i, irnode);
					}
				}
				codeList.add(new TinyNode(TinyNode.TinyOp.unlnk));
				codeList.add(new TinyNode(TinyNode.TinyOp.ret));
				
				break;
			
			case JSR:
//				Register[] tempReg=new Register[4];
				for(int i=0;i<NUMREG;i++){
					if(!contain(irnode.out, reg[i].getStr())){
						free(i, irnode);
					}
				}

				codeList.add(new TinyNode(TinyNode.TinyOp.push, "r0"));
				codeList.add(new TinyNode(TinyNode.TinyOp.push, "r1"));
				codeList.add(new TinyNode(TinyNode.TinyOp.push, "r2"));
				codeList.add(new TinyNode(TinyNode.TinyOp.push, "r3"));
				codeList.add(new TinyNode(TinyNode.TinyOp.jsr, transArg(irnode.result)));
				codeList.add(new TinyNode(TinyNode.TinyOp.pop, "r3"));
				codeList.add(new TinyNode(TinyNode.TinyOp.pop, "r2"));
				codeList.add(new TinyNode(TinyNode.TinyOp.pop, "r1"));
				codeList.add(new TinyNode(TinyNode.TinyOp.pop, "r0"));
				break;
			case LABEL:
				for(int i=0;i<NUMREG;i++){
//					if(!contain(irnode.out, reg[i].getStr())){
						free(i, irnode);
//					}
				}
				codeList.add(new TinyNode(TinyNode.TinyOp.label, transArg(irnode.result)));
				if(!irnode.result.startsWith("label")){
					
					String currentTable=irnode.result;
					curLocalVar=stl.getSymbolTable().get(stl.searchTable(currentTable)).countNumLocal();
					curParaVar=stl.getSymbolTable().get(stl.searchTable(currentTable)).countNumPara();
				}

				break;
			default:
				break;
		}
		
		
		for(int i=0;i<NUMREG;i++){
			System.out.print(";      r"+i);
			if(reg[i].dirty>0){
			System.out.print(" "+reg[i].getStr());
			}
			else{
				System.out.print(" "+null);
			}
		}
		System.out.println();
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
	
	public void compare(String op1, String op2, IRNode.IROp irop, boolean isFloat, IRNode irnode){
		TinyNode.TinyOp compri = isFloat? TinyNode.TinyOp.cmpr:TinyNode.TinyOp.cmpi;
		int rx=-1;
		int ry=-1;
		if(op1!=null){
			rx=ensure(transArg(op1), irnode);
		}
		if(op2!=null){
			ry=ensure(transArg(op2), irnode);
		}
		
		if(irop != IRNode.IROp.GE && irop != IRNode.IROp.GT){
			codeList.add(new TinyNode(compri, reg[rx].getName(), reg[ry].getName()));
		}
		else{
			System.out.println(";           GE || GT");
			codeList.add(new TinyNode(compri, reg[rx].getName(), reg[ry].getName()));
		}
		
		if(rx!=-1 && !contain(irnode.out,reg[rx].getStr())){
			free(rx, irnode);
		}
		
		if(ry!=-1 && !contain(irnode.out,reg[ry].getStr())){
			free(ry, irnode);
		}

	}
	
	
	
	
	
	//return index of r
	public int ensure(String op, IRNode irnode){
		System.out.println(";      ensure  "+op);

		for(int i=0;i<NUMREG;i++){
			if(reg[i].dirty > 0 && reg[i].getStr().equals(op)){
				reg[i].setTime();
				return i;
			}
		}
		//load
//		System.out.println(";      ensure+allocate"+op);
		int index=allocate (op, irnode);
	//	if(irnode.opCode!=IRNode.IROp.POP && irnode.opCode!=IRNode.IROp.STOREF && irnode.opCode!=IRNode.IROp.STOREI && irnode.opCode!=IRNode.IROp.READF && irnode.opCode!=IRNode.IROp.READI){
		codeList.add(new TinyNode(TinyNode.TinyOp.move, op, reg[index].getName()));
		//}

		return index;

	}
	

	public void free(int index, IRNode irnode){
		if(index<0){
			return;
		}
		System.out.println(";      free   "+index+"  "+reg[index].getStr());

		if(reg[index].dirty == 2 && contain(irnode.out, reg[index].getStr())){
			System.out.println(";      store "+index+"  "+reg[index].getStr());
			codeList.add(new TinyNode(TinyNode.TinyOp.move, reg[index].getName(), reg[index].getStr()));
		}

		reg[index].clearTime();
		reg[index].setDirty(0);
//		reg[index].setStr(null);
	}
	
	public int allocate(String op, IRNode irnode){
		System.out.println(";      allocate   "+op);
		for(int i=NUMREG-1;i>=0;i--){
			if(reg[i].getDirty()==0){
				reg[i].setTime();
				reg[i].setStr(op);
				reg[i].setDirty(1);
				return i;
			}
		}
		
		int index=0;
		for(int i=1; i<NUMREG;i++){
			if(reg[i].getTime()<reg[index].getTime()){
				index=i;
			}
		}
		free(index, irnode);
		
		reg[index].setDirty(1);
		reg[index].setTime();
		reg[index].setStr(op);
		return index;
		
	}
	
	public boolean contain(ArrayList<String> arlst, String regStr){
		for(int i=0;i<arlst.size();i++){
			if(transArg(arlst.get(i)).equals(regStr)){
				return true;
			}
		}
		return false;
	}
}
