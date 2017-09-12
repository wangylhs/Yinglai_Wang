import java.awt.*;

/**
 * Holds information about the player's ship and handles firing of projectiles
 * 
 * @author James Wilkinson <jhwilkin@purdue.edu>
 * @version 1.7
 * @since 2011-11-20
 **/
public class Ship {
	/** Position that the ship is trying to move into **/
	public Point tryLoc;
	/** Actual position of the ship **/
	public Point loc;
	public boolean con = false;
	/** Number of lives that the ship has **/
	public int lives;
	private long time;
	/** Used by the super laser. True if firing. **/
	public boolean firing;

	/** Time (ms) left for the ship to be invulnerable **/
	public int invulnerableTime;

	/** Array of projectiles **/
	private Point myProjectiles[];

	/** Time (ms) left for the ship to be invulnerable **/
	private GameSounds myGameSounds;

	/**
	 * @param inGameSounds
	 *            Used to generate sound when ship fires
	 * @param inProjectiles
	 *            Used to create new projectiles
	 **/
	public Ship(GameSounds inGameSounds, Point inProjectiles[]) {
		// TODO: Initialize myProjectiles and myGameSounds with the
		// TODO: passed parameters.
		this.myGameSounds = inGameSounds;
		this.myProjectiles = inProjectiles;
		// TODO: Set the loc of the ship to (Settings.shipStartLoc.x,
		// Settings.shipStartLoc.y)
		loc = new Point(Settings.shipStartLoc.x, Settings.shipStartLoc.y);
		// TODO: Set tryLoc to the same location as the ship's starting
		// position.
		tryLoc = new Point(Settings.shipStartLoc.x, Settings.shipStartLoc.y);
		// TODO: Set the ship's lives to Settings.startLives
		lives = Settings.startLives;
		this.firing = Settings.superLaser;
		// TODO: Initialize invulnerableTime to 0.
		invulnerableTime = 0;
	}

	/**
	 * Try to fire a projectile from the ship
	 * 
	 * Fires a projectile from the ship if the ship is not invulnerable and
	 * there are less than Settings.maxProjectiles projectiles.
	 **/
	public void fire() {
		// TODO: Write code to implement the description above.
		// TODO: Make sure to play the appropriate sound effect if the ship
		// fires.
		int existProjectiles = 0;
		for (int i = 0; i < myProjectiles.length; i++)
			if (myProjectiles[i] != null)
				existProjectiles++;
		if (firing) {
			while (con) {
				if (Settings.maxProjectiles > existProjectiles) {
					for (int i = 0; i < myProjectiles.length; i++)
						if (System.currentTimeMillis() > (time + Settings.superLaserDelay))
							if (myProjectiles[i] == null&con==true) {
								myProjectiles[i] = new Point(loc.x + 9,
										loc.y - 1);
								time = System.currentTimeMillis();
								System.out.println("asdasdas");
								myGameSounds.laser();
								break;
							}
				}
			}
		} else {
			if (Settings.maxProjectiles > existProjectiles)
				for (int i = 0; i < myProjectiles.length; i++) {
					if (myProjectiles[i] == null) {
						myProjectiles[i] = new Point(loc.x + 9, loc.y - 3);
						myGameSounds.cannon();
						break;
					}
				}
		}
	}
}
