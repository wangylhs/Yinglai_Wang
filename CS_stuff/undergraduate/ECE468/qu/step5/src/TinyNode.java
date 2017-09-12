
public class TinyNode {
	
	public enum TinyOp {
        var,
        str,
        label,
        move,
        addi,
        addr,
        subi,
        subr,
        muli,
        mulr,
        divi,
        divr,
        inci,
        deci,
        cmpi,
        push,
        pop,
        jsr,
        ret,
        link,
        unlnk,
        cmpr,
        jmp,
        jgt,
        jlt,
        jge,
        jle,
        jeq,
        jne,
        sys_readi,
        sys_readr,
        sys_writei,
        sys_writer,
        sys_writes,
        sys_halt,
        end
	}

	public TinyOp op;
	public String arg1;
	public String arg2;
		
	public TinyNode(){
		this.op=null;
		this.arg1=null;
		this.arg2=null;
	}
	
	public TinyNode(TinyOp op){
		this.op=op;
		this.arg1=null;
		this.arg2=null;
	}
	
	public TinyNode(TinyOp op, String arg1){
		this.op=op;
		this.arg1=arg1;
		this.arg2=null;
	}
	
	public TinyNode(TinyOp op, String arg1, String arg2){
		this.op=op;
		this.arg1=arg1;
		this.arg2=arg2;
	}
	
	public String getOp(){
		String option = null;
		switch(op){
			case var: option= "var";break;
			case str: option= "str";break;
			case label: option= "label";break;
			case move: option= "move";break;
			case addi: option= "addi";break;
			case addr: option= "addr";break;
			case subi: option= "subi";break;
			case subr: option= "subr";break;
			case muli: option= "muli";break;
			case mulr: option= "mulr";break;
			case divi: option= "divi";break;
			case divr: option= "divr";break;
			case inci: option= "inci";break;
			case deci: option= "deci";break;
			case cmpi: option= "cmpi";break;
			case push: option= "push";break;
			case pop: option= "pop";break;
			case jsr: option= "jsr";break;
			case ret: option= "ret";break;
			case link: option= "link";break;
			case unlnk: option= "unlnk";break;
			case cmpr: option= "cmpr";break;
			case jmp: option= "jmp";break;
			case jgt: option= "jgt";break;
			case jlt: option= "jlt";break;
			case jge: option= "jge";break;
			case jle: option= "jle";break;
			case jeq: option= "jeq";break;
			case jne: option= "jne";break;
			case sys_readi: option= "sys readi";break;
			case sys_readr: option= "sys readr";break;
			case sys_writei: option= "sys writei";break;
			case sys_writer: option= "sys writer";break;
			case sys_writes: option= "sys writes";break;
			case sys_halt: option= "sys halt";break;
			case end: option= "end";break;
		}
		return option;
	}
	
	public String getArg1(){
		return arg1;
	}
	
	public String getArg2(){
		return arg2;
	}
}
