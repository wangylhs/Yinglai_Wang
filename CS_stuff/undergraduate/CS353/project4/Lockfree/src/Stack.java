import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

public class Stack<T> {
	private AtomicReference<Node<T>> stack;
	private AtomicInteger tries;
	private int size;
	
	public Stack(){
		stack = new AtomicReference<Node<T>>();
		tries = new AtomicInteger();
	}
	
	public void push(T item){
		Node<T> oldh = null;
		Node<T> newh = new Node<T>(item);
		while(!stack.compareAndSet(oldh, newh)){
			oldh = stack.get();
			newh.next = oldh;
			tries.getAndIncrement();
		}
		++size;
	}
	public T pop(){
		Node<T> oldh = null;
		Node<T> newh = null;
		while(!stack.compareAndSet(oldh, newh)){
			oldh = stack.get();
			if(oldh==null){
				return null;
			}
			newh = oldh.next;
			tries.getAndIncrement();
		}
		--size;
		return oldh.value;
	}
	public int size(){
		return size;
	}
	public int getTries(){
		return tries.get();
	}

}
