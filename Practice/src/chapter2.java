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
	
	static Node reverse_copy(Node node){
		Node head = null;
		while(node!=null){
			Node n = new Node(node.data);
			n.next = head;
			head = n;
			node = node.next;
		}
		return head;
	}
	
	static boolean check_palindrome(Node node){
		Node r_node = reverse_copy(node);
		while(node!=null){
			if(node.data!=r_node.data){
				return false;
			}
			node=node.next;
			r_node=r_node.next;
		}
		return true;
		
	}
	
	static Node find_intersection(Node list1, Node list2){
		int len1 = list_length(list1);
		int len2 = list_length(list2);
		Node longer, shorter;
		int diff = Math.abs(len1-len2);
		if(len1<len2){
			shorter = list1;
			longer = list2;
		}else{
			shorter = list2;
			longer = list1;
		}
		//check tail
		Node tail1=list1;
		Node tail2=list2;
		while(tail1.next!=null){
			tail1=tail1.next;
		}
		while(tail2.next!=null){
			tail2=tail2.next;
		}
		if(tail1.data!=tail2.data){
			return null;
		}
		
		for(int i=0;i<diff;i++){
			longer = longer.next;
		}
		PrintList(longer);
		PrintList(shorter);
		while(longer.data!=shorter.data){
			longer = longer.next;
			shorter = shorter.next;
		}
		return longer;
		
	}
	
	static Node find_loop_start(Node list){
		Node fast = list;
		Node slow = list;
		while(fast!=null && fast.next!=null){
			fast=fast.next.next;
			slow=slow.next;
			if(fast==slow) break;
		}
		if(fast==null || fast.next==null) return null;
		//fast stay, slow moves from start
		//fast and slow moves 1 step at a time until they meet
		slow=list;
		while(slow!=fast){
			slow=slow.next;
			fast=fast.next;
		}
		return slow;
		
	}
	
	static void PrintList(Node node){
		while(node!=null){
			if(node.next==null) System.out.print(node.data + "\n");
			else System.out.print(node.data + " -> ");
			node=node.next;
		}
	}
	
	public static void main(String args[]){
		
		Node list = new Node(0);
		list.appendToTail(1);
		list.appendToTail(2);
		list.appendToTail(1);
		list.appendToTail(0);
		//list.appendToTail(2);
		//list.appendToTail(1);
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
		list1.appendToTail(5);
		Node n1 = list1;
		Node n2 = list1;
		for(int i=0;i<2;i++){
			n1=n1.next;
		}
		while(n2.next!=null) n2=n2.next;
		n2.next = n1;
		Node list2 = new Node(5);
		list2.appendToTail(3);
		list2.appendToTail(4);
		list2.appendToTail(5);
		//list2.appendToTail(7);
		/*PrintList(list1);
		PrintList(list2);
		PrintList(addList_reverse(list1,list2));
		PrintList(addList_forward(list1,list2));
		
		PrintList(list);
		Node r_list = reverse_copy(list);
		PrintList(r_list);
		System.out.println(check_palindrome(list));
		*/
		//Node r = find_intersection(list1,list2);
		//PrintList(r);
		//PrintList(list1);
		Node res = find_loop_start(list1);
		System.out.println(res.data);
	}	
}
