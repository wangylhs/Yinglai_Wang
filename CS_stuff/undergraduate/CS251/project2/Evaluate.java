
public class Evaluate {
	public static void main(String[] args){
		Stack<String> operators = new Stack<String>();
		Stack<Double> operands = new Stack<Double>();
		
		//Read token, push if operator
		while(!StdIn.isEmpty()){
			String s = StdIn.readString();
			if(s.equals("("))						;
			else if(s.equals("+")) operators.push(s);
			else if(s.equals("-")) operators.push(s);
			else if(s.equals("*")) operators.push(s);
			else if(s.equals("/")) operators.push(s);
			else if(s.equals("sqrt")) operators.push(s);
			else if(s.equals(")")){
				String opr = operators.pop();
				double value = operands.pop();
				if(opr.equals("+"))
					value = operands.pop() + value;
				if(opr.equals("-"))
					value = operands.pop() - value;
				if(opr.equals("*"))
					value = operands.pop() * value;
				if(opr.equals("/"))
					value = operands.pop() / value;
				if(opr.equals("sqrt"))
					value = Math.sqrt(value);
				operands.push(value);
			}
			else 
				operands.push(Double.parseDouble(s));
		}
		StdOut.println(operands.pop());
	}
}
