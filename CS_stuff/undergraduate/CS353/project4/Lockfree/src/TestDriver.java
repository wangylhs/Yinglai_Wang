

public class TestDriver {
	public static final int NO_OF_THREADS = 10;
	static final int HOW_LONG_TO_RUN = 4000;
	static ReentrantLockPseudoRandom myLPR = new ReentrantLockPseudoRandom(20);
	static NonBlockingPseudoRandom myNBPR = new NonBlockingPseudoRandom(20);
	
	private static class LPR implements Runnable{
		public int counter = 0;
		public void run(){
			while(true){
				myLPR.nextInt(100);
				counter++;
			}
		}
	}
	private static class NBPR implements Runnable{
		public int counter = 0;
		public void run(){
			myNBPR.nextInt(100);
			counter++;
		}
	}
	
	@SuppressWarnings("deprecation")
	public static void main(String[] args) throws InterruptedException{
		long start, end;
		Thread[] threads;
		int numlock;		//number generated of lock version
		int numnb;			//number generated of non-blocking
		//test lock version random number generator
		LPR[] lprs = new LPR[NO_OF_THREADS];
		threads = new Thread[NO_OF_THREADS];
		numlock = 0;
		start = System.currentTimeMillis();
		for(int i=0; i<NO_OF_THREADS; i++){
			lprs[i] = new LPR();
			threads[i] = new Thread(lprs[i]);
		}
		for (int i=0; i<NO_OF_THREADS; i++) {
			threads[i].start();
		}
		Thread.sleep(HOW_LONG_TO_RUN);
		for (int i=0; i<NO_OF_THREADS; i++) {
			threads[i].stop();
			numlock += lprs[i].counter;
		}
		end = System.currentTimeMillis();
		System.out.println("Lock version generated " + numlock + " random numbers in "
				+ (end-start) + " ms.");
		//test non-blocking version random numebr generator 
		NBPR[] nbprs = new NBPR[NO_OF_THREADS];
		threads = new Thread[NO_OF_THREADS];
		numnb = 0;
		start = System.currentTimeMillis();
		for (int i=0; i<NO_OF_THREADS; i++) {
			nbprs[i] = new NBPR();
			threads[i] = new Thread(nbprs[i]);
		}
		for (int i=0; i<NO_OF_THREADS; i++) {
			threads[i].start();
		}
		Thread.sleep(HOW_LONG_TO_RUN);
		for (int i=0; i<NO_OF_THREADS; i++) {
			threads[i].stop();
			numnb += nbprs[i].counter;
		}
		end = System.currentTimeMillis();
		System.out.println("Non-blocking version generated " + numnb + " random numbers in "
				+ (end-start) + " ms.");
		System.out.println("(Non-blocking version)/(Lock version) ratio is " + (1.0*numnb)/numlock);
	}
}
