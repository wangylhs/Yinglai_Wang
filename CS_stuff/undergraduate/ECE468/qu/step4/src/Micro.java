import java.io.IOException;
import java.util.*;

import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.ParseTree;

public class Micro {

	// static ArrayList<SymbolTable> symbolTable ;

	/**
	 * @param args
	 */
	public class Tree {
		String value;
		Tree left, right;
	}

	static int regCount = 1;
	static LinkedList<IRNode> IR;
	static ArrayList<SymbolTable> symbolTable;

	public Micro() {
		// symbolTable = new ArrayList<SymbolTable>();
	}

	public static void main(String[] args) {

		// lets do some file io

		CharStream inputstream = null;
		MicroLexer lexer = null;
		CommonTokenStream tokens = null;
		MicroParser parser = null;
		ParseTree tree = null;

		Micro micro = new Micro();
		try {
			inputstream = new ANTLRFileStream(args[0].trim());
			lexer = new MicroLexer(inputstream);
			symbolTable = new ArrayList<SymbolTable>();
			symbolTable = micro.symbolTable(lexer);
			inputstream = new ANTLRFileStream(args[0].trim());
			lexer = new MicroLexer(inputstream);
			tokens = new CommonTokenStream(lexer);
			parser = new MicroParser(tokens);
			parser.setBuildParseTree(true);
			tree = parser.program();
			// parser.setErrorHandler(new Errorhandler());


		} catch (Exception e) {
			System.out.println("Couldn't find the file");
		}
		//micro.printSymbolTable(symbolTable);

		// Tree traveltree=tree.toStringTree();
		IR = new LinkedList<IRNode>();
		// genIR(tree.getChild(3), symbolTable);
		tree = tree.getChild(3).getChild(1).getChild(0).getChild(6).getChild(1);

		// printtree(tree);
		// printIRNode();
		genIR(tree, symbolTable);

		printIRNode();
		IRToTiny ir2tiny=new IRToTiny();
		ir2tiny.irToTiny(IR, symbolTable);
	
	}

	public static void printIRNode() {

		System.out.println(";IR code");
		for (int i = 0; i < IR.size(); i++) {
			System.out.println("; " + IR.get(i).opCode + " " + IR.get(i).op1
					+ " " + IR.get(i).op2 + " " + IR.get(i).result);
		}
	}

	public static void printtree(ParseTree tree) {
		for (int i = 0; i < tree.getChildCount(); i++) {

			System.out.println(tree.getChild(i).getText());

		}
	}

	public static void genIR(ParseTree AST, ArrayList<SymbolTable> symbolTable) {
		// System.out.println("in genIR:  " + AST.getChildCount());

		for (int i = 0; i < AST.getChildCount(); i++) {
			genStatement(AST.getChild(i), symbolTable);

		}
	}

	public static void genStatement(ParseTree AST,
			ArrayList<SymbolTable> symbolTable) {
		// System.out.println("in genStatement:  " + AST.getText());
		// + "  ```` " + AST.getText());
		if (AST.getText().contains("WRITE")) {
			ParseTree last = AST;
			while (AST.getChildCount() != 0) {
				last = AST;
				AST = AST.getChild(0);
			}
			AST = last;
			// System.out.println(AST.getChild(0).getText());
			if (AST.getChild(0).getText().equals("WRITE")) {
				IRNode n = new IRNode();
				boolean isFloat = isFloatSymbol(AST.getChild(0).getText(),
						symbolTable);
				n.opCode = (isFloat) ? (IRNode.IROp.WRITEF)
						: (IRNode.IROp.WRITEI);
				n.op1 = "";
				n.op2 = "";
				n.result = AST.getChild(2).getText();
				IR.add(n);
			}
		} else if (AST.getText().contains("READ")) {
			ParseTree last = AST;
			while (AST.getChildCount() != 0) {
				last = AST;
				AST = AST.getChild(0);
			}
			AST = last;
			// System.out.println(AST.getChild(0).getText());
			if (AST.getChild(0).getText().equals("READ")) {
				IRNode n = new IRNode();
				boolean isFloat = isFloatSymbol(AST.getChild(0).getText(),
						symbolTable);
				n.opCode = (isFloat) ? (IRNode.IROp.READF)
						: (IRNode.IROp.READI);
				n.op1 = "";
				n.op2 = "";
				n.result = AST.getChild(2).getText();
				IR.add(n);
			}
		} else if (AST.getText().contains(":=")) {
			ParseTree last = AST;
			while (AST.getChildCount() != 0) {
				last = AST;
				AST = AST.getChild(0);
			}
			AST = last.getParent();
			genAssignmentStatement(AST, symbolTable);

			// System.out.println(AST.getChild(2).getText() + "  `````" +
			// AST.getChildCount());

		}
	}

