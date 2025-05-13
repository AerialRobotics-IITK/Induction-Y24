Level 0
I saw all the important key words like cat,ls,ls -a,mkdir,…on google first to learn them.
Made a directory using mkdir with name Bandit so that I can store all the passwords separately
Then used cd Bandit to enter into it.
I am saving all the passwords so I saved the first password as echo bandit0 > 0 so I saved it with name 0 so that if I  am lost I can retrieve any password back
After that I used sshpass -p $ (cat 0) ssh bandit0@bandit.labs.overthewire.org -p 2220

Level 0 –> Level1
After entering I typed ls I got a file named readme  then to read the contents of it I typed cat readme  and I got the password.
Then typed exit and came out and then saved it as 1.

Level1 –> Level2
And after entering into to bandit1 similar to bandit0 I got a file named (-) so as it is a special character  I used cat  ./-   then I got the password and saved it as 2.

Level2 –> Level3
After entering bandit2 the file name was spaces in the filename  I thought it as a single file and typed cat spaces\ in\ this\ filename. Then  I got the password saved it as 3.
Got to know that to tell to  include the spaces we have to type \

Level 3 –> Level 4
After entering into bandit3 I got inhere and typed cd inhere   then I typed ls I did not get any file so I typed ls -a(which gave all the files including hidden files) then I got file name …Hiding-From-You  I got the password and saved it as 4.

Level 4 –>Level 5
After entering into bandit4 I got inhere again after typing ls. Then after getting into inhere I typed ls then I got file names with -file00 to -file09 to read all this first I examined every file individually but one of my friend suggested me to use for loop. 
for i in $(ls);do file ./$i;done then I got all the file types and one file with the type ASCII TEXT and remaining all with data so human readable one is ASCII (-file07) then I got the password from that file and saved it as 5.

Level 5–> Level 6
After entering into bandit5 I got inhere again went into that directory and typed ls then got different files with the name maybehere00-maybehere19.
Got to know  ls -alR  where a stands for all L stands for detailed list and R stands for recursively .and tried too search manually but I googled to show whether there is a way to find then got find . used find . -readable -size 1033c -not -executable  dot means to operation on current directory. So after this got the file name ./maybehere07/.file2 then Saved the password as 6.

Level 6 –> Level 7
After entering into bandit6 to search in server we need to use / so typed
find / -user bandit7 -group bandit6 -size 33c  then got so many files then used the command find / -user bandit7 -group bandit6 -size 33c  2>/dev/null  I got /var/lib/dpkg/info/bandit7.password  then cat /var/lib/dpkg/info/bandit7.password  gave the password

Level 7 –> Level 8
After entering into bandit7 got a file named data.txt I used cat data.txt got so may words then I used grep cat data.txt | grep “millionth” then I got the password next to the word millionth.

Level 8 –>Level 9
After entering into bandit8 I used cat data.txt then got so many passwords then to sort them out such that only one of them occurs I did cat data.txt | sort | uniq -c then I got string that repeated only once like the count of each line came so in that there was a text with count 1 so that was my pass word .

Level 9 –> Level 10
After entering into bandit9 I got so many characters so as in the level the password was in the string which is preceded by many = so used cat data.txt | grep =  in that I have searched manually.

Level 10 –> Level 11
After entering into bandit10 , I have typed cat data.txt then I got string of characters which is base64 encoded data so to decode cat data.txt | base64 -d (-d stands for decode) then I got the password.

Level 11 –> Level 12
After entering into bandit11 given that the info in file I rotated by 13 positions that means A ↔ N AND SIMILARLY so B with O like that  then  I did cat data.txt so then to decode this first I tried to do for each letter but in google I got ot know that there areonline decoders available then I used it to get the password

Level 12 –> Level 13
After entering into bandit12 I got data.txt then I have done cat data.txt then I got some data known as Hexdump..made a directory in tmp by cd /tmp and mkdir vivek
Then cd vivek ..then used cp data.txt /tmp/vivek
cat data.txt | xxd -r xxd stands for generate and -r stands for reverse then I saved this into a filename cat data.txt | xxd -r > hexdum
the file type of hexdum was gzip compressed file
then renamed it as mv hexdum hexdum.gz
then gzip -d hexdum.gz (-d stands to decompress)..
again gzip -d hexdum.gz this extracted another hexdum file and then now the file type was bzip2 then again renaming the file name hexdum as hexdum.bz2 by using 
mv hexdum hexdum.bz2   then again using bzip -d hexdum.bz2 to extract the file hexdum now the file type was gzip compressed 
again renamed it mv hexdum hexdum.gz
then again to extract other file gzip -d hexdum.gz
now hexdum file types was posix tar archive 
now tar -x -v -f (x stands for extract v stands for verbose and f stands for file)
tar -xvf hexdum verbose will tell us that what file or files this tar archive has been extracted for us then got data5.bin then again used tar -xvf data5.bin then I got data6.bin  as data5.bin was again a psix tar archive then file type of data6.bin was bzip so I renamed it as mv data6.bin.bz2
then I did bzip -d data6.bin.bz2
then got data6.bin now file type of data6.bin was posix tar archive then again tar -xvf data6.bin
this extracted data8.bin

