//import java.lang.Math;
public class Ln{
    public static double Ln(int N){
        double e = Math.E;
        //double value = 0;
        //value = Math.log((double)N);
        if(N==1 || N==0)
            return Math.log((double)N);
        return Ln(N-1) + Ln(N-2);
    }
    public static void main(String[] args){
        System.out.println(Ln(6));
    }
}