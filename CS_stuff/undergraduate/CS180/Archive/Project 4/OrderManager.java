import project4.*;
import project4.ILinkedList.OrderIndexOutOfBoundsException;


public class OrderManager extends OrderList{

	private LinkedList<Order> List;
	private int MaxDist;
	private int MaxSeats;

	public OrderManager()
	{
		List = new LinkedList<Order>();
		MaxDist = 20;
		MaxSeats = 20;
	}
	
	public OrderManager(int MaxDist, int MaxSeats)
	{
		List = new LinkedList<Order>();
		this.MaxDist = MaxDist;
		this.MaxSeats = MaxSeats;
	}
	
	public void addOrder(Order order, int orderType, int dist, int seats)
			throws UnAcceptanceOrderException {

		if(orderType == Order.TAKE_OUT_ORDER_TYPE)
		{
			List.insertTail(order);
		}
		
		if(orderType == Order.DELIVERED_ORDER_TYPE)
		{
			if(dist>MaxDist)
			{
				throw new UnAcceptanceOrderException();
			}
			
			List.insertTail(order);
			
		}
		
		if(orderType == Order.DINE_IN_ORDER_TYPE)
		{
			if(seats>MaxSeats)
			{
				throw new UnAcceptanceOrderException();
			}
			
			List.insertTail(order);
		}
		
	}


	public Order getOrder(int index) throws OrderIndexOutOfBoundsException {
		
		if(List.size()< index+1)
		{
			throw new OrderIndexOutOfBoundsException();
		}
		
		return (Order) List.get(index);
	}


	public Order[] getOrderList() throws NoOrderException {
			
		if(List.isEmpty())
		{
			throw new NoOrderException();
		}
		
		
		Order[] orderlist = new Order[List.size()];
		
		for(int i=0; i<List.size(); i++)
		{
			try {
				orderlist[i] = (Order) List.get(i);
			} catch (OrderIndexOutOfBoundsException e) {

				e.printStackTrace();
			}
		}
		
		return orderlist;
	}


	public boolean isEmpty() {
		
		if(List.isEmpty())
		{
			return true;
		}
		
		return false;
	}


	public Order removeOrder(int index) throws OrderIndexOutOfBoundsException {
		
		return (Order) List.remove(index);
	}


	public int size() {

		return List.size();
	}	
}