it was a gzip file so again I used mv data8.bin data8.bin.gz again gzip -d data8.bin.gz
got data8.bin and file type was ASCII text finally !!!.
Then used cat data8.bin then got the pass word

Level 13–> Level 14
After entering into bandit 13 got sshkey.private then used ssh bandit14@localhost -p 2220 -i sshkey.private then entered bandit14  cat /etc/bandit_pass/bandit14
Saved that password 

Level 14 –> Level 15
I ran the command nc localhost 30000 and entered the password obtained in l13 to l14 and it gave me a new password

Passwords I got 
bandit0
ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If
FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey
dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr
7x16WNeHIi5YkIhWsfFIqoognUTyj9
FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn
MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS
8xCjnmgoKbGLhHFAZlGE5Tmu4M2tKJQo
263JGJPfgU6LtdEvgfWU1XP5yac29mFx
MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx
2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ
4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw
HWasnPhtq9AVKe0dmk45nxy20cvUa6EG
morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj
dfwvzFQi4mU0wfNbFOe9RoWskMLg7eE
4CKMh1JI91bUIZZPXDqGanal4xvAg0JM

Some more important points I have learnt 
To use special characters in a file we hav eto use ' ./(special character)' if we dont give this ./ bash is taking this as switch for the cat command
2.To know. WHether it is a single file /continuous file use 'ls-la' command in that thing u can observe it as a single file/continuous file or the multiple files
TO give spaces in the file name you have to use "\ like spaces\ in\ this\ filename"
if we dont give \ this in the above then bash will treat that as four files
git init means initializing 
Stack:we can remove the last in added
Using ls -a to see the hidden files in it
even if it starts with the special character u have to us e ./
To see the file typr file (file name) and pt 8 also works here
To see all the types of file to see in the directory then we have to run a for loop with the syntax for i in $(ls);do file ./$i;done
he Unix operator “$” can be used to access the value of a variable or command. This can be especially useful in conjunction with the cat command to include the contents of a file in another Unix command.
ls -R will give us a recursive view of what files are present inside each folder R means recursive
ls -alR means show detailed lists of files in the directories in a recursive manner
a stands for all L standds for detailed lists and R stands for recursively
c stands for bytes and in using find commmand we can use this thing
like the syntax of the find is find . -(file type like readable or ..) -size (####c) -executable 
if the file is not executable then we have to do this following syntax
find .-(file type like readable or ..) -size (####c) -not -executable in this find . dot siignifies for to search in the directory 
du-to estimate the space usage
find / means search in root directory
we can redirect all the unnecessary messages to bin by using the dustbin by the command 2>/dev/null
grep is used to search for the word in  a file syntax for that is grep '(the word needs to be searched)' filename
in the above one while entering the word no brackets are required
wc menas word count
wc -l data.txt output gives number of words or lines in that file
cat filename |sort will sort the files in that
cat filename | sort | uniq if in the end if we use -c then this will give how many times did the line repeat so cat filename(like data.txt) | sort | uniq
strings used to show the human readable strings 
Base64 encoded data is binary information that has been converted into a printable ASCII string
To decode we use -d
the syntax to use Base64 is cat (filename/directoryname) | base64 -d
from man ls we can see all  the commands we can see
xxd is a tool to generetae and xxd -r -r to reverse
in cp used for copying files
To use rename syntax is mv original name  newname
gzip -d hexdump.gz --->to decompress this gz file (gzip is the tool which helps to compress or decompress the things
GNU tar and POSIX tar. GNU tar was based on an early draft of the POSIX 1003.1 ustar standard. GNU extensions to tar , such as the support for file names longer than 100 characters, use portions of the tar header record which were specified in that POSIX draft as unused.
-xvf x means extract -v stands for verbose -f stands for file
Verbose wil ltell what file or files this tar archivve has extracted for us
ssh bandit14@localhost -p 2220 -i sshkey.private when private key is given
Netcare tool - It is a  nc — arbitrary TCP and UDP connections and listens give md format for this

