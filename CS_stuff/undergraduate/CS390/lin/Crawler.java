import java.io.*;
import java.net.*;
import java.util.regex.*;
import java.sql.*;
import java.util.*;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;



public class Crawler
{
	Connection connection;
	int urlID;
	public Properties props;
    int maxurls;
    int NextURLID;
    int NextURLIDScanned;
    static String root;
	String domain = "cs.purdue.edu";
    int description_length = 100;

	Crawler() {
		urlID = 0;
	}

	public void readProperties() throws IOException {
      		props = new Properties();
      		FileInputStream in = new FileInputStream("database.properties");
      		props.load(in);
      		in.close();
	}

	public void openConnection() throws SQLException, IOException
	{
		String drivers = props.getProperty("jdbc.drivers");
      		if (drivers != null) System.setProperty("jdbc.drivers", drivers);

      		String url = props.getProperty("jdbc.url");
      		String username = props.getProperty("jdbc.username");
      		String password = props.getProperty("jdbc.password");

		connection = DriverManager.getConnection( url, username, password);
   	}

	public void createDB() throws SQLException, IOException {
		openConnection();

         	Statement stat = connection.createStatement();
		
		// Delete the table first if any
		try {
			stat.executeUpdate("DROP TABLE URLS");
		}
		catch (Exception e) {
		}
        
        try {
			stat.executeUpdate("DROP TABLE Words");
		}
		catch (Exception e) {
		}

			
		// Create the table
        	stat.executeUpdate("CREATE TABLE URLS (urlid INT, url VARCHAR(512), description VARCHAR(500))");
            stat.executeUpdate("CREATE TABLE Words (word VARCHAR(512), urlid INT)");
	}

	public boolean urlInDB(String urlFound) throws SQLException, IOException {
        Statement stat = connection.createStatement();
		ResultSet result = stat.executeQuery( "SELECT * FROM URLS WHERE url LIKE '"+urlFound+"'");

		if (result.next()) {
			return true;
		}
		return false;
	}

	public void insertURLInDB( String url) throws SQLException, IOException {
         	Statement stat = connection.createStatement();
		String query = "INSERT INTO urls VALUES ('"+NextURLID+"','"+url+"','')";
		stat.executeUpdate( query );
		urlID++;
	}
    public void insertWordInDB(String word, int urlidList) throws SQLException, IOException {
        Statement stat = connection.createStatement();
		String query = "INSERT INTO words VALUES ('"+word+"','"+urlidList+"')";
		stat.executeUpdate( query );
	}

    void startCrawl() {
        
        NextURLID = 0;
        NextURLIDScanned = 0;
        urlID = NextURLID;
        try{
            createDB();
            insertURLInDB(root);
            NextURLID++;
        }catch(Exception e){
            e.printStackTrace();
        }
        crawl();
    }
   
   void crawl(){
       try{
           Statement stmt = connection.createStatement();
           while (NextURLIDScanned < NextURLID && NextURLIDScanned<maxurls) {
                ResultSet results = stmt.executeQuery("SELECT * FROM urls WHERE urlid LIKE '"+NextURLIDScanned+"'");
               if(!results.next()){
                   NextURLIDScanned++;
                   continue;
               }
               String curUrl = results.getString(2);
               Document doc;
               String dscrpt;
               
               try{
                   doc = Jsoup.connect(curUrl).timeout(10000).followRedirects(true).get();
                   dscrpt = doc.text();
               }catch(Exception e){
                   NextURLIDScanned++;
                   continue;
               }

                //  Get the first 100 characters or less of the document from url1 without tags. Add this description to the URL record in the URL table.
               dscrpt = dscrpt.replaceAll("[']","");
               String dsp;
               if(dscrpt.length()>description_length){
                   dsp = dscrpt.substring(0,description_length);
               }
               else{
                   dsp = dscrpt.substring(0,dscrpt.length());
               }

               stmt.executeUpdate( "UPDATE urls SET description = '"+dsp+"' WHERE urlid LIKE '"+NextURLIDScanned+"'");

              
               if(NextURLID < maxurls){
                    Elements links = doc.select("a[href]");
                   for (Element link : links){
                       if(NextURLID >= maxurls)
                           break;
                       String urlFound = link.absUrl("href");
                       if(!textORhtml(urlFound))
                           continue;
                       if (NextURLID < maxurls && !urlInDB(urlFound)){
                           insertURLInDB(urlFound);
                           NextURLID++;
                       }
                   }
               }
                System.out.println("NextURLIDScanned:"+NextURLIDScanned+"\n, NextURLID:"+NextURLID);
               // Get the document in url1 without tags
               wordtable(dscrpt,NextURLIDScanned);

               NextURLIDScanned++;
               

           }
           
           }
           catch(Exception e){
               e.printStackTrace();
           }
       }
    public void wordtable(String dscrpt,int NextURLIDScanned)throws SQLException, IOException{
        String html = dscrpt.replaceAll("[^a-zA-Z\\s]","");
        List<String> wordList = Arrays.asList(html.split("\\s+"));
        Set<String> set = new HashSet<String>(wordList);
        for(String thisword : set){
        if(thisword.length()<256)
            insertWordInDB(thisword, NextURLIDScanned);
        }
    }

