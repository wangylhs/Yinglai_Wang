package chapter4;

import java.util.LinkedList;



class Graph{
	private Node[] nodes;
	int size;
	int index;
	int edges;
	
	public Graph(int size){
		this.size=size;
		nodes = new Node[size];
		this.index=0;
		this.edges=0;
	}
	
	void addNode(String name){
		nodes[index] = new Node(name);
		index++;
	}
	int getSize(){
		return index;
	}
	Node[] getNodes(){
		return nodes;
	}
	
	void connect(Node n1, Node n2){
		n1.adjacent.add(n2);
		n2.adjacent.add(n1);
		edges++;
	}

}

class Node{
	public String name;
	LinkedList<Node> adjacent;
	boolean visited;
	public Node(String name){
		this.name = name;
		this.visited = false;
		this.adjacent = new LinkedList<Node>();
	}
}



public class chapter4 {
	
	public static void main(String[] args){
		Graph g = new Graph(10);
		g.addNode("1");
		g.addNode("2");
		g.addNode("3");
		int size = g.getSize();
		Node[] nodes = g.getNodes();
		//System.out.println(size);
		g.connect(nodes[0],nodes[1]);
		//System.out.println(nodes[0].adjacent.get(0).name);
		/*for(int i=0;i<size;i++){
			System.out.println(nodes[i].name);
		}*/
	}
	
	
}
