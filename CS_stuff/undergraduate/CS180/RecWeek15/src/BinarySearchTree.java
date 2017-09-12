public class BinarySearchTree
{
	private Node root;
    
    public void addNode(Node v)
    {
    	if(root == null)
    		root = v;
    	else if(v.getValue() < root.getValue())
    	{
    		if(root.getLeftLink() != null)
    			addNode(v, root.getLeftLink());
    		else
    			root.setLeftLink(v);
    	}

    	else if(v.getValue() > root.getValue())
    	{
    		if(root.getRightLink() != null)
    			addNode(v, root.getRightLink());	
    		else
    			root.setRightLink(v);
    	}
    }
    
    public void addNode(Node n, Node r)
    {
    	if(n.getValue() < r.getValue())
    	{
    		if(root.getLeftLink() != null)
    			addNode(n, r.getLeftLink());
    		else
    			r.setLeftLink(n);
    	}

    	else if(n.getValue() > r.getValue())
    	{
    		if(r.getRightLink() != null)
    			addNode(n, r.getRightLink());	
    		else
    			r.setRightLink(n);
    	}
    }
    
    public void traverse()
    {
    	if(root==null)
    		return;
    	else
    		traverse(root);
    }
    
    public void traverse(Node r)
    {
		if(r==null)
			return;
		traverse(r.getLeftLink());
		System.out.print(r.getValue() + " ");
		traverse(r.getRightLink());
    }
    
    public static void main(String args[])
    {
    	BinarySearchTree t = new BinarySearchTree();
    	t.addNode(new Node(15, null, null));
    	t.addNode(new Node(8, null, null));
    	t.addNode(new Node(17, null, null));
    	t.traverse();
    }
}