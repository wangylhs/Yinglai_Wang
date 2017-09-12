public class Infix2Prefix{
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
        else if (s.equals("(") || s.equals(")"))
            return true;
        else
            return false;
    }
    
    public static boolean needPop(String a, String b) {
        String map = "+-*/()";
        int [][] p = new int[][] {
            {1, 1, 0, 0, 0, 1},
            {1, 1, 0, 0, 0, 1},
            {1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 0, 1},
            {0, 0, 0, 0, 0, 1}
        };
        
        return p[map.indexOf(a)][map.indexOf(b)]==1;
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
        
        while(StdIn.hasNextLine()){
            String l = StdIn.readLine();
            String[] line = l.split(" ");
            for(int i=0; i<line.length; i++){
                s = line[i];
                
                if (isOperator(s) == false) {
                    stack.push(s, Color.RED);
                } else if (s.equals(")")) {
                    while(!stack.isEmpty(Color.BLUE) &&
                          !stack.peek(Color.BLUE).equals("(")) {
                        String o = stack.pop(Color.BLUE);
                        String b = stack.pop(Color.RED), a = stack.pop(Color.RED);
                        stack.push(o + " " + a + " " + b, Color.RED);
                    }
                    stack.pop(Color.BLUE);
                } else {
                    while(!stack.isEmpty(Color.BLUE) &&
                          needPop(stack.peek(Color.BLUE), s)) {
                        String o = stack.pop(Color.BLUE);
                        String b = stack.pop(Color.RED), a = stack.pop(Color.RED);
                        stack.push(o + " " + a + " " + b, Color.RED);
                    }
                    stack.push(s, Color.BLUE);
                }
            }
            
            while(!stack.isEmpty(Color.BLUE)) {
                String o = stack.pop(Color.BLUE);
                String b = stack.pop(Color.RED), a = stack.pop(Color.RED);
                stack.push(o + " " + a + " " + b, Color.RED);
            }
            
            StdOut.print(stack.peek(Color.RED));
            StdOut.print("\n");
        }
    }
}