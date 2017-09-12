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

	static LinkedList<LinkedList<IRNode>> IR;
	static ArrayList<SymbolTable> symbolTable;
	static public int label;
	public Micro() {
		// symbolTable = new ArrayList<SymbolTable>();
	}

	public static void main(String[] args) {
		label=0;
		// lets do some file io
		IR = new LinkedList<LinkedList<IRNode>>();
		CharStream inputstream = null;
		MicroLexer lexer = null;
		CommonTokenStream tokens = null;
		MicroParser parser = null;
		ParseTree tree = null;
		SymbolTableList stl = null;

		// Micro micro = new Micro();

		try {
			inputstream = new ANTLRFileStream(args[0].trim());
			lexer = new MicroLexer(inputstream);
			stl = new SymbolTableList(lexer);

			symbolTable = stl.getSymbolTable();
			// symbolTable = micro.symbolTable(lexer);
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

		// stl.printSymbolTable();

		// Tree traveltree=tree.toStringTree();
		// IR = new LinkedList<IRNode>();
		// genIR(tree.getChild(3), symbolTable);
		// go to the body
		GenIR genir;


		tree = tree.getChild(3).getChild(1);

		for (int i = 0; i < tree.getChildCount(); i++) {
//			System.out.println("~~~~~~~~~~   " + tree.getChild(i).getText());
			genir = new GenIR(tree.getChild(i), stl);
			IR.add(genir.getIR());
		}
		// tree =
		// tree.getChild(3).getChild(1).getChild(0).getChild(6).getChild(1);

		// printtree(tree);
		printIRNode();

		// printIRNode();
		 IRToTiny ir2tiny = new IRToTiny();
		 ir2tiny.irToTiny(IR, stl);

	}

	public static void printIRNode() {

		System.out.println(";IR code");
		for (int j = 0; j < IR.size(); j++) {
			for (int i = 0; i < IR.get(j).size(); i++) {
				System.out.println("; " + IR.get(j).get(i).opCode + " "
						+ IR.get(j).get(i).op1 + " " + IR.get(j).get(i).op2
						+ " " + IR.get(j).get(i).result);
			}
		//	System.out.println();
	//	System.out.println();
		}
	}

}
