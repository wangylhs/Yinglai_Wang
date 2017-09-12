/**
 * Project5Constants.java
 * A class centralizing all the constants you'll need in this project.
 */
 
// ? package project5;

import java.awt.Color;
import java.awt.Dimension;
 
public class Project5Constants
{
    /**
     * The square dimension of the canvas in pixels.
     */
    public static int GRID_SIZE = 800;
    /**
     * The width of a road in pixels.
     */
    public static int LANE_WIDTH = 50;
    /**
     * The width of the rendering of the roads in pixels.
     */
    public static int LINE_WIDTH = 2;
    /**
     * The length of one of the dashes in the roads in pixels.
     */
    public static int DASH_LENGTH = 5;
    /**
     * Size of the traffic lights.
     */
    public static int TRAFFIC_LIGHT_SIZE = 50;
    /**
     * Constant representing the current state of allowing traffic to travel
     * left-right.  This constant is the opposite of UP_DOWN_TRAFFIC and has the
     * same value as HORIZONTAL_HEADING.
     */
    public static int LEFT_RIGHT_TRAFFIC = -1;
    /**
     * Constant representing the current state of allowing traffic to travel
     * up-down.  This constant is the opposite of LEFT_RIGHT_TRAFFIC and has the
     * same value as VERTICAL_HEADING.
     */
    public static int UP_DOWN_TRAFFIC = 1;
    /**
     * Recommended dimensions for each car controller.
     */
    public static Dimension CAR_CONTROLLER_DIMENSION = new Dimension(185, 60);
    /**
     * Rate of movement of each car in pixels.
     */
    public static int MOVE_RATE = 2;
    /**
     * Default sleep rate of each car in milliseconds.
     */
    public static long DEFAULT_SLEEP_RATE = 100;
    /**
     * Width of each car in pixels.
     */
    public static int CAR_WIDTH = 30;
    /**
     * Length of each car in pixels.
     */
    public static int CAR_LENGTH = 50;
    /**
     * Constant to define a car heading left-right.  This constant is the
     * opposite of VERTICAL_HEADING and has the same value as
     * LEFT_RIGHT_TRAFFIC.
     */
    public static int HORIZONTAL_HEADING = -1;
    /**
     * Constant to define a car heading up-down.  This constant is the opposite
     * of HORIZONTAL_HEADING and has the same value as UP_DOWN_TRAFFIC.
     */
    public static int VERTICAL_HEADING = 1;
    /**
     * One of 4 possible starting positions of the cars.
     */
    public static int CAR_START_POSITION_LEFT   = 0;
    /**
     * One of 4 possible starting positions of the cars.
     */
    public static int CAR_START_POSITION_RIGHT  = 1;
    /**
     * One of 4 possible starting positions of the cars.
     */
    public static int CAR_START_POSITION_TOP    = 2;
    /**
     * One of 4 possible starting positions of the cars.
     */
    public static int CAR_START_POSITION_BOTTOM = 3;
    /**
     * 4x2 array of move multipliers for the four possible moving directions,
     * in order, right, left, down, up.
     */
    public static int[][] CAR_MOVE_DIRECTIONS =
        {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    /**
     * 4x2 array of pixel start positions, in order, the left, right, up, and
     * down start positions.
     */
    public static int[][] CAR_START_POSITIONS = {
        {Project5Constants.CAR_LENGTH/2,
         Project5Constants.GRID_SIZE/2+Project5Constants.LANE_WIDTH/2},
        {Project5Constants.GRID_SIZE-Project5Constants.CAR_LENGTH/2,
         Project5Constants.GRID_SIZE/2-Project5Constants.LANE_WIDTH/2},
        {Project5Constants.GRID_SIZE/2-Project5Constants.LANE_WIDTH/2,
         Project5Constants.CAR_LENGTH/2},
        {Project5Constants.GRID_SIZE/2+Project5Constants.LANE_WIDTH/2,
         Project5Constants.GRID_SIZE-Project5Constants.CAR_LENGTH/2}
    };
    /**
     * Array holding the four possible colors of the cars.
     */
    public static Color[] CAR_COLORS =
        {Color.cyan, Color.magenta, Color.yellow, Color.gray};
}