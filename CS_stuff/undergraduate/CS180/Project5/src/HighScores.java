import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * Displays and updates high scores
 * 
 * @author  James Wilkinson <jhwilkin@purdue.edu>
 * @version 1.7
 * @since   2011-11-21
 **/
public class HighScores implements ActionListener{
    /** Used to display high scores and name prompt on the main frame **/
    public Frame myFrame;
    private String names[];    
    private int scores[];
    int count;
    
    JFrame f=new JFrame("High Scores");
	JPanel p=new JPanel();
    JLabel[] l = new JLabel[10];
	JButton b=new JButton("OK");
	
    public HighScores(){
    	//Initialize names[] and scores[] arrays. 
    	names=new String[Settings.numScores]; 
    	scores=new int[Settings.numScores];
    	
        // TODO: Check if the file named in Settings.highScoresFileName exists.
        boolean fileNotExist=false;
    	Scanner in=null;
    	PrintWriter out=null;
        File inFile=new File(Settings.highScoresFileName);
        try{
        	in=new Scanner(inFile);
        }catch(Exception e){
        	System.out.println("Sorry, the file 'highScores.txt' does not exist. We have created the file for you.");
        	fileNotExist=true;
        }
    	
    	// TODO: If it does not, create it with Settings.numScores entries of
        // TODO: name = nobody and score = 0.  If it does exist, load its contents
        // TODO: into the names and scores arrays.
        if(fileNotExist){
        	File outFile=new File(Settings.highScoresFileName);
        	try{
        		out=new PrintWriter(outFile);
        		for(int i=0; i<names.length; i++){
        			scores[i]=0;
        			names[i]="nobody";
        			out.println(scores[i]+" "+names[i]);
        		}
        	}catch(Exception e){}
        	
        	finally{
        		if(in!=null) in.close();
        		if(out!=null) out.close();
        	}
        }else{  
        	String[][] data=new String[Settings.numScores][2];
        	String s;
        	try{
        		in=new Scanner(inFile);
        		int i=0;
        		while(in.hasNextLine()){
        			s=in.nextLine();
        			data[i]=s.split(" ");
        			scores[i]=Integer.valueOf(data[i][0]);
        			names[i]=data[i][1];
        			i++;
        		}
        		
        		//In case the file has less than Settings.numScores names or scores.
        		while(i<Settings.numScores){
        			scores[i]=0;
        			names[i]="nobody";
        			i++;
        		}
        	}catch(Exception e){}
        	finally{
        		if(in!=null) in.close();
        	}
        }
        
        //create a graphic interface.(High Scores)
        f.setSize(500, 500);
    	f.setLayout(new GridLayout(11,1));
    	f.setVisible(false);
    	b.addActionListener(this);
    	
    	for(int i=0; i<Settings.numScores-count; i++){
    		l[i]= new JLabel();
    		f.add(l[i]);
    	}
    	f.add(p);
		p.add(b);
    }
    
    /**
     * Display high scores
     * 
     * @param name  Name of player to highlight
     * @param score Score of player to highlight
     **/
    public void showHighScores(String name, int score){
        // TODO: Display high scores and if an entry has the same name and
        // TODO: score as the passed parameters, highlight it with >>> <<<
    		for(int i=0; i<10; i++){
        		l[i].setText(names[i]+" - "+scores[i]);
        	}
    		if(name!=null){
    			l[Settings.numScores-count-1].setText(">>>" + names[Settings.numScores-count-1]+" - "+scores[Settings.numScores-count-1]+ "<<<");
    		}else{
    			l[Settings.numScores-count-1].setText(names[Settings.numScores-count-1]+" - "+scores[Settings.numScores-count-1]);
    		}
    		f.setVisible(true);
    		writeScores();
    }
    
    /**
     * Add score to high scores if greater than lowest high score
     * 
     * @param score Score to try to add
     **/
    public void addHighScore(String name, int score){
        // TODO: If the provided score is greater than the lowest high score,
        // TODO: then replace the lowest score with the new score and then
        // TODO: call the sortScores() method.
    	
    		scores[Settings.numScores-1]=score;
    		names[Settings.numScores-1]=name;
    		sortScores();
    		
    }
    
    public void checkScore(int score){
    	if(score>scores[Settings.numScores-1]){
    		String name = JOptionPane.showInputDialog("Congratulations! You have got a high score! Please input your name:");
    		addHighScore(name,score);
            showHighScores(name, score);
    	}
    }

    /**
     * Sort bottom score up to correct position in high scores table
     **/
    public void sortScores(){
        // TODO: Use a single round of bubble sort to bubble the last entry
        // TODO: in the high scores up to the correct location.
    	count=0;
    	for(int i=Settings.numScores-1; i>0;i--){
    		if(scores[i]>scores[i-1]){
    			int tempS;
    			tempS=scores[i];
    			scores[i]=scores[i-1];
    			scores[i-1]=tempS;
    			
    			String tempN;
    			tempN=names[i];
    			names[i]=names[i-1];
    			names[i-1]=tempN;
    			count++;
    		}
    	}
    }
    
    /**
     * Write scores to high scores file
     **/
    public void writeScores(){
        // TODO: Write the high scores data to the file name indicated
        // TODO: by Settings.highScoresFileName.
    	File outFile=new File(Settings.highScoresFileName);
    	PrintWriter out=null;
    	try{
    		out=new PrintWriter(outFile);
    		for(int i=0; i<Settings.numScores; i++){
    			out.println(scores[i]+" "+names[i]);
    		}
    	}catch(Exception e){}    	
    	finally{
    		if(out!=null) out.close();
        }
    }
    
	public void actionPerformed(ActionEvent e) {
		Object o=e.getSource();
		if(o==b){
			f.dispose();
		}
	}
}