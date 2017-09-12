
import project3.Chef;
import project3.KitchenInterface;
import project3.Order;
import project3.OrderList;
import project3.Chef.NoOrderException;
import project3.OrderList.FullOrdersException;

public class Kitchen implements KitchenInterface{

	private OrderManager list;
	
	public Kitchen(int size)
	{
		list = new OrderManager(size);
	}
	
	@Override
	public Order cookNextOrder(Chef arg0) throws NoOrderException {
		
		return arg0.cookNextOrder(list);
	}

	@Override
	public OrderList getOrderList() {
		// TODO Auto-generated method stub
		return list;
	}

	@Override
	public void placeOrder(Order order) throws FullOrdersException {
		// TODO Auto-generated method stub
		
		list.addOrder(order);
	}
	
}
