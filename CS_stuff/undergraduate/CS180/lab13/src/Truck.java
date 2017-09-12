import java.util.*;

public class Truck extends Vehicle{
  static Random r = new Random();
  public Truck(){
    super(r.nextInt(100));
  }
  public void doneFixing(){
    System.out.println("Truck "+id+" is done being fixing");
  }
}