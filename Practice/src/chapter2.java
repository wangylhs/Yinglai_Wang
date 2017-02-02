import java.util.*;



class Node{
	Node next = null;
	int data;
	
	public Node(int data){
		this.data = data;
	}
	
	void appendToTail(int data){
		Node end = new Node(data);
		Node n = this;
		while(n.next != null){
			n = n.next;
		}
		n.next = end;
	}
	
	Node deleteNode(Node head, int d){
		Node n = head;
		if(n.data==d){
			return head.next;
		}
		while(n.next!=null){
			if(n.next.data==d){
				n.next=n.next.next;
				return head;
			}
			n=n.next;
		}
		return head;
	}
}


public class chapter2 {
	static void deleteDups(Node n){
		HashSet<Integer> set = new HashSet<Integer>();
		Node prev = null;
		while(n!=null){
			if(set.contains(n.data)){
				prev.next=n.next;
			}else{
				prev=n;
				set.add(n.data);
			}
			n=n.next;
		}
	}
	public static void main(String args[]){
		/*LinkedList<Integer> list = new LinkedList<Integer>();
		
		list.add(1);
		list.add(2);
		list.add(3);
		*/
		Node list = new Node(1);
		list.appendToTail(2);
		list.appendToTail(1);
		list.appendToTail(3);
		list.appendToTail(4);
		list.appendToTail(5);
		list.appendToTail(1);
		deleteDups(list);
		
		while(list!=null){
			System.out.println(list.data);
			list=list.next;
		}
		
	}	
}
