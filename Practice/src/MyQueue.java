import java.util.Stack;

public class MyQueue {
	Stack<Integer> newest, oldest;
	
	public MyQueue(){
		newest = new Stack<Integer>();
		oldest = new Stack<Integer>();
	}
	public int size(){
		return newest.size()+oldest.size();
	}
	public void add(int value){
		newest.push(value);
	}
	public int remove(){
		shift();
		return oldest.pop();
	}
	public void shift(){
		if(oldest.isEmpty()){
			while(!newest.isEmpty()){
				oldest.push(newest.pop());
			}
		}
	}
	public int peek(){
		shift();
		return oldest.peek();
	}
}
