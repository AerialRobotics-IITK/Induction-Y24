 ## BANDIT

# Level 0:
We used the cat command to open the readme file which contained the password for the level 1.
# Level 1:
We entered the password for level 1. (ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If).
For opening the hyphenated files, we gave the command cat ./file name .
We got the password for level 2( 263JGJPfgU6LtdEvgfWU1XP5yac29mFx ).
# Level 2:
We entered the password for level 2. 
We used cat command ad we put \ at the end of every word so that linux can understand that this file has spaces in its name. 
We got the password for level 3 (MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx)
# Level 3:
we entered the password for level 3.
We used ls –alps which shows all the files including hidden one and give detailed information.
We got the password for level 4 ( 2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ ).
# Level 4:
We entered the password for level 4.
Now we used file ./-* to get the type of data present in each file starting from - . and then we found a file with ASCII text . we open that using cat .
# Level 5:
We entered the password for level 5.
We used cd inhere to go inside this directory . then we used find . -type f -size 1033c ! executable (which are the given condition)  to get the file we required. 
We got the password of level 6 from that file. ( HWasnPhtq9AVKe0dmk45nxy20cvUa6EG ) 
# Level 6:
We entered the password for level 6. Go on the root directory.
We used find / -type f -user bandit7 -group bandit6 -size 33c 2>/dev/null ( where 2> = redirect error output (stderr) and   /dev/null = throw it away (ignore) ) .
We get a file . open it and get the password. ( morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj ) 
                                                                    OR
Go to the root directory .
use find . -type f -size 33c | grep "bandit7" 2>/dev/null. We get a file . open it and get the password.
# Level 7:
We entered the password for level 7.
We used grep “millionth” file.txt . grep helps to find the line containing the word millionth and we got the password( dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc )  next to it.
# Level 8:
We entered the password for level 8. 
We used sort data.txt | uniq -u where sort is used to sort the data and uniq -u removes all the files which are duplicate with original and gives distinct file only.
we got the password for level 9 ( 4CKMh1JI91bUIZZPXDqGanal4xvAg0JM ) .
# Level 9:
We entered the password for level 9.
We used strings data.txt | grep “==*” . where strings helps us in finding the human readable strings and grep helps us to find the strings starting from == .
We got the password for level 10 (FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey ) .
# Level 10:
We entered the password for level 10.
We open the data.txt file with cat . we got a data to decode . we used echo "(data to be decoded)" | base64 –decode  . which decode the data and we got the password ( dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr ).
# Level 11 :
We entered the password for level 11.
We used cat data.txt | tr A-Za-z N-ZA-Mn-za-m where cat used to open the file. And tr is used to transform alphabets from set 1 to set 2. We got the password ( 7x16WNeHIi5YkIhWsfFIqoognUTyj9Q4 ) . 
# Level 12 :
We entered the password for level 12.
We used xxd to convert hex dump to binary. Then we decompressed files one by one using gzip , bzip2 , tar xf. And we get password (FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn ).

# Level 13 :	
We entered password for level 13.
We used ssh -I sshkey.private -p 2220 bandit14@localhost . where -I is used to identify the private key . this took us to bandit14 where we used to open the file and we got the password ( MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS ) .
# Level 14 : 
We entered password for level 14.
We used echo "MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS" | nc localhost 30000   . or use telnet localhost 30000 and type password for level 13. 
We got the password 8xCjnmgoKbGLhHFAZlGE5Tmu4M2tKJQo .
# Level 15 :
We entered the password for level 15.
We used openssl s_client -connect localhost:30001 .  -connect localhost:30001: Tells the client to connect to the specified address and port over SSL/TLS.