	public static void genAssignmentStatement(ParseTree AST,
			ArrayList<SymbolTable> symbolTable) {
		IRNode n = new IRNode();
		boolean isFloat = isFloatSymbol(AST.getChild(0).getText(), symbolTable);
		n.opCode = (isFloat) ? (IRNode.IROp.STOREF) : (IRNode.IROp.STOREI);
		n.result = AST.getChild(0).getText(); // where to store
		// for (int i = 0; i < AST.getChildCount(); i++)

		AST = AST.getChild(2);

		n.op1 = genExpression(AST, isFloat);

		n.op2 = "";
		IR.add(n);
	}

	public static String genExpression(ParseTree AST, boolean isFloat) {

		//System.out.println(AST.getText() + "`````" + AST.getChildCount());

		if (AST.getChildCount() == 1 && AST.getChild(0).getChildCount() == 0) {
			if (AST.getText().matches("[A-Za-z]")) {
				return AST.getText();
			} else {
				IRNode n = new IRNode();
				n.opCode = (isFloat) ? (IRNode.IROp.STOREF)
						: (IRNode.IROp.STOREI);
				String temp = genTempReg();
				n.result = temp; // where to store
				n.op1 = AST.getText();
				n.op2 = "";
				IR.add(n);
				return temp;
			}
		} else if (AST.getChildCount() == 1) {
			return genExpression(AST.getChild(0), isFloat);
		} else if (AST.getChildCount() > 3) {
			String temp = "";
			
			String tempOp1 = genExpression(AST.getChild(0), isFloat);
			for (int i = 0; i < AST.getChildCount()-2; i += 2) {
				IRNode n = new IRNode();

				
				if (AST.getChild(i+1).getText().equals("+"))
					n.opCode = (isFloat) ? (IRNode.IROp.ADDF)
							: (IRNode.IROp.ADDI);
				if (AST.getChild(i+1).getText().equals("-"))
					n.opCode = (isFloat) ? (IRNode.IROp.SUBF)
							: (IRNode.IROp.SUBI);
				if (AST.getChild(i+1).getText().equals("*"))
					n.opCode = (isFloat) ? (IRNode.IROp.MULTF)
							: (IRNode.IROp.MULTI);
				if (AST.getChild(i+1).getText().equals("/"))
					n.opCode = (isFloat) ? (IRNode.IROp.DIVF)
							: (IRNode.IROp.DIVI);
				n.op1=tempOp1;
				n.op2 = genExpression(AST.getChild(i + 2), isFloat);
				n.result = genTempReg();
				temp=n.result;
				IR.add(n);
				tempOp1=n.result;
//				n = new IRNode();

			}
			// return genExpression(AST.getChild(0), isFloat);
			return temp;

		} else if (AST.getChild(0).getText().equals("(")) {
			return genExpression(AST.getChild(1), isFloat);

		} else if (AST.getChild(1).getText().equals("+")) {
			IRNode n = new IRNode();
			n.opCode = (isFloat) ? (IRNode.IROp.ADDF) : (IRNode.IROp.ADDI);
			n.op1 = genExpression(AST.getChild(0), isFloat);
			n.op2 = genExpression(AST.getChild(2), isFloat);
			n.result = genTempReg();
			IR.add(n);
			return n.result;
		} else if (AST.getChild(1).getText().equals("*")) {
			IRNode n = new IRNode();
			n.opCode = (isFloat) ? (IRNode.IROp.MULTF) : (IRNode.IROp.MULTI);
			n.op1 = genExpression(AST.getChild(0), isFloat);
			n.op2 = genExpression(AST.getChild(2), isFloat);
			n.result = genTempReg();
			IR.add(n);
			return n.result;
		} else if (AST.getChild(1).getText().equals("-")) {
			IRNode n = new IRNode();
			n.opCode = (isFloat) ? (IRNode.IROp.SUBF) : (IRNode.IROp.SUBI);
			n.op1 = genExpression(AST.getChild(0), isFloat);
			n.op2 = genExpression(AST.getChild(2), isFloat);
			n.result = genTempReg();
			IR.add(n);
			return n.result;
		} else if (AST.getChild(1).getText().equals("/")) {

			IRNode n = new IRNode();
			n.opCode = (isFloat) ? (IRNode.IROp.DIVF) : (IRNode.IROp.DIVI);
			n.op1 = genExpression(AST.getChild(0), isFloat);
			n.op2 = genExpression(AST.getChild(2), isFloat);
			n.result = genTempReg();
			IR.add(n);
			return n.result;
		} else {
			// literal or symbol. just return
			return AST.getText();
		}

	}

