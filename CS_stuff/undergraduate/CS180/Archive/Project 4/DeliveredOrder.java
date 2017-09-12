import project4.Order;

public class DeliveredOrder extends Order{

	private int Distance;
	
	public DeliveredOrder(int numHamburgers, int numCheeseburgers, int numFries, int dist)
			throws NegativeOrderException {
		super(numHamburgers, numCheeseburgers, numFries);
		// TODO Auto-generated constructor stub
		Distance = dist;
	}

	public String toString()
	{
		return (numHamburgers + " hamburgers, " + 
		numCheeseburgers + " Cheeseburgers, and " + numFries + 
		" fries (value=" + getOrderValue() + ") DELIVERED (#distance=" + Distance + ")"); 
	}
	

}
