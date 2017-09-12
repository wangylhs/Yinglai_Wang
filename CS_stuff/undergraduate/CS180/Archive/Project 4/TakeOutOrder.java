
import project4.Order; 

public class TakeOutOrder extends Order {

	public TakeOutOrder(int numHamburgers, int numCheeseburgers, int numFries)
			throws NegativeOrderException {
		super(numHamburgers, numCheeseburgers, numFries);
		// TODO Auto-generated constructor stub
	}

	public String toString()
	{
		return (numHamburgers + " hamburgers, " + 
		numCheeseburgers + " Cheeseburgers, and " + numFries + 
		" fries (value=" + getOrderValue() + ") TAKE-OUT"); 
	}
}
