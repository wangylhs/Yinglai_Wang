/**
 * Project3.java
 * the driver class for your program
 */
 
import project3.BurgerJoint;
import project3.Chef;
 
 public class main
 {
    public static void main(String[] args)
    {
        // default order list size - you can change this number during your own
        // testing of your program
        int orderListSize = 5;
        if (args.length == 1)
        {
            try
            {
                orderListSize = Integer.parseInt(args[0]);
            }
            catch (NumberFormatException e)
            {
                e.printStackTrace();
            }
        }
        // create the burger joint
        BurgerJoint burgerJoint = new BurgerJoint();
        // create the kitchen
        burgerJoint.setKitchen(new Kitchen(orderListSize));
        // create the 3 chefs
        Chef queueChef = new QueueChef();
        queueChef.setBurgerJoint(burgerJoint);
        Chef stackChef = new StackChef();
        stackChef.setBurgerJoint(burgerJoint);
        Chef valueChef = new ValueChef();
        valueChef.setBurgerJoint(burgerJoint);
        burgerJoint.setQueueChef(queueChef);
        burgerJoint.setStackChef(stackChef);
        burgerJoint.setValueChef(valueChef);
        // create and show the GUI
        burgerJoint.createAndShowGUI();
    }
 }