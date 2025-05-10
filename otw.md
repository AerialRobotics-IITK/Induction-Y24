# bandit solutions

## level 1 - The password for the next level is stored in a file called readme located in the home directory. Use this password to log into bandit1 using SSH. Whenever you find a password for a level, use SSH (on port 2220) to log into that level and continue the game.
      ssh username@host -p (port no.)

## level 2 - The password for the next level is stored in a file called - located in the home directory.
sol> to access file with name with special character we use ./ (special char)

## level 3 - The password for the next level is stored in a file called spaces in this filename located in the home directory.
      cat spaces\ in\ filename

## level 4 - The password for the next level is stored in a hidden file in the inhere directory.
sol > ls , then cd inhere , ls -a, cat <thehiddenfile>

## level 5 - The password for the next level is stored in the only human-readable file in the inhere directory. 
sol > ls then ,cd inhere ,ls,
for  i  in {0..9}; do file ./-file0$i; done
cat file 07

## level 6 - The password for the next level is stored in a file somewhere under the inhere directory and has all of the following properties:
### human-readable,1033 bytes in size,not executable

sol > ls , cd inhere , du -a -b | grep 1033,cd maybehere07 ,  ls -l, check for -rw-r-------  files ,
check for file  is human readable by doing- file <file name>, now cat <filename>

## level 7 - The password for the next level is stored somewhere on the server and has all of the following properties:
### owned by user bandit7
### owned by group bandit6
### 33 bytes in size
sol > find then . or / ( < . >will search in disk and < / > will search on the server)

     find / -type f -user <___> -group <____>  -size <__>c
                            


## level 8 - The password for the next level is stored in the file data.txt next to the word millionth
sol >

     cat data.txt | grep millionth   
, pipe take input from a cmd then treansfer it to next cmd
,grep find patern in the file .

## level 9 -The password for the next level is stored in the file data.txt and is the only line of text that occurs only once
sol >

      sort data.txt |uniq -u   
first sort to keep same lines together, then uniq cmd delete
same lines .


## level 10 - The password for the next level is stored in the file data.txt in one of the few human-readable strings, preceded by several ‘=’ characters.

sol >

    strings data.txt | grep "===="  
strings output readable text then we pipe it 
into grep which simply find the pattern in it .

## level 11 - The password for the next level is stored in the file data.txt, which contains base64 encoded data

sol >

        base64 -d data.txt   
here base64 decodes the file -d flag for decoding cmd

## level 12 - The password for the next level is stored in the file data.txt, where all lowercase (a-z) and uppercase (A-Z) letters have been rotated by 13 positions

sol >
    
    cat data.txt | tr 'a-z' 'n-za-m' |tr 'A-Z' 'N-ZA-M' 
    
 first cat and pipe data to tr which rotate all 
lower case letters then pipe this again to tr which rotate all upper case letters

## level 13 - The password for the next level is stored in the file data.txt, which is a hexdump of a file that has been repeatedly compressed.

 sol > first make a file in temp dir. then cp data file in it , extract using xxd -r cmd ,specify file type by file <filename> cmd then,
 change file name using mv acc to file type ,then extract and rename several times using bzip2 ,gzip,tar

## level 14 - The password for the next level is stored in /etc/bandit_pass/bandit14 and can only be read by user bandit14. For this level, you don’t get the next password,
### but you get a private SSH key that can be used to log into the next level.

sol > ssh bandit14@bandit.labs.overthewire.org -p 2220 -i sshkey.private to log in
 then cat , here -i flag to use thekey file

## level 15 - The password for the next level can be retrieved by submitting the password of the current level to port 30000 on localhost.

sol > used the nc cmd >  nc localhost <portno.> send info which you want

## level 16 - The password for the next level can be retrieved by submitting the password of the current level to port 30001 on localhost using SSL/TLS encryption.

sol > used  openssl s_client -connect localhost:30001  , then send the data.
