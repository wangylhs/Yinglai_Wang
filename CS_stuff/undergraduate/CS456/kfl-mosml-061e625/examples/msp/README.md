ML Server Pages (version 1.2)
=============================

ML Server Pages (MSP) is a web scripting language, a loose integration
of Standard ML (SML) and HTML in the style of Sun's Java Server Pages,
Microsoft's Active Server Pages, or PHP.

This note describes how to install MSP under Moscow ML 2.10.

To use MSP scripts you'll need

 - Moscow ML 2.10 (may even work with older versions)
 - an Apache webserver (or similar)

This directory contains:

 - mspcompile.sml
 - example MSP scripts


Installation instructions
-------------------------

 1. Edit CGI_DIR and SCRIPTCACHE in `Makefile` to reflect your
    webserver setup for cgi scripts and where to store compiled MSP
    scripts.

 2. Edit `mspcompile.sml` to reflect the location of your Moscow ML
    installation and where to store compiled MSP scripts.

 3. Do 

        make all

 4. Then, install everything by

        sudo make install

 5. Setup your Apache webserver configuration (tested with a standard
    Apache 2.4 installation under Ubuntu 13.10):

    5a. copy the file `msp.conf` to `/etc/apache2/conf-available`

    5b. enable the MSP configuration with the command

            sudo a2enconf msp

    5c. Restart Apache with the command

            sudo service apache2 restart
    
    5d. If you are not using Ubuntu or Debian, then your Apache setup
        might be slightly different. In that case, copy the content of
        `msp.conf` to the relevant Apache conf file for your setup.

 6. Test it.  Copy `hello.msp` to a directory accessible from the web,
    say, `http://foo.com/hello.msp` and point your browser to that URL.


If it doesn't work
------------------
 
 - If you get an error like:

         AH00526: Syntax error on line 1 of /etc/apache2/conf-enabled/msp.conf:
         Invalid command 'Action', perhaps misspelled or defined by a module not included in the server configuration

   After you restart Apache, you probably need to enable the `actions`
   module. For instance, by the command:
         
         sudo a2enmod actions

   And then you most likely also need to enable the `cgi` module
   (using the `a2enmod` command).

 - If mspcompile does start, then check Apache's `error.log`; the
   mspcompile script logs all errors there.

 - If mspcompile starts but cannot compile the generated scripts, then
   possibly the compiler mosmlc cannot find the Msp.ui and Msp.uo files.  
   Make sure you set MOSMLLIB correctly in the Makefile (in this directory).


Writing ML Server Pages
-----------------------

An ML server page script is stored in an .msp file and consists of
HTML (text) fragments and SML (code) fragments.  

Thus a date-enhanced Hello World script might look like this:

    <HTML><BODY>

    <H1>Hello world!</H1>

    The current date and time is
    <?MSP= Date.toString (Date.fromTimeLocal(Time.now())) ?>

    <HR><ADDRESS>Your friendly ML server page</ADDRESS>
    </BODY></HTML>


In general, an SML fragment must have one of the following forms:

* `<?MSP dec ?>`

  An SML declaration  dec  in  <?MSP dec ?>  may define types, 
  functions and variables, and may print (on standard output) HTML
  code that becomes part of the resulting HTML page.

* `<?MSP= exp ?>`

  An SML expression  exp  in  <?MSP= exp ?>  must have type string.  
  The expression is evaluated and the resulting string is printed on
  standard output as part of the resulting HTML page.

* `<?MSP$ exp ?>`

  An SML expression  exp  in  <?MSP$ exp ?>  must have type Msp.wseq.  

  The expression is evaluated and the resulting word sequence is
  printed on standard output as part of the resulting HTML page.

The following structures are particularly useful for writing ML server
page scripts:

 * `Msp`         for efficient functional generation of HTML.  

 * `Mosmlcgi`    for accessing CGI parameters

 * `Mosmlcookie` for manipulating cookies.  Untested.  Cookies can be
                 accessed anywhere in an MSP script, but can be set
                 only in a ML fragment immediately at the beginning of
                 the MSP script, before any HTML fragment.


Who is responsible?
-------------------

The concept of ML server pages was presented by Christian Stefansen at
a Funtechs meeting in December 1999 at the IT University of
Copenhagen.  This early design and implementation is by Peter Sestoft.
The third honourable member of the ML server pages group is Peter
Lund.


For further information
-----------------------

See MSP homepage in `index.msp`

Peter Sestoft (sestoft@itu.dk) 2000-02-22, 2000-08-20
Ken Friis Larsen (ken@friislarsen.net) 2014-03-05
