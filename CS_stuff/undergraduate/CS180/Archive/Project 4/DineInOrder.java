
import project4.Order;

public class DineInOrder extends Order {

	private int Seats;
	public DineInOrder(int numHamburgers, int numCheeseburgers, int numFries, int numSeats)
			throws NegativeOrderException {
		super(numHamburgers, numCheeseburgers, numFries);
		// TODO Auto-generated constructor stub
		
		Seats = numSeats;
	}
	
	public String toString()
	{
		return (numHamburgers + " hamburgers, " + 
		numCheeseburgers + " Cheeseburgers, and " + numFries + 
		" fries (value=" + getOrderValue() + ") DINE-IN (#seats=" + Seats + ")"); 
	}
}
