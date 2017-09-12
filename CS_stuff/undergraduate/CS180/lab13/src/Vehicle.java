public class Vehicle{
  
  protected int fix_time;
  protected int id;
  
  public Vehicle(int id){
    fix_time=500;
    this.id=id;
  }
  
  public void fix(){
    try{Thread.sleep(fix_time);}catch(Exception e){}
    doneFixing();
  }
  
  public void fix(int sleep ){
    try{Thread.sleep(sleep);}catch(Exception e){}
    doneFixing();
  }
  
  public void doneFixing(){
    System.out.println("Vehicle "+id+" is done being fixing");
  }
  
}