import java.awt.*;

/**
 * Centipede direction, length and its segments
 * 
 * @author James Wilkinson <jhwilkin@purdue.edu>
 * @version 1.7
 * @since 2011-11-20
 **/
public class Centipede {
	/** Array of the centipede's body segments **/
	public Point segments[];

	/** Centipede head's horizontal heading **/
	public int horizontal;

	/** Centipede body's vertical heading **/
	public int vertical;

	/** Number of segments left in the centipede **/
	public int length;

	/**
	 * @param inLength
	 *            Length of the centipede to create
	 * @param inHorizontal
	 *            Initial horizontal heading of the centipede head
	 * @param inVertical
	 *            Initial vertical heading of the centipede head
	 **/
	public Centipede(int inLength, int inHorizontal, int inVertical) {
		// TODO: Initialize length, horizontal and vertical with
		// TODO: passed parameters.
		this.length = inLength;
		this.horizontal = inHorizontal;
		this.vertical = inVertical;
		// TODO: Create the head segment of the Centipede.
		segments = new Point[inLength];
		segments[0] = new Point(0,0);
	}

	/**
	 * Returns the segment that matches that Point.
	 * 
	 * @param testLoc
	 *            Grid location
	 * @return int corresponding to the segment that is at <code>testLoc</code>
	 *         location. -1 if none match
	 */
	public int contains(Point testLoc) {
		// TODO: Find the segment that contains the Point testLoc and return
		// TODO: the int corresponding to that segment. -1 if no match.
		for (int i = 0; i < segments.length; i++)
			if (segments[i] != null)
				if (segments[i].x == testLoc.x & segments[i].y == testLoc.y)
					return i;
		return -1;
	}
}
