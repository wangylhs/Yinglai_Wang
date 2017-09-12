import java.util.*;
import java.lang.*;

public class chapter3 {
	
	abstract class Animal{
		private int order;
		protected String name;
		public Animal(String n){
			name = n;
		}
		public void setOrder(int ord){
			order = ord;
		}
		public int getOrder(){
			return order;
		}
		public boolean isOlderThan(Animal a){
			if(this.order<a.getOrder()) return true;
			else return false;
		}
	}
	public class Dog extends Animal{
		public Dog(String n){
			super(n);
		}
	}
	public class Cat extends Animal{
		public Cat(String n){
			super(n);
		}
	}
	
	class AnimalQueue{
		LinkedList<Dog> dogs = new LinkedList<Dog>();
		LinkedList<Cat> cats = new LinkedList<Cat>();
		private int order = 0;
		public void enqueue(Animal a){
			a.setOrder(order);
			order++;
			if(a instanceof Dog){
				dogs.addLast((Dog)a);
			}
			if(a instanceof Cat){
				cats.addLast((Cat)a);
			}
		}
		public Animal dequeueAny(){
			if(dogs.size()==0){
				return dequeueCat();
			}else if(cats.size()==0){
				return dequeueDog();
			}
			Dog dog = dogs.peek();
			Cat cat = cats.peek();
			if(dog.isOlderThan(cat)){
				return dequeueDog();
			}else{
				return dequeueCat();
			}
			
		}
		
		public Dog dequeueDog(){
			return dogs.poll();
		}
		public Cat dequeueCat(){
			return cats.poll();
		}
	}
	
	public static void sort(Stack<Integer> s){
		Stack<Integer> r = new Stack<Integer>();
		while(!s.isEmpty()){
			int temp = s.pop();
			while(!r.isEmpty()&&r.peek()>temp){
				s.push(r.pop());
			}
			r.push(temp);
		}
		while(!r.isEmpty()) s.push(r.pop());
	}
	
	
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
		/*StackWithMin swm = new StackWithMin();
		swm.push(1);
		swm.push(2);
		swm.push(3);
		System.out.println(swm.min());*/
		/*SetOfStacks sos = new SetOfStacks();
		for(int i=0;i<30;i++) sos.push(1);
		for(int i=0;i<30;i++) System.out.println(i+" "+sos.pop());
		
		MyQueue q = new MyQueue();
		q.add(1);
		q.add(2);
		q.add(3);
		while(q.size()>0) System.out.println(q.remove());
		
		Stack<Integer> s = new Stack<Integer>();
		s.push(8);
		s.push(12);
		s.push(10);
		s.push(7);
		sort(s);
		while(!s.isEmpty()) System.out.println(s.pop());
		*/
		chapter3 c3 = new chapter3();
		chapter3.AnimalQueue aq = c3.new AnimalQueue();
		for(int i=0;i<10;i++){
			String d = "dog"+Integer.toString(i);
			String c = "cat"+Integer.toString(i);
			chapter3.Dog dog = c3.new Dog(d);
			chapter3.Cat cat = c3.new Cat(c);
			aq.enqueue(dog);
			aq.enqueue(cat);
		}
		System.out.println(aq.dequeueAny());
		System.out.println(aq.dequeueDog());
		
	}
}

