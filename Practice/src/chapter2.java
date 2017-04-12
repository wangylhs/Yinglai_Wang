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
	
	static Node kthToLast(Node head, int k){
		Node p1 = head;
		Node p2 = head;
		for(int i=0; i<k; i++){
			if(p1==null) return null;
			p1=p1.next;
		}
		
		while(p1!=null){
			p1=p1.next;
			p2=p2.next;
		}
		return p2;
	}
	
	static void deleteNode(Node n){
		if(n==null || n.next==null){
			System.out.println("Error");
			System.exit(0);
		}
		Node temp = n.next;
		n.data = temp.data;
		n.next = temp.next;
	}
	
	static Node partition(Node node, int x){
		Node head = node;
		Node tail = node;
		while(node!=null){
			Node next = node.next;
			if(node.data < x){
				node.next = head;
				head = node;
			}else{
				tail.next = node;
				tail = node;
			}
			node = next;
		}
		tail.next = null;
		
		return head;
	}
	
	static Node addList_reverse(Node n1, Node n2){
		Node node = new Node(0);
		int value=0;
		int carry = 0;
		Node head = node;
		while(n1!=null || n2!=null){
			value = 0;
			if(carry>0){
				value += carry;
				carry = 0;
			}
			if(n1==null) value += n2.data;
			else if(n2==null) value += n1.data;
			else value += (n1.data + n2.data);
			if(value >= 10){
				carry = 1;
				node.data = value%10;
			}else{
				node.data = value;
			}
			if(n1!=null && n2==null){
				if(n1.next!=null){
					node.next = new Node(0);
					node = node.next;
				}
			}else if(n1==null && n2!=null){
				if(n2.next!=null){
					node.next = new Node(0);
					node = node.next;
				}
			}else{
				node.next = new Node(0);
				node = node.next;
			}
			if(n1!=null) n1 = n1.next;
			if(n2!=null) n2 = n2.next;
		}
		
		
		return head;
	}
	
	static Node insertBefore(Node node, int data){
		Node n = new Node(data);
		if(node!=null) n.next = node;
		return n;
	}
	static int list_length(Node n){
		int i=0;
		while(n!=null){
			i++;
			n = n.next;
		}
		return i;
	}
	static Node PadList(Node l, int pad_size){
		int i;
		Node head=l;
		for(i=0;i<pad_size;i++){
			head = insertBefore(head,0);
		}
		return head;
		
	}
	static class Sum{
		public Node sum = null;
		public int carry = 0;
	}
	static Sum addList_helper(Node l1, Node l2){
		if(l1==null && l2==null){
			//base case
			Sum s = new Sum();
			return s;
		}
		Sum s = addList_helper(l1.next,l2.next);
		int value = s.carry + l1.data + l2.data;
		Node node = insertBefore(s.sum,value%10);
		s.sum = node;
		s.carry = value/10;
		return s;
		
	}
	
	static Node addList_forward(Node l1, Node l2){
		int len1 = list_length(l1);
		int len2 = list_length(l2);
		if(len1>len2) l2 = PadList(l2,len1-len2);
		else l1 = PadList(l1,len2-len1);
		PrintList(l1);
		PrintList(l2);
		Sum s = addList_helper(l1,l2);
		if(s.carry==0){
			return s.sum;
		}else{
			Node ret = insertBefore(s.sum,s.carry);
			return ret;
		}
	}
	
	
	static void PrintList(Node node){
		while(node!=null){
			if(node.next==null) System.out.print(node.data + "\n");
			else System.out.print(node.data + " -> ");
			node=node.next;
		}
	}
	
	public static void main(String args[]){
		/*LinkedList<Integer> list = new LinkedList<Integer>();
		
		list.add(1);
		list.add(2);
		list.add(3);
		*/
		Node list = new Node(3);
		list.appendToTail(5);
		list.appendToTail(8);
		list.appendToTail(5);
		list.appendToTail(10);
		list.appendToTail(2);
		list.appendToTail(1);
		//deleteDups(list);
		//Node n = kthToLast(list,4);
		/*Node n=list;
		for(int i=0;i<3;i++){
			n=n.next;
		}
		deleteNode(n);
		*/
		//PrintList(list);
		//list = partition(list,5);
		//PrintList(list);
		Node list1 = new Node(1);
		list1.appendToTail(2);
		list1.appendToTail(3);
		list1.appendToTail(4);
		Node list2 = new Node(5);
		list2.appendToTail(6);
		//list2.appendToTail(7);
		PrintList(list1);
		PrintList(list2);
		PrintList(addList_reverse(list1,list2));
		PrintList(addList_forward(list1,list2));
	}	
}
