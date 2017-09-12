import java.util.*;

public class Car extends Vehicle{
  static Random r = new Random();

  public Car(){
    
    super(r.nextInt(100));
  }
  public void doneFixing(){
    System.out.println("Car "+id+" is done being fixing");
  }
  
}