
public class Log{
    public static int logbase2(int N){
        int i=0;
        int value=1;
        if(N==1)
            return 0;
        for(int j=0; j<N; j++){
            value = value*2;
            if(value > N)
                return j;
        }
        return -1;
    }
    public static void main(String[] args){
        int n = Integer.parseInt(args[0]);
        System.out.println("The value of log(base 2) " + n +" is " + logbase2(n) + ".");
    }
}