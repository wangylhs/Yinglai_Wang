import project4.*;
import project4.ILinkedList.OrderIndexOutOfBoundsException;
import project4.OrderList.NoOrderException;

public class Kitchen implements IKitchen
{

	private LinkedList<Chef> List;
	
	public Kitchen()
	{
		List = new LinkedList<Chef>();
	}
	
	
	public void addChef(project4.Chef chef) {
	
		List.insertTail(chef);
			
	}

	@Override
	public project4.Order cookNextOrder(project4.OrderList idx)
			throws project4.OrderList.NoOrderException, NoChefException {
		
		int Score;
		int index=0;
		
		if(List.isEmpty())
		{
			throw new NoChefException();
		}
		
		Chef chef = getCurrentChef();
		Order o = chef.cookNextOrder(idx);
		
		System.out.println("Before");
		List.print();
		
		Score = this.removeChef().getCreditScore();
		System.out.println("After");
		
		List.print();
		
		try {
			
			for(int i=0; i<List.size(); i++)
			{
				if(Score > ((Chef)List.get(i)).getCreditScore())
				{
					index++;
				}	
			}
			System.out.println("After After");	
			List.insert(chef, index);
		} catch (OrderIndexOutOfBoundsException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		List.print();
		return o;
	}

	
	public project4.Chef[] getChefs() throws NoChefException {
		
		if(List.isEmpty())
		{
			throw new NoChefException();
		}
		
		
		Chef[] cheflist = new Chef[List.size()];
		
		for(int i=0; i<List.size(); i++)
		{
			try {
				cheflist[i] = (Chef) List.get(i);
			} catch (OrderIndexOutOfBoundsException e) {

				e.printStackTrace();
			}
		}
		
		return cheflist;
	}


	public project4.Chef getCurrentChef() throws NoChefException {
		try {
			return (Chef) List.get(0);
		} catch (OrderIndexOutOfBoundsException e) {
			throw new NoChefException();
		}
	}

	@Override
	public project4.Chef removeChef() throws NoChefException {
		
		try {
			return (Chef) List.remove(0);
		} catch (OrderIndexOutOfBoundsException e) {
			throw new NoChefException();
		}
	}

}