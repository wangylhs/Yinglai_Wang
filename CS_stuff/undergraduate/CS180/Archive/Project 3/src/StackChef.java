import project3.BurgerJoint;
import project3.Chef;
import project3.Order;
import project3.OrderList;
import project3.OrderList.OrderIndexOutOfBoundsException;

public class StackChef implements Chef{

	BurgerJoint Bjoint;
	
	
	public Order cookNextOrder(OrderList list) throws NoOrderException {
	
		try
		{
			return list.removeOrder(list.size()-1);
		}
		
		catch(OrderIndexOutOfBoundsException e)
		{
			Bjoint.updateGuiText("Error: Index is out of bound !");
			e.printStackTrace();
			throw new NoOrderException();
		}
	}
	
	public void setBurgerJoint(BurgerJoint bjoint) {
		
		Bjoint = bjoint;
	}
	
	
}
