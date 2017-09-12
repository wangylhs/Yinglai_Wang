
public class Symbol {
	private String name;
	private String type;
	private String value;
	private boolean isPara;
	
	public Symbol(){
		this.name=null;
		this.type=null;
		this.value=null;
		this.isPara=false;
	}
	
	public Symbol(String name, String type, String value, boolean isPara){
		this.name=name;
		this.type=type;
		this.value=value;
		this.isPara=isPara;
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
	
	public void setPara(boolean isPara){
		this.isPara=isPara;
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
	
	public boolean getPara(){
		return isPara;
	}
}
