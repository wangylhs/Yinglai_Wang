
import java.util.concurrent.atomic.AtomicInteger;


public class NonBlockingPseudoRandom extends PseudoRandom {

    private AtomicInteger seed;

    NonBlockingPseudoRandom (int seed) {
        this.seed = new AtomicInteger(seed);
    }

     public int nextInt (int n) {
    	 while (true) {
 			int s = seed.get();
 			int nextSeed = calculateNext(s);
 			
 			if (seed.compareAndSet(s, nextSeed)) {
 				int remainder = s % n;
 				return remainder > 0 ? remainder : remainder + n;
 			}
    	 }
     }

	
}
