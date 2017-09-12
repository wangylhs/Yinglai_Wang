/**
 * Project4.java
 * the driver class for your program
 * Put your name, recitation here
 */

import project4.BurgerJoint;
 
 public class Project4
 {
    public static void main(String[] args)
    {
        // create the burger joint
        BurgerJoint burgerJoint = new BurgerJoint();
        // create the kitchen
        burgerJoint.setKitchen(new Kitchen());
        burgerJoint.setOrderList(new OrderManager());
        // create and show the GUI
        burgerJoint.createAndShowGUI();
    }
 }