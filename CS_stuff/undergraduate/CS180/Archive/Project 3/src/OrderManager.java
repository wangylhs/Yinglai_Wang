import project3.Order;
import project3.OrderList;
import project3.Order.NegativeOrderException;
import project3.OrderList.FullOrdersException;
public class OrderManager implements OrderList{

	private Order[] orders;
	private int size;
	private int capacity;
	
	public OrderManager(){
		orders=new Order[5];
		size=0;
		capacity=5;
	}
	
	public OrderManager(int N){
		orders=new Order[N];
		size=0;
		capacity=N;
	}
	@Override
	public void addOrder(Order arg0) throws FullOrdersException {
		// TODO Auto-generated method stub
		
		if(size==capacity)
		{
			throw new OrderList.FullOrdersException();
		}
		
		try {
			orders[size]=new Order(arg0.getNumCheeseburgers(),arg0.getNumFries(),arg0.getNumHamburgers());
			orders[size].setNumCheeseburgers(arg0.getNumCheeseburgers());
			orders[size].setNumFries(arg0.getNumFries());
			orders[size].setNumHamburgers(arg0.getNumHamburgers());
			size++;
		} catch (NegativeOrderException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public int capacity() {
		// TODO Auto-generated method stub
		return capacity;
	}

	@Override
	public Order getOrder(int arg0) throws OrderIndexOutOfBoundsException {
		// TODO Auto-generated method stub
		if(arg0<size && arg0>=0)
			return orders[arg0];
		throw new OrderList.OrderIndexOutOfBoundsException();
	}

	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		if(size==0)
			return true;
		return false;
	}

	@Override
	public Order removeOrder(int arg0) throws OrderIndexOutOfBoundsException {
		// TODO Auto-generated method stub
		
		
		if(arg0>size && arg0<0)
			throw new OrderList.OrderIndexOutOfBoundsException();		
		Order o = null;
		
		try {
			o = new Order(orders[arg0].getNumHamburgers(),orders[arg0].getNumCheeseburgers(),orders[arg0].getNumFries());
			
			for(int i=arg0; i<size-1; i++)
			{
				orders[i].setNumCheeseburgers(orders[i+1].getNumCheeseburgers());
				orders[i].setNumFries(orders[i+1].getNumFries());
				orders[i].setNumHamburgers(orders[i+1].getNumHamburgers());
			}

			size--;
		} catch (NegativeOrderException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return o;
	}

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return size;
	}

}
