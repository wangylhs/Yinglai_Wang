import java.util.*;

public class Motorcycle extends Vehicle{
  static Random r = new Random();
  public Motorcycle(){
    super(r.nextInt(100));
  }
  public void doneFixing(){
    System.out.println("Motorcycle "+id+" is done being fixing");
  }
}