public class Node
{
	private int val;
	private Node leftLink;
	private Node rightLink;
    
    public Node(int val, Node leftLink, Node rightLink)
    {
    	this.val=val;
    	this.leftLink=leftLink;
    	this.rightLink=rightLink;
    }
    
    public Node getLeftLink()
    {
    	return leftLink;
    }
    
    public Node getRightLink()
    {
    	return rightLink;
    }
    
    public int getValue()
    {
    	return val;
    }
    
    public void setLeftLink(Node l)
    {
    	leftLink = l;
    }
    
    public void setRightLink(Node r)
    {
    	rightLink = r;
    }
}