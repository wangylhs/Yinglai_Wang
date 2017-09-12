
public class Symbol {
	public String name;
	public String type;
	public String value;
	
	public Symbol(){
		this.name=null;
		this.type=null;
		this.value=null;
	}
	
	public Symbol(String name, String type, String value){
		this.name=name;
		this.type=type;
		this.value=value;
	}
	
	public void setName(String name){
		this.name=name;
	}
	
	public void setType(String type){
		this.type=type;
	}
	
	public void setValue(String value){
		this.value=value;
	}
	
	public String getName(){
		return name;
	}
	
	public String getType(){
		return type;
	}
	
	public String getValue(){
		return value;
	}

}
