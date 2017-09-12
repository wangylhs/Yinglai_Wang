import java.util.ArrayList;
import java.util.Stack;


public class SetOfStacks {
	ArrayList<Stack<Integer>> stacks = new ArrayList<Stack<Integer>>();
	public void push(int value){
		Stack<Integer> last;
		if(stacks.size()==0){
			last = new Stack<Integer>();
			last.push(value);
			stacks.add(last);
			
		}else{
			last = stacks.get(stacks.size()-1);
			if(last!=null && last.size()<=10){
				last.push(value);
			}else{
				Stack<Integer> s = new Stack<Integer>();
				s.push(value);
				stacks.add(s);
			}
		}
		
	}
	public int pop(){
		Stack<Integer> last = stacks.get(stacks.size()-1);
		int value;
		if(last==null){
			System.out.println("Error: Stack is null!");
			System.exit(0);
		}
		value = last.pop();
		if(last.size()==0) stacks.remove(stacks.size()-1);
		return value;
	}
}
