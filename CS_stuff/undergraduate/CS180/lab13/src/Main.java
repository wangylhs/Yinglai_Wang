import java.util.*;


public class Main{
  
  public static void main(String[] args){
    Holder h = new Holder();
    new Producer(h).start();
    new Consumer(h).start();
    
  }
  
}

class Holder{
  
  Vehicle v;
  
  public Holder(){
    v=getVehicleInstance();
  }

  
  public synchronized Vehicle getVehicle() throws Exception{
    
    while(v==null){
      wait();
    }
    Vehicle t = v;
    v = null;
    notifyAll();
   return t;
  }
  
  public synchronized void setVehicle(Vehicle t) throws Exception{
    
    while(v!=null){
    wait();
    }
    v = t;
    notifyAll();
    
  }
  
  
  public Vehicle getVehicleInstance(){
    return null;
  }
  
}

class Producer extends Thread{
  
  Holder h;
  
  public Producer(Holder h){
  this.h=h;
  }
  
  public void run(){
    Random r = new Random();
    while(true){int n = r.nextInt(3);
        if(n==0){
      try{
  h.setVehicle(new Car());
  }catch(Exception e){}
  
    }
      if(n==1){
      try{
  h.setVehicle(new Truck());
  }catch(Exception e){}
  
    }
        if(n==2){
      try{
  h.setVehicle(new Motorcycle());
  }catch(Exception e){}
  
    }
  }
  }
}



class Consumer extends Thread{
  
  Holder h;
  
  public Consumer(Holder h){ 
    this.h=h;
  }
    public void run(){
      while(true)try{
    h.getVehicle().fix();
      }catch(Exception e){}
    
  }
  
}
