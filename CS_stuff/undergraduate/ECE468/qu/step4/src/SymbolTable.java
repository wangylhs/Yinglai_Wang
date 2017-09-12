import java.util.ArrayList;

import org.antlr.v4.runtime.*;

public class SymbolTable {
	
	String name;
	ArrayList<Symbol> symbolTable;
	
	public SymbolTable(String name){
		this.name = name;
		symbolTable = new ArrayList<Symbol>();
	}
	
	public void addSymbol(Symbol symbol){
		symbolTable.add(symbol);
	}
	
	public boolean hasSymbol(String name){
		for(int i=0; i<symbolTable.size(); i++){
			if(symbolTable.get(i).getName().equals(name)){
				return true;
			}
		}
		return false;
	}
	public ArrayList<Symbol> get(){
		return symbolTable;
	}
	public void printTable(){
		System.out.println("Symbol table "+name);
		for(int i=0;i<symbolTable.size();i++){
			if(symbolTable.get(i).getValue().equals("")){
				System.out.println("name "+symbolTable.get(i).getName()+" type "+symbolTable.get(i).getType());
			}
			else{
				System.out.println("name "+symbolTable.get(i).getName()+" type "+symbolTable.get(i).getType()+" value "+symbolTable.get(i).getValue());
			}
		}
		System.out.println();
	}
	
	
//	private isType
	
}
