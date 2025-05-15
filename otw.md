# Bandit wargames :
This games requires to find the passwords at each level, using different Linux commands. 
Connection : We logged in into the game using ssh, which is secure shell.The host to which we need to connect is bandit.labs.overthewire.org, on port 2220.The username is bandit0 and the password is bandit0. Once logged in, we move to the zeroth level of the game.
## Level 0 : 
In this level, in order to get the password for the next level, we need to find it in a readme file in home directory. I used ls to first list the file in home directory. Then I used cat to read the file. And hence, got password for the next level.
## Level 1 : 
For moving to the next level, we need to find a file named - in home directory. In order to get the password, I used cat/- to open the file with this name. Hence, got the password.
## Level 2 : 
For this level, password is in a file named "spaces in this filename". First, I use ls to list all the files. Then, I used cat and wrote the file name in inverted commas to open the file. Hence, I got the password and moved to the next level.
## Level 3 : 
In this level, password is in a hidden file in inhere directory. To get this, first I did ls to list the files and folders. Then, cd inhere to open the folder. Then did ls -a to list all the hidden files. Then I got a file named "...hiding from you". Then used cat to open this file. Hence, I got the password.
## Level 4 : 
In this level, password is again in inhere directory but it is an human readable file. I did ls to get the directory inhere. Then I navigated it using cd inhere. Then I used ls -l.
Then all the files in the directory showed up. Next command is file ./*, this gave the datatype that is stored in each file. For file 7, the datatype is different from all others. This file has password. Then used cat to open the file. Hence, got the password.
## Level 5 : 
In this level, in inhere directory, there is a file which is human readable, 1033 byte sized and non executable. I did ls, then cd inhere. Then find . -type f -size 1033c ! executable to find the file with given requirements. This gives the file address. Then cat ./maybehere07/.file2 . Hence, got the password.
## Level 6 : 
In this level, file address is unknown. The properties of the file are given. Then use command find / -user bandit7 -group bandit6 -size 33c -type f -print 2>/dev/null to find the file with given requirements. Then I got the file address and used cat to open it. Hence, got the password.
## Level 7 : 
In this level, there is a file named data.txt in home directory . There is a line in this file which starts with millions, password is in that line. I used the following commands to get the password
cat data.txt | grep millionth 
Hence, got the password.
## Level 8 : 
In this level, in the file data.txt, every line is getting repeated except 1, which has the password. I used the following commands 
sort data.txt | uniq -c | grep '^ *1 ' . Here, first I sorted all the lines in data.txt in alphabetical order, then the output of this goes as input to uniq -c. Then uniq command processes the sorted lines and outputs each unique line along with a count of how many times it appears. Then output of this goes to grep, and the following command matches the exponential sign to the beginning of the line, asterisk matches 0 or more spaces. 1 matches 1 followed by a space. This ensures we are only selecting lines that appear once. Hence, got the password and moved to the next level.
## Level 9 : 
In this level, the file data.txt has only few human readable strings preceded by several = characters. The command I used here is cat data.txt | strings -e s | grep ==. Opened the file using cat, the output of this goes to strings command, the output of strings goes to grep which checks for = character in the output. It printed 4 lines, where 1 line contains the password. Hence, moved to the next level.
## Level 10 : 
Tn this level, the password for the next level is stored in the file data.txt which contains base64 encoded data. The command used is base64 -d data.txt. This calls base64, -d is used to decode the file. This prints the password.
## Level 11 : 
In this level, there is a data.txt file where all lowercase and uppercase letters have been rotated by 13 positions. The command used is cat data.txt | tr 'a-zA-Z' 'n-za-mN-ZA-M'. Here cat data.txt:  reads the contents of the data.txt file and sends it to the standard output.Then, pipe sends the output of cat to the input of the tr command.
tr 'a-zA-Z' 'n-za-mN-ZA-M': This is the translation part.
'a-z': Represents all lowercase letters from 'a' to 'z'. These will be translated to the corresponding letters in the second set.
'A-Z': Represents all uppercase letters from 'A' to 'Z'. These will also be translated.
'n-za-m': This is the ROT13-shifted lowercase alphabet. 'a' becomes 'n', 'b' becomes 'o', ..., 'm' becomes 'z', and then it wraps around: 'n' becomes 'a', 'o' becomes 'b', ..., 'z' becomes 'm'.
'N-ZA-M': This is the ROT13-shifted uppercase alphabet, following the same logic as the lowercase.
This outputs the password.
## Level 12 : 
In this level, the password is in data.txt file which is a hexdump of a file that has been repeatedly compressed. A temporary directory is to be made using command mkdir /tmp/folder/. Then cd tmp/folder/ to open the temporary directory. Then copied the data.txt file in home directory to current directory using cp ~/data.txt. Then used command xxd -r data.txt > data2.txt to convert ascii text to gunzip. Then renamed the file data2.txt to binary.gz. Then extracted the file the file using gunzip binary.gz. Then the output will be a file named binary. To check the filetype of this file, used the command file binary. This gives a file of filetype bzip2. Then extracted this using bunzip. The command is bzip2 binary. This outputs a file named binary.bz2. To check the filetype, used file binary.bz2. Then extracted this file using bzip2 -d binary. This gives an extracted file named binary.out. Then, checked its filetype which is gunzip. Then renamed binary.out to binary.hz using mv binary.out binary.gz. Then extracted from gunzip using gunzip binary.gz. Similarly, extracted it multiple times. Finally got  a file with datatype asciitext named data8. Then opened it using cat and got the password.
## Level 13 : 
In this level, the password for next level is stored in /etc/bandit_pass/bandit14 and only bandit14 user can read it. This will not give a password but will give an ssh key. Listed the files using ls, got a file named sshkey.private. ssh command can be used with the -i flag to use the private key. Then used the command ssh -i sshkey.private -key 2220. I have logged as bandit14 user. To get the password for the current user, command used cat /etc /bandit_pass/bandit14. This gives the password for 14 level.
## Level 14 : 
In this level, the password for the next level can be retrived by submitting the password of the current level to port 30000  on localhost. I have to check if there is any service running on port mentioned. For this, command is netcat localhost 30000. When entered, this will require a password. I entered a random which lead to a message saying password is incorrect. It is known that the current level is password is stored in /etc/bandit_pass/bandit14.It is to be checked if the password stored in this file is the password for the service running on the mentioned port. For this command is cat /etc/bandit_pass/bandit14. Thus, we get a password, which I copied. Then next command is netcat localhost 30000. This reuires a password when entered, I entered the password I copied previously. 
# This outputs correct and gives the password for the next level. Hence, we enter to the 15th level.
