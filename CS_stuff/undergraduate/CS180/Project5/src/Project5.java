import java.awt.Point;

/**
 * CS 180 - Project 5: Variation of classic Centipede arcade game
 * 
 * @author James Wilkinson <jhwilkin@purdue.edu>
 * @version 1.6
 * @since 2011-08-08
 **/
public class Project5 {
	/** Plays sounds **/
	private GameSounds myGameSounds;

	/** Handles high scores **/
	private HighScores myHighScores;

	/** Displays main game screen and handle mouse input **/
	private GameCanvas myGameCanvas;

	/** Handles game logic **/
	private GameLogic myGameLogic;

	/** Frame with menu **/
	private Frame myFrame;

	/** Array of mushrooms **/
	private Mushroom myMushrooms[][];

	/** Array of centipedes **/
	private Centipede myCentipedes[];

	/** Player's ship **/
	private Ship myShip;

	/** Array of projectiles **/
	private Point myProjectiles[];

	/**
	 * Starts the program
	 * 
	 * @param args
	 *            Array of input strings. Not used.
	 **/
	public static void main(String[] args) {
		new Project5();
	}

	public Project5() {
		// TODO: Create new objects myGameSounds, myHighScores, myMushrooms,
		myGameSounds = new GameSounds();
		myHighScores = new HighScores();
		myMushrooms = new Mushroom[Settings.width][Settings.height];
		// TODO: myProjectiles, myShip, myCentipedes, myGameCanvas, myGameLogic,
		// myFrame
		myProjectiles = new Point[Settings.maxProjectiles];
		myCentipedes = new Centipede[Settings.centipedeStartSize];
		myShip = new Ship(myGameSounds, myProjectiles);
		myGameCanvas = new GameCanvas(myGameSounds, myMushrooms, myCentipedes,
				myShip, myProjectiles);
		myGameLogic = new GameLogic(myGameSounds, myGameCanvas, myHighScores,
				myMushrooms, myCentipedes, myShip, myProjectiles);
		myFrame = new Frame(myGameLogic, myGameCanvas, myHighScores);
		// TODO: Set myGameCanvas.myGameLogic to myGameLogic
		myGameCanvas.myGameLogic = myGameLogic;
		// TODO: Set myHighScores.myFrame to myFrame
		myHighScores.myFrame = myFrame;
		// TODO: Set myGameLogic.syncReset to true
		myGameLogic.syncReset = true;
		// TODO: Start myGameLogic and then wait for it to join
		myGameLogic.start();
		try {
			myGameLogic.join();
		} catch (Exception e) {
		}
	}
}
