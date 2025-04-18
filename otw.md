
**Level 0 :**
 Did ssh to port 2220 of the given server with the given username. Entered the password, and in.

**Level 0->1 :** 
Did ls to see readme file in ./ current directory. Used cat to print it

**Level 1->2 :**
Using the command cat - is invalid, so I used cat ./- as it explicitly tells its a file named '-'

**Level 2->3 :** 
Just put file name in " " or ' '. And use cat

**Level 3->4 :** 
Use ls with -a to see it. hidden files have a '.' appended to beginning, so do cd ./.inhere/

**Level 4->5 :** 
Opened all file manually. Or use find's -readable option

**Level 5->6 :** 
Used find with -not -executable, -readable, -size 1033c which tells its 1033 bytes in size

**Level 6->7 :** 
Use find with -user bandit7 -group bandit6 -size 33c. and then manually checking the ones where permission was not denied

**Level 7->8 :** 
Just give the file as input to grep and grep the word millionth

**Level 8->9 :** 
First use sort and then use uniq on the output, with -u flag to find unique line of text

**Level 9->10 :** 
Used strings and passed the file to it, the readable strings got separated and then manually checked the ones with "=" appended to them.

**Level 10->11 :** 
Just use base64 with decode flags

**Level 11->12 :** 
Found the text, and used ROT13 caeser cipher online

**Level 12->13 :** 
Find data.txt use xxd to reverse hexdump(keeping the no-formatting flag off). Then continuously use file to see what type of file it is and using tar, gunzip and bunzip2 until a ascii text file comes

**Level 13->14 :** 
Used ls to find ssh private key. using -i flag on ssh on the bandit server itself, to use the private key

**Level 14->15 :**  
Used nc command to listen on port, and then inputting the password of the Level 14 

**Level 15->16 :** 
Using openssl s_client -connect to connect on localhost on port 30001, and submitting it the password of level 15, to get pass of level 16 
