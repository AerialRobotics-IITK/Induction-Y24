Level 0:
Connected to the bandit server using ssh with the given username and password.Used the command: ssh bandit0@bandit.labs.overthewire.org -p 2220
Level 1:
Password is stored in a file named '-'. Used cat ./- to access it.
Level 2:
Password is stored in a file named 'spaces in this filename'.Used cat "spaces in this filename"
Level 3:
Password is stored in a hidden file. Navigated to inhere directory using cd inhere, then listed all files using ls -a, then used cat .hiddenfile
Level4:
Password is stored in only human readable file in the inhere directory. Navigated to inhere directory using cd inhere, then used ls -lh and then used cat file to get the password.
Level5:
Navigated to inhere directory using cd inhere, then used find . -type f -size 1033c ! -executable and then manually used the command file to find whether the text is ASCII then used the cat.
Level6:
I first used cd /.. to navigate to /. Then used find . -type f -user bandit7 -group bandit6 -size 33c then cat.
Level7:
First used the command grep -n "millionth" data.txt and got it. Then used the command grep "millionth" data.txt to get it directly.
Level8:
Used the command sort data.txt | uniq -u, as uniq can only find the unique strings if the repeayedly occuring string occur together.
Level9:
Used the command strings data.txt | grep ==* and then selected from the list appeared. The strings data.txt will give the strings available and then grep ==*
Level10:
Directly used the command base64 -d data.txt to decode the content of the file.
Level11:
Used the command cat data.txt |tr [a-z] [n-za-m] | tr [A-Z] [N-ZA-M] to first update the small alphabets and the bigger ones
Level12:
First used xxd -r data.txt to convert the hex dump to binary. Then I setup a dir in /tmp as told then used the mv, cp commands, and the file command(to find whether it is compressed by gzip or bzip2 or tar archived) and then used the appropriate commands to decompress it or to extract files from it.
Level13:
Password is stored in /etc/bandit_pass/bandit14. So I have to login into bandit14 to access it. First located the private ssh key inside a file in the home directory of the bandit13. Then setup the correct permissions and then used ssh to log into bandit14 user on the localhost. Then I went to the address /etc/bandit_pass/bandit14 and found the key.
Level 14:
I have already logged into the user bandit14. Now submitted the password to port 30000 on localhost using telnet.