       public boolean textORhtml(String urlFound){
           if(urlFound.indexOf("cs.purdue")==-1) return false;
           if(urlFound.length()==0) return false;
           if(urlFound.indexOf("ftp")>=0) return false;
           if(urlFound.indexOf("mailto")>=0) return false;
           
           int index = urlFound.indexOf('#');
           if( index >= 0)
               urlFound = urlFound.substring(0, index);
           index = urlFound.lastIndexOf('.');
           if( index > 0){
               String suffix = urlFound.substring(index+1, urlFound.length());
               if (suffix.equals("pdf"))
                   return false;
               if(suffix.equals("shtml"))
                   return false;
               if(suffix.equals("pptx"))
                   return false;
               if(suffix.equals("jpg"))
                   return false;
               if(suffix.equals("gif") || suffix.equals("png") || suffix.equals("jpeg") || suffix.equals("bmp"))
                   return false;
               if(suffix.equals("mp3"))
                   return false;
               if(suffix.equals("au"))
                   return false;
               if(suffix.equals("lsl"))
                   return false;
               if(suffix.equals("PDF"))
                   return false;
               if(suffix.equals("doc"))
                   return false;
               if(suffix.equals("docx"))
                   return false;
               if(suffix.equals("txt"))
                   return false;
               if(suffix.equals("ppt"))
                   return false;
               if(suffix.equals("mp4")|| suffix.equals("avi") || suffix.equals("mpg") || suffix.equals("wmv") || suffix.equals("flv")|| suffix.equals("mov"))
                   return false;
               if(suffix.equals("xz"))
                   return false;
               if(suffix.equals("bz2"))
                   return false;
               if(suffix.equals("ps"))
                   return false;
               if(suffix.equals("wrz"))
                   return false;
               if(suffix.equals("wrl"))
                   return false;
               if(suffix.equals("v"))
                   return false;
               if(suffix.equals("gz"))
                   return false;
               if(suffix.equals("Z"))
                   return false;
               if(suffix.equals("swf"))
                   return false;
               if(suffix.equals("zip") || suffix.equals("tar") || suffix.equals("tgz"))
                   return false;
           }
           return true;
       }

   	
    public void fetchURL(String urlScanned) {
        Document doc;
        String url_Found=null;
		try {
			URL url = new URL(urlScanned);
		//	System.out.println("urlscanned="+urlScanned+" url.path="+url.getPath());
            
            doc = Jsoup.connect(urlScanned).get();
            
            Elements links = doc.select("a[href]");
            for (Element link : links) {
                if (urlID >= maxurls)
                    return;
                
                // get the value from href attribute
                url_Found = link.attr("href");

                URL url_x = new URL(url_Found);
                InputStreamReader in =
                new InputStreamReader(url_x.openStream());
                
    			// read contents into string builder
    			StringBuilder input = new StringBuilder();
    			int ch;
                while ((ch = in.read()) != -1) {
         			input.append((char) ch);
                }
                
     			// search for all occurrences of pattern
    			String patternString =  "<a\\s+href\\s*=\\s*(\"[^\"]*\"|[^\\s>]*)\\s*>";
    			Pattern pattern =
                Pattern.compile(patternString,
                                Pattern.CASE_INSENSITIVE);
    			Matcher matcher = pattern.matcher(input);
                
                while (matcher.find()) {
                    // System.out.println("Found");
    				int start = matcher.start();
    				int end = matcher.end();
    				String match = input.substring(start, end);
                    String urlFound = matcher.group(1);
                    System.out.println(urlFound);
                    
                    // Check if it is already in the database
                    if (!urlInDB(urlFound)) {
                        insertURLInDB(urlFound);
                    }				
                    
    				//System.out.println(match);
                }
            }
            
		}
                catch (Exception e)
      		{
                System.out.println("error "+url_Found);
       			e.printStackTrace();
      		}
	}

   	public static void main(String[] args)
   	{
		Crawler crawler = new Crawler();

		try {
			crawler.readProperties();
			root = crawler.props.getProperty("crawler.root");
            crawler.domain = crawler.props.getProperty("crawler.domain");
            crawler.maxurls = Integer.parseInt(crawler.props.getProperty("crawler.maxurls"));
			//crawler.createDB();
			//crawler.fetchURL(root);
            crawler.startCrawl();
		}
		catch( Exception e) {
         		e.printStackTrace();
		}
    	}
}

