import java.util.*;
import java.lang.*;

public class chapter3 {
	
	
	public static void main(String[] args){
		/*FixedMultiStack fs = new FixedMultiStack(10);
		fs.push(0, 1);
		fs.push(1, 2);
		fs.push(2, 3);
		fs.push(0, 4);
		fs.push(1, 5);
		System.out.println(fs.pop(0));
		System.out.println(fs.pop(0));
		System.out.println(fs.pop(1));
		System.out.println(fs.peek(0));
		System.out.println(fs.peek(1));
		System.out.println(fs.peek(2));
		*/
		StackWithMin swm = new StackWithMin();
		swm.push(1);
		swm.push(2);
		swm.push(3);
		System.out.println(swm.min());
	}
}

