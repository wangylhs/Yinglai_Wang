import java.util.NoSuchElementException;

public class DoubleStack<T> {
	static int Nred, N, Nblue;
	static int posR, posB;
	T[] elements;
    T temp;
    
	public enum Color {
		RED, BLUE
	}
	public DoubleStack(int N) {
		this.N=N;
	}

	public int size(Color c) {
		if (c.equals(Color.RED))
			return Nred;
		if (c.equals(Color.BLUE))
			return Nblue;
		return 0;
	}

	public void push(T item, Color c) {
		if(isFull())
			throw new RuntimeException("Stack overflow!");
		if(c.equals(Color.BLUE)){
			elements[posB] = item;
			posB--;
			Nblue++;
		}
		if(c.equals(Color.RED)){
			elements[posR] = item;
			posR++;
			Nred++;
		}
	}

	public T pop(Color c) {
		
		if(isEmpty(c))
			throw new RuntimeException( c + "Stack is impty!");
		if(c.equals(Color.BLUE)){
            posB++;
			temp = elements[posB];
			elements[posB] = null;
			Nblue--;
			return temp;
		}
		if(c.equals(Color.RED)){
            posR--;
			temp = elements[posR];
			elements[posR] = null;
			Nred--;
			return temp;
		}
		return temp;
	}

	public T peek(Color c) {
		if(isEmpty(c))
			throw new RuntimeException( c + "Stack is impty!");
		if(c.equals(Color.BLUE)){
            posB++;
			temp = elements[posB];
            posB--;
			return temp;
		}
		if(c.equals(Color.RED)){
            posR--;
			temp = elements[posR];
            posR++;
			return temp;
		}
		return temp;
	}

	public boolean isEmpty(Color c) {
		if(c.equals(Color.BLUE)){
			if(Nblue==0)
				return true;
		}
		if(c.equals(Color.RED)){
			if(Nred==0)
				return true;
		}
		return false;
	}

	public boolean isFull() {
		if ((Nred + Nblue) == N)
			return true;
		else
			return false;
	}
	public static void main(String[] args){
		DoubleStack<String> stack;
        Color currentColor = Color.RED;
		Nred = 0;
		Nblue = 0;
		int size = StdIn.readInt();
        posR = 0;
        posB = size-1;
		stack = new DoubleStack<String>(size);
        stack.elements = new String[size];
        stack.temp = new String();
        stack.temp = null;
        while(!StdIn.isEmpty()){
            String next = StdIn.readString();
            if(next.equals("--blue"))
                currentColor = Color.BLUE;
            else if(next.equals("--red"))
                currentColor = Color.RED;
            else if(next.equals("-")){
                String popedElement = stack.pop(currentColor);
                StdOut.print(popedElement + " ");
            }
            else if(next.equals("?")){
                String peekedElement = stack.peek(currentColor);
                StdOut.print(peekedElement + " ");
            }else{
                stack.push(next, currentColor);
                }
            }
        StdOut.println("\n("+Nred + " left on RED stack, " + Nblue + " left on BLUE stack)");
        }
        
}
