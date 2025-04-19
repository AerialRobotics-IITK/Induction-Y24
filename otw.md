COMMANDS:

1. man <command> (Manual): it displays the full documentation (like a guidebook) for most Unix commands.

2. help <command> (Help): Gives quick help for bash built-in commands (like cd, exit, history).


3. ls (list): Lists files and directories in the current directory. 
      Usage: 
ls,
ls -l →to check executable flag
ls -lR → to list sub directories
ls -a → for listing hidden files in directory
ls \directory1 → list files of just next directory while being in previous directory.
4. cd (change directory): Changes the current working directory.
      Usage: 
      cd [directory]
      cd .. : for coming to previous directory
5. cat (concatenate and display):  Displays the contents of a file.
      Usage: 
      cat [filename] → to read content
      cat /[directory1] [filename] : display file while being in home or any other directory.
      cat file ./* : to display all the files in a directory

6. file: Tells you what type of data is in a file (text, binary, image, etc.).
      Usage: 
      file [filename]
      file ./* : for finding data types of all the files in a directory.

7. du (disk usage): Shows the size of files and directories.
Usage: 
du, 
du -b → gives size in bytes
du -sh *
      
8. find : Searches for files and directories based on conditions.
      Usage: 
    • find [path] [options]
    • find inhere -type f -size 1033c ! -executable -readable → Find file of certain properties
      inhere — the directory to search in
      type f — find only files
      -size 1033c — look for files exactly 1033 bytes (c stands for bytes)
      ! -executable — exclude executable files
       -readable — ensure the file is readable
9. grep (Global Regular Expression Print): It searches for patterns/keywords inside files or command output.
      Usage: 
    • grep [options] "pattern" filename
10. sort: Sorts lines of text files.
Syntax: sort [OPTIONS] [FILE...]
Usage: sort names.txt
Details: The sort command arranges the observations of the current data into ascending order based on the values of the variables in varlist.
11. uniq: Filters out repeated lines in a file. (use with pipeing)
Syntax: uniq [OPTIONS] [INPUT [OUTPUT]]
Usage: uniq sorted.txt
Details: The uniq command in Linux is a command-line utility that reports or filters out the repeated lines in a file.
12. strings: Extracts printable strings from binary files.
Syntax: strings [OPTIONS] FILE...
Usage: strings binaryfile
Details: The strings command looks for printable strings in a file. A string is any sequence of 4 or more printable characters.
13. base64: Encodes or decodes data using Base64 representation.
Syntax: base64 [OPTIONS] [FILE]
Usage: base64 image.png > image.b64
Details: Base64 encoding converts binary data into ASCII characters, suitable for embedding in text files.
14. tr: Translates or deletes characters from input.
Syntax: tr [OPTIONS] SET1 [SET2] (use with pipeing)
Usage: tr 'a-z' 'A-Z' < file.txt
Details: The tr command translates or deletes characters from standard input and writes the result to standard output.
15. tar: Archives multiple files into a single file.
Syntax: tar [OPTIONS] [ARCHIVE_NAME] [FILE...]
Usage: tar -cvf archive.tar file1 file2
Details: The tar command is used to create and manipulate archive files.
16. gzip: Compresses files using the Gzip algorithm.
Syntax: gzip [OPTIONS] [FILE...]
Usage: gzip file.txt
Details: The gzip command compresses files, reducing their size for storage or transmission.
17. bzip2: Compresses files using the Burrows-Wheeler block sorting algorithm.
Syntax: bzip2 [OPTIONS] [FILE...]
Usage: bzip2 file.txt
Details: The bzip2 command compresses files, achieving higher compression ratios.
18. xxd: Creates a hex dump of a file or standard input.
Syntax: xxd [OPTIONS] [FILE]
Usage: xxd file.bin
Details: The xxd command creates a hex dump or converts it back to binary form.
19. mkdir: Creates a new directory.
Syntax: mkdir [OPTIONS] DIRECTORY...
Usage: mkdir new_folder
Details: The mkdir command is used to create one or more directories specified by the user.
20. cp: Copies files and directories.
Syntax: cp [OPTIONS] SOURCE DEST
Usage: cp file1.txt backup/
Details: The cp command copies files or groups of files and directories.
21. mv: Moves or renames files and directories.
Syntax: mv [OPTIONS] SOURCE DEST
Usage: mv oldname.txt newname.txt
Details: The mv command is used to move files and directories or rename them.
1. ssh
Definition: Secure Shell for remote login.
Syntax: ssh [OPTIONS] user@hostname
Usage: ssh user@192.168.1.10
Details: SSH is used to securely log into a remote machine and execute commands.
2. telnet
Definition: User command and underlying TCP/IP protocol for accessing remote computers.
Syntax: telnet [HOST] [PORT]
Usage: telnet 192.168.1.10 23
Details: Telnet allows remote access over TCP, often used for testing open ports.
3. nc (netcat)
Definition: Reads and writes data across networks using TCP or UDP.
Syntax: nc [OPTIONS] HOST PORT
Usage: nc -v 192.168.1.10 80
Details: Netcat is a versatile networking tool used for port scanning, file transfer, and debugging.
4. ncat
Definition: A modern reinvention of netcat by Nmap.
Syntax: ncat [OPTIONS] HOST PORT
Usage: ncat --ssl 192.168.1.10 443
Details: Ncat offers encryption and connection brokering.
5. socat
Definition: Multipurpose relay for bidirectional data transfer.
Syntax: socat [OPTIONS] <address1> <address2>
Usage: socat TCP4-LISTEN:1234,fork EXEC:/bin/bash
Details: Socat connects two data streams and is used for port forwarding and tunneling.
6. openssl
Definition: Toolkit for TLS/SSL protocols and encryption.
Syntax: openssl [command] [options]
Usage: openssl enc -aes-256-cbc -in file.txt -out file.enc
Details: OpenSSL is used for encryption, key generation, and certificate management.
7. openssl s_client
Definition: SSL/TLS client program for testing servers.
Syntax: openssl s_client -connect host:port
Usage: openssl s_client -connect google.com:443
Details: Useful for debugging SSL configurations and certificates.
8. nmap
Definition: Network scanner for host discovery and port scanning.
Syntax: nmap [OPTIONS] [TARGET]
Usage: nmap -sS 192.168.1.0/24
Details: Nmap is used to scan networks, detect hosts, and discover services
9. netstat
Definition: Displays network connections, routing tables, and interface statistics.
Syntax: netstat [OPTIONS]
Usage: netstat -tuln
Details: Netstat helps monitor and troubleshoot network issues.
10. ss
Definition: Displays socket statistics.
Syntax: ss [OPTIONS]
Usage: ss -tuln
Details: SS is a faster alternative to netstat for showing open ports and connections.

NOTE:

    1. Use < before –, if – is a file name. example “cat < -”
    2. Use \ before “ ”(space), if we the name of the file isn't in single word.  example “cat spaces\ in\ this\ filename”
    3. “ls \directory1 ←→ cat /directory1” don’t confuse between them.
    4. . → points to current directory, .. → points to the directory above, / → used before writing any directory or file name
       

LEVELS:

Level 0: 
first I entered the command “ssh bandit0@bandit.labs.overthewire.org -p 2220” where ‘bandit0’ is user id and password is ‘bandit0’. -p is used to connect with a particular port and bandit.labs.overthewire.org is host.
Ssh stands for secure shell, it lets you securely connect to another computer (usually a server) over the internet or network. 

OR, “ssh bandit.labs.overthewire.org -l bandit0 -p 2220” also works, where -l is for login.


Level 0 → Level 1:
First I entered ‘ls’ command to list the “readme” file then use ‘file’ and ‘cat’ command to find the file type and text stored in that file, that is “ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If” the password for bandit1. Then exit from bandit0 and login to bandit1.


Level 1 → Level 2:
in bandit1, similar to bandit0 password was stored in ‘-’ file, entered ls to list then “cat < -” or “cat ./-” (. → points to current directory, .. → points to the directory above, / → used before writing any directory or file name) to extract the password. Given as “263JGJPfgU6LtdEvgfWU1XP5yac29mFx”.
 Then exit from bandit1 and login to bandit2.
[< tells the shell: “take input from the file named -” So cat reads the contents of - file, not from keyboard input.]


Level 2 → Level 3: 
in bandit2, similar to bandit1 password was stored in ‘spaces in this filename’ file, entered ls to list then “cat spaces\ in\ this\ filename” or ““spaces in this filename”” to extract the password. Given as “MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx”. Then exit from bandit2 and login to bandit3.
[Used \ To tell the shell that the spaces are part of the filename, we escape each space or and other character with a backslash (\):]


Level 3 → Level 4:
in bandit3, ‘inhere’ is directory not file, check via file command. Then use find command to find hidden file that is “...Hiding-From-You”. For excising this file first I change directory by cd command then use “cat ...Hiding-From-You”. Password for bandit4 is “2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ”.

OR, Go to inhere by cd then type “ls -a” to directly find hidden file that is “...Hiding-From-You”, now use “cat ...Hiding-From-You” to find password. Also we can use “cd ..” to return to previous directory and then use “cat inhere/...Hiding-From-You” to find text directly from home directory.


Level 4 → Level 5:
First use cd to change directory to inhere then use “file ./*” or “file ./-file*” (due to pattern) to find the data types of all the files in directory inhere. Find for file, whose data type given as ASCII text. Use “cat <-file07” or “cat ./-file07” command to read the password for bandit5, given by “4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw”

 
Level 5 → Level 6:
first enter into inhere directory via cd command. 

we can directly write find command with the given conditions, as “find -size 1033c ! -executable -readable”(-size 1033c →  look for files exactly 1033 bytes (c stands for bytes), ! -executable →  exclude executable files, -readable →  ensure the file is readable).

OR, use “find -size 1033c” to find maybehere07 directory then use “ls -a -l” or “ls -al” to list all files. Here ‘d’ points to directory, and remaining nine bits  rwx rwx rwx corrosponds to owner, group and user on any system of the file respectively. ‘r’ means readable, ‘w’ means can be write and ‘x’ means executable.

Then use “cat .file2”, to get password “HWasnPhtq9AVKe0dmk45nxy20cvUa6EG”.


Level 5 → Level 6:
First I entered the root directory for linux machine i.e, “/” via “cd /” then write find command as, “find -user bandit7 -group bandit6 -size 33c 2>/dev/null” (/ — search the entire system, -type f — look for files, -user bandit7 — file must be owned by user bandit7, -group bandit6 — file must be owned by group bandit6, -size 33c — file must be exactly 33 bytes, 2>/dev/null — hide all permission denied errors). Then use “cat to getcat ./var/lib/dpkg/info/bandit7.password” to get “morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj”.

OR, use “find / -type f -user bandit7 -group bandit6 -size 33c 2>/dev/null” without using “cd /”.


    /dev/null → bil/black whole 




















Level 7 → Level 8:
ls 
“grep "millionth" data.txt” → to find millionth in data.text file
password comes out “dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc” for bandit8.

Level 8 → Level 9:
ls
“sort data.txt | uniq -u” → first sort the data and find the unique text.
password comes out “4CKMh1JI91bUIZZPXDqGanal4xvAg0JM” for bandit9

Level 9 → Level 10:
ls
“strings data.txt | grep “=====”” → first find the human readable strings then find the strings preceded by sevral “=” character.
password comes out “FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey” for bandit10

Level 10 → Level 11:
ls
“base64 -d data.text”  → to decode the file 
password comes out “dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr” for bandit11.

Level 11 → Level 12:
ls
“cat data.txt | tr abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWSYZ nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM” → rotate all lowercase (a-z) and uppercase (A-Z) letters by 13 positions.
OR, “”
password comes out “7x16WNeHIi5YkIhWsfKIqoognUTyj9Q4” for bandit12.

Level 12 → Level 13:
The password is stored in a hexdump format. First use: xxd -r data.txt
This reverses the hexdump. Then, check the output file with: file data.txt
Then use: cat data.txt
Password: 8ZjyCRiBWFYkneahHwxCv3wb2a1ORpYL

Level 13 → Level 14:
The password is stored in /etc/bandit_pass/bandit14 but you can only read it using a program in the
same directory.
Run the program with: ./sshkey.private
Change permissions if needed using chmod 600 sshkey.private
Then SSH into bandit14 with the private key: ssh -i sshkey.private bandit14@localhost -p 2220
Password: fGrHPx402xGC7U7rXKDaxiWFTOiF0ENq

Level 14 → Level 15:
You need to connect to localhost on port 30000 and use the password from bandit14: Use: telnet localhost 30000
Then paste the password when prompted.
Password: jN2kgmIXJ6fShzhT2avhotn4Zcka6tnt

Level 15 → Level 16:
The same as before but now SSL encryption is used. Use: openssl s_client -connect localhost:30001
Paste the password when connected.
Password: cluFn7wTiGryunymYOu4RcffSxQluehd

