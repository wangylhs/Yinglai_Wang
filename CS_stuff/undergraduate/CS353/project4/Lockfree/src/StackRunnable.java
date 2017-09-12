
public class StackRunnable implements Runnable {

	// number of iterations
	private int iterations;
	// shared stack instance
	private Stack<Integer> stack;

	public StackRunnable(int iterations, Stack<Integer> stack) {
		this.iterations = iterations;
		this.stack = stack;
	}


	public void run() {
		for (int i = 0; i < iterations; i++) {
			// push current iteration number
			stack.push(i);
			// pop item from stack
			stack.pop();
		}
	}
}