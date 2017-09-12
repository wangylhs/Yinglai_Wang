
import project3.BurgerJoint;
import project3.Chef;
import project3.Order;
import project3.OrderList;
import project3.OrderList.OrderIndexOutOfBoundsException;


public class ValueChef implements Chef{

	BurgerJoint Bjoint;
	
	public Order cookNextOrder(OrderList list) throws NoOrderException {
		
		int MaxIndex = 0;
		int MaxValue = 0;
		
		try
		{
			for(int i=0; i<list.size(); i++)
			{
				if(MaxValue < list.getOrder(i).getOrderValue())
				{
					MaxValue = list.getOrder(i).getOrderValue();
					MaxIndex = i;
				}
			}
			return list.removeOrder(MaxIndex);			
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
