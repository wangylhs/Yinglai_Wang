
public class Register {
    
    long time;
    int index;
    String str;
    int dirty;
    
    public Register(){
        time =-1;
        index = -1;
        str="";
        dirty = 0;
    }
    
    
    public void setDirty(int dir){
        this.dirty=dir;
    }
    
    public int getDirty(){
        return dirty;
    }
    
    public void setTime(){
        this.time=System.currentTimeMillis();
    }
    
    public long getTime(){
        return time;
    }
    
    public void clearTime(){
        time=0;
    }
    
    public void setIndex(int index){
        this.index=index;
    }
    
    public int getIndex(){
        return index;
    }
    
    public void setStr(String str){
        this.str=str;
    }
    
    public String getStr(){
        return str;
    }
    
    public String getName(){
        return "r"+index;
    }
    
    public Register getReg(){
        Register reg = new Register();
        reg.dirty=this.dirty;
        reg.index=this.index;
        reg.str=this.str;
        reg.time=this.time;
        return reg;
    }
}
