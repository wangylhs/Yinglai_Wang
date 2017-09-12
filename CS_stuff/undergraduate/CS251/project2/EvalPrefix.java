public class EvalPrefix{
    static DoubleStack.Color Color;
    public static boolean isOperator(String s){
        if(s.equals("+"))
            return true;
        else if(s.equals("-"))
            return true;
        else if(s.equals("*"))
            return true;
        else if(s.equals("/"))
            return true;
        else
            return false;
    }
    public boolean isOperands(String s){
        if(s.matches("\\d"))
            return true;
        else
            return false;
    }
    public static void reverse(String[] a){
        String temp;
        for(int i=0; i<a.length/2; i++){
            temp = a[i];
            a[i] = a[a.length-i-1];
            a[a.length-i-1] = temp;
        }
    }
    
    public static void main(String[] args){
        DoubleStack<String> stack;
        int size = 500;
        stack = new DoubleStack<String>(size);
        stack.elements = new String[size];
        stack.temp = new String();
        stack.temp = null;
        stack.Nred = 0;
        stack.Nblue = 0;
        stack.posR = 0;
        stack.posB = size-1;
        String s;
        String[] a;
        while(StdIn.hasNextLine()){
            s = StdIn.readLine();
            a = s.split(" ");
            reverse(a);
            for(int i=0; i<a.length; i++){
                if(isOperator(a[i])){
                    stack.push(a[i], Color.RED);
                String op = stack.pop(Color.RED);
                int result = Integer.parseInt(stack.pop(Color.BLUE));
                if(op.equals("+"))
                    result += Integer.parseInt(stack.pop(Color.BLUE));
                if(op.equals("-"))
                    result -= Integer.parseInt(stack.pop(Color.BLUE));
                if(op.equals("*"))
                    result *= Integer.parseInt(stack.pop(Color.BLUE));
                if(op.equals("/"))
                    result /= Integer.parseInt(stack.pop(Color.BLUE));
                stack.push(Integer.toString(result), Color.BLUE);
                }else
                    stack.push(a[i], Color.BLUE);
            }
            StdOut.print(stack.pop(Color.BLUE) + "\n");
            
        }
    }
}