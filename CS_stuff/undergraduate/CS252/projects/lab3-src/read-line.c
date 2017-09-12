
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>
#include <termios.h>
#include <string.h>
#define MAX_BUFFER_LINE 2048
#define backspace 8
void tty_raw_mode(void);
// Buffer where line is stored
int lineLen, cur = 0;
char line[MAX_BUFFER_LINE];


int hisEnd = -1, hisNum = 0, hisIndex;
const int hisLen = 20;
char * history [hisLen] = {0};

void read_line_print_usage()
{
  const char * usage = "\n"
    " ctrl-?       Print usage\n"
    " Backspace    Deletes last character\n"
    " up arrow     See last command in the history\n";

  write(1, usage, strlen(usage));
}

void writeChars(const char ch, int n)
{
	while(n--) {
		write(1, &ch, 1);
	}
}

/* 
 * Input a line with some basic editing.
 */
char * read_line() {
    int showTab = 0;
    char names[2][1024];
    
    struct termios orig_attr;
    tcgetattr(0,&orig_attr);
    
	// Set terminal in raw mode
	tty_raw_mode();

    cur = lineLen = 0;
    hisIndex = hisNum;
	// Read one line until enter is typed
	while (1) {
		// Read one character in raw mode.
    	char ch;
    	read(0, &ch, 1);
        if (ch!=9) {
            showTab = 0;
        }
	    if (ch>=32 && ch != 127) {
			// It is a printable character.

	      	// If max number of character reached return.
			if (lineLen==MAX_BUFFER_LINE-2) {
				break;
			}

	      	// add char to buffer.
            for(int i = lineLen + 1; i > cur; i--) {
                line[i] = line[i-1];
            }
    	  	line[cur] = ch;
            lineLen++;
            write(1, line + cur, lineLen - cur);
            cur++;
            writeChars(backspace, lineLen - cur);
    	} else if (ch==10) {
      		// <Enter> was typed. Return line
      
			// Print newline
			write(1, &ch, 1);
			break;
    	} else if (ch == 9) { //Tab
            regex_t preg;
            regmatch_t pmatch[1];
            char *arg = strrchr(line, ' ');
            if (!arg) {
                arg = line;
            }
            char exp[1024];
            int i, j = 1;
            exp[0] = '^';
            while(arg < line + cur) {
                switch(*arg) {
                    case '.':
                        exp[j++] = '\\'; exp[j++] = '.'; break;
                    case '?':
                        exp[j++] = '.'; break;
                    case '*':
                        exp[j++] = '.'; exp[j++] = '*'; break;
                    default:
                        exp[j++] = *arg;
                        break;
                }
                arg++;
            }
            strcpy(exp + j, ".*");
            if (regcomp(&preg, exp, REG_EXTENDED | REG_NOSUB)) {
                continue ;
            }
            struct dirent64 *ent;
            DIR *d = opendir(".");
            
            if (showTab == 0) {
                // Now we need to check what entries match
                for(i=0; i<2 && (ent = readdir64(d));) {
                    // Check if name matches
                    if (!regexec(&preg, ent->d_name, 1, pmatch, 0)) {
                        strcpy(names[i++], ent->d_name);
                    }
                }
                if (i==1) {
                    int l = strlen(names[0] + cur);
                    write(1, names[0] + cur, l);

                    if (cur + l < lineLen) {
                        writeChars(backspace, lineLen - l - cur);
                    }
                    lineLen = cur = cur + l;
                } else {
                    showTab = i;
                }
            } else {
                write(1, line + cur, strlen(line + cur));
                writeChars('\n', 1);
                while(ent = readdir64(d)) {
                    if (!regexec(&preg, ent->d_name, 1, pmatch, 0)) {
                        write(1, ent->d_name, strlen(ent->d_name));
                        write(1, " \t", 2);
                    }
                }
                writeChars('\n', 1);
                write(1, "myshell>", 8);
                write(1, line, lineLen);
                writeChars(backspace, lineLen - cur);
            }
            regfree(&preg);
            closedir(d);
        } else if (ch == 1) { // Ctrl + A
            writeChars(backspace, cur);
            cur = 0;
        } else if (ch == 5) { // Ctrl + E
            write(1, line + cur, lineLen - cur);
            cur = lineLen;
        } else if (ch == 4 && cur < lineLen) { // Ctrl + H
      		// Remove one character from buffer
            for(int i = cur; i<lineLen; i++) {
                line[i] = line[i+1];
            }
      		lineLen--;
            write(1, line + cur, lineLen - cur);
      		ch = ' ';
            write(1, &ch, 1);
            
      		// Go back one character
      		writeChars(backspace, lineLen + 1 - cur);
    	} else if ((ch == 8 || ch ==127) && cur > 0) {
			// <backspace> was typed. Remove previous character read.

			// Go back one character
      		ch = backspace;
      		write(1,&ch,1);

      		// Remove one character from buffer
            for(int i = cur - 1; i<lineLen; i++) {
                line[i] = line[i+1];
            }
      		lineLen--;
            cur--;
            write(1, line + cur, lineLen - cur);
      		ch = ' ';
      		write(1,&ch,1);
            
      		// Go back one character
      		writeChars(backspace, lineLen + 1 - cur);
    	} else if (ch==27) {
			// Escape sequence. Read two chars more
			// HINT: Use the program "keyboard-example" to
      		// see the ascii code for the different chars typed.
			char ch1;
    	  	char ch2;
      		read(0, &ch1, 1);
      		read(0, &ch2, 1);
      		if (ch1 == 91 && ch2 == 65 && hisIndex > 0) { // up
                hisIndex--;
                int i = ( hisEnd - hisNum + 1 + hisLen + hisIndex ) % hisLen;
                writeChars(' ', lineLen - cur);
                writeChars(backspace, lineLen);
                strcpy(line, history[i]);
                cur = lineLen = strlen(line);
                write(1, line, lineLen);
      		} else if (ch1 == 91 && ch2 == 66 && hisIndex+1 < hisNum) { // down
                hisIndex++;
                int i = ( hisEnd - hisNum + 1 + hisLen + hisIndex ) % hisLen;
                writeChars(' ', lineLen - cur);
                writeChars(backspace, lineLen);
                strcpy(line, history[i]);
                cur = lineLen = strlen(line);
                write(1, line, lineLen);
			} else if (ch1 == 91 && ch2 == 67) { // right
                if (cur < lineLen) {
                    write(1, line + cur, 1);
                    cur++;
                }
			} else if (ch1 == 91 && ch2 == 68) { // left
				if (cur > 0) {
                    ch = 8;
                    write(1, &ch, 1);
                    cur--;
                }
			}
    	}
	}

	// Add eol and null char at the end of string
    line[lineLen] = 0;
    if (lineLen) {
        hisEnd = (hisEnd + 1) % hisLen;
        if (history[hisEnd]) {
            free(history[hisEnd]);
        } else {
            hisNum++;
        }
        history[hisEnd] = strdup(line);
    }

	line[lineLen++] = 10;
	line[lineLen] = 0;
    
    tcsetattr(0,TCSANOW,&orig_attr);

	return line;
}
void printHistory(){
    for(int i=0; history[i]!=NULL; i++){
        printf(" %d: %s\n", i, history[i]);
    }
}

