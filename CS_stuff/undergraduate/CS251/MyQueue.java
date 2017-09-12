import java.util.*;

public class MyQueue<T> implements Iterable<T>{
    T[] elements,a;
    static int size;
    static int num;
    static int pos;
    T temp;
    public MyQueue(){
        size = 2;
        num = 0;
        pos = 0;
        temp = null;
    }
    public int size(){
        return num;
    }
    public boolean isEmpty(){
        if(num == 0)
            return true;
        else
            return false;
    }
    public boolean isFull(){
        if(num == size)
            return true;
        else
            return false;
    }
    public void enqueue(T item){
        if(isFull()){
            size = size * 2;
            resize(2*elements.length);
        }
        elements[pos] = item;
        pos++;
        num++;
        //StdOut.println(pos + " " + size + " " + num);
    }
    public T dequeue(){
        if (isEmpty())
            throw new RuntimeException("Queue underflow");
        if((pos) == (elements.length/4)){
            size = size / 2;
            resize(elements.length/2);
        }
        temp = elements[0];
        for(int i = 0; i < num-1; i++){
            elements[i] = elements[i+1];
        }
        pos--;
        num--;
        return temp;
    }
    public T peek(){
        temp = elements[0];
        return temp;
    }
    public T lookup(int i){
        if(i <= num){
            temp = elements[i-1];
            return temp;
        }else{
            throw new RuntimeException((i)+"th element is not available!");
        }
    }
    public Iterator<T> iterator(){
        return new OrderIterator();
    }
    public class OrderIterator implements Iterator<T> {
        public int i=0;
        public boolean hasNext(){
            if(elements[i+1] != null)
                return true;
            else
                return false;
        }
        public void remove(){
            throw new UnsupportedOperationException();
        }
        public T next(){
            if(!hasNext())
                throw new NoSuchElementException();
            T ele = elements[i];
            i = i+1;
            return ele;
        }
        
    }
    public void resize(int size){
		a = (T[])new Object[size];
		for(int i=0; i < num; i++)
			a[i] = elements[i];
		elements = a;
    }
    
    public static void main(String[] args){
        MyQueue<String> queue = new MyQueue<String>();
        queue.elements = new String[size];
        queue.temp = new String();
        queue.temp = null;
        String s = "";
        while(!StdIn.isEmpty()){
            String next = StdIn.readString();
            if(next.equals("*")){
                String peekedElement = queue.peek();
                StdOut.print(peekedElement + " ");
            }else if(next.equals("-")){
                String dequeuedElement = queue.dequeue();
                StdOut.print(dequeuedElement + " ");
            }else if(next.equals("?")){
                s = StdIn.readString();
                int i = Integer.parseInt(s);
                String lookedElement = queue.lookup(i);
                StdOut.print(lookedElement + " ");
            }else{
                queue.enqueue(next);
            }
        }
        StdOut.println("\n" + num);
    }
        
}