	public static String genTempReg() {
		return "$T" + (regCount++);
	}

	public static boolean isFloatSymbol(String name,
			ArrayList<SymbolTable> symbolTable) {
		// start with local scope
		for (int i = 0; i < symbolTable.size(); i++)
			for (int j = 0; j < symbolTable.get(i).get().size(); j++) {
				Symbol te = symbolTable.get(i).get().get(j);
				if (te.name.equals(name))
					if (te.type.equals("FLOAT"))
						return true;
					else
						return false;
			}

		// System.out.println("symbol can not be found.");
		return false;
	}

	// create symboltables
	public ArrayList<SymbolTable> symbolTable(MicroLexer lexer) {
		ArrayList<SymbolTable> symbolTable = new ArrayList<SymbolTable>();
		Stack<SymbolTable> tempST = new Stack<SymbolTable>();
		Token temp = null;
		int blockCT = 1;
		boolean error = false;
		while ((temp = lexer.nextToken()).getText() != "<EOF>" && (!error)) {
			// System.out.println(temp.getType()+"    "+temp.getText());
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
			// new function
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
			// if/do
			case 8:
				st = new SymbolTable("BLOCK " + blockCT);
				symbolTable.add(st);
				tempST.push(st);
				blockCT++;
				break;
			// else if
			case 9:
				tempST.pop();
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
		if (token.getType() == 5) {
			return 1;
		}
		// Variable declaration INT/FLOAT/STRING
		else if (token.getType() == 33 | token.getType() == 27
				| token.getType() == 14) {
			return 2;
		}
		// FUNCTION
		else if (token.getType() == 25) {
			return 3;
		}
		// END/ENDIF/WHILE
		else if (token.getType() == 9 || token.getType() == 12
				|| token.getType() == 21) {
			return 4;
		}
		// id
		else if (token.getType() == 34) {
			return 5;
		}
		// ;/)
		else if (token.getType() == 24 | token.getType() == 19) {
			return 6;
		}
		// value of variable
		else if (token.getType() == 36 || token.getType() == 37
				|| token.getType() == 35) {
			return 7;
		}
		// if/do
		else if (token.getType() == 15 || token.getType() == 2) {
			return 8;
		}
		// elseif
		else if (token.getType() == 22) {
			return 9;
		}
		// else
		else {
			return 0;
		}
	}
	// public static void genReadStatement(ParseTree AST,
	// ArrayList<SymbolTable> symbolTable) {
	// for (int i = 0; i < AST.getChildCount(); i++) {
	// IRNode n = new IRNode();
	// boolean isFloat = isFloatSymbol(AST.getChild(i).getText(),
	// symbolTable);
	// n.opCode = (isFloat) ? (IRNode.IROp.READF) : (IRNode.IROp.READI);
	// n.op1 = "";
	// n.op2 = "";
	// n.result = AST.getChild(i).getText();
	// IR.add(n);
	// }
	// }
}
