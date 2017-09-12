import java.util.TreeMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class StackDriver {
    public static final int ITERATION = 10000;
    public static final int TOTAL_RUN = 15;
    private static Stack<Integer> stack;
    private static ExecutorService executor;
    //map to record the tries of each run
    private static TreeMap<Integer, Double> TriesMap;
    //map to record the time of each run
    private static TreeMap<Integer, Double> TimeMap;
    
    public static void main(String[] args) {
        System.out.println("Start running ......");
        
        TriesMap = new TreeMap<Integer, Double>();
        TimeMap = new TreeMap<Integer, Double>();
        
        for(int i=0; i<5; i++){
        }
    
    
    }
}
