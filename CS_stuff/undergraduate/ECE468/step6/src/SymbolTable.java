import java.util.ArrayList;
import java.util.LinkedList;

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
	
	public void printTable(){
		System.out.println("Symbol table "+name);
		for(int i=0;i<symbolTable.size();i++){
			System.out.print(symbolTable.get(i).getPara()+"   ");
			if(symbolTable.get(i).getValue().equals("")){
				System.out.println("name "+symbolTable.get(i).getName()+" type "+symbolTable.get(i).getType());
			}
			else{
				System.out.println("name "+symbolTable.get(i).getName()+" type "+symbolTable.get(i).getType()+" value "+symbolTable.get(i).getValue());
			}
		}
		System.out.println(countNumPara());
		System.out.println();
	}
	
	public int countNumPara(){
		int count=0;
		for(int i=0;i<symbolTable.size();i++){
			if(symbolTable.get(i).getPara()){
				count++;
			}
		}
		return count;
	}
	public int countNumLocal(){
		int count=0;
		for(int i=0;i<symbolTable.size();i++){
			if(!symbolTable.get(i).getPara()){
				count++;
			}
		}
		return count;
	}
	
	public Symbol getSymbol(int i){
		return symbolTable.get(i);
	}

	public ArrayList<Symbol> get(){
		return symbolTable;
	}
	public int size(){
		return symbolTable.size();
	}
//	private isType
	
}
