#LEVEL 0
What the level asked for: Logging in to the game via SSH	
Logic used: *Used # ssh bandit0@bandit.labs.overthewire.org -p 2220 # with password "bandit0".
            *read the "readme" file using command ## cat readme ##.

#LEVEL 1
What the level asked for: *Read a file named "-" which is also used in commands so can't be used directly as file name.
Logic used: *Used ## ssh bandit1@bandit.labs.overthewire.org -p 2220 ## with password "ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If".
            *Use # cat ./- # to bypass filename error.
            ./ specifies the current directory and prevents - from being interpreted as a command.

#LEVEL 2
What the level asked for: Reading a file with spaces in its name.
Logic used: *Used # ssh bandit2@bandit.labs.overthewire.org -p 2220 # with password "263JGJPfgU6LtdEvgfWU1XP5yac29mFx".
            *Included spaces in file name itself by using double quotes and making it as a string. # cat "spaces in this filename" #.

#LEVEL 3
What the level asked for: Finding a hidden file.
Logic used: *Used # ssh bandit3@bandit.labs.overthewire.org -p 2220 # with password "MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx".
            *Used # ls -a # which lists hidden files (starting with .), and # cat # reads the hidden file.

#LEVEL 4
What the level asked for: Identifying the only human-readable file.
Logic used: *Used # ssh bandit4@bandit.labs.overthewire.org -p 2220 # with password "2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ".
            *Used the # file # command to check the file type for each file listed using # ls #.
            *# file file_name # the showing ASCII TXT is the required file.
#LEVEL 5
What the level asked for: Find a file with specific properties (1033 bytes, non-executable and human-readable).
Logic used: *Used # ssh bandit5@bandit.labs.overthewire.org -p 2220 # with password "4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw".
            *# find . -size 1033c -type f ! -executable -readable #
            * find command used to locate a file file in current directory of size 1033bytes(using -size 1033cc command), type of file (-type f command),non-executable(using ! -executable command) and
              readable(using -readable command).

#LEVEL 6
What the level asked for: Locate a file owned by user bandit7 and group bandit6.
Logic used: *Used # ssh bandit6@bandit.labs.overthewire.org -p 2220 # with password "HWasnPhtq9AVKe0dmk45nxy20cvUa6EG".
            *# find / -user bandit7 -group bandit6 2>/dev/null #
            *Search the entire system (/) for files owned by bandit7 and group bandit6. 2>/dev/null hides errors.

#LEVEL 7
What the level asked for: Extract a password next to the word "millionth" stored in the file data.txt
Logic used: *Used # ssh bandit7@bandit.labs.overthewire.org -p 2220 # with password "morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj".
            *# grep 'millionth' data.txt #
            *(grep) searches for the line containing the keyword "millionth" in file data.txt

#LEVEL 8
What the level asked for: Find the only unique line in a file of duplicates.
Logic used: *Used # ssh bandit8@bandit.labs.overthewire.org -p 2220 # with password "dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc".
            *# sort data.txt | uniq -u #
            *(sort) puts the lines in the file in order; (uniq -u) filters out duplicates, leaving only the unique line.

#LEVEL 9
What the level asked for: Extract a human-readable string from binary data which has multiple "=" preceeding it.
Logic used: *Used # ssh bandit9@bandit.labs.overthewire.org -p 2220 # with password "4CKMh1JI91bUIZZPXDqGanal4xvAg0JM".
            *# strings data.txt | grep '==' #
            *(strings) extracts human-readable text from binaries; (grep) finds lines with == in a file named data.txt

#LEVEL 10
What the level asked for: Decode base64 data.
Logic used: *Used # ssh bandit10@bandit.labs.overthewire.org -p 2220 # with password "FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey".
            *# base64 -d data.txt #
            *(base64 -d) decodes the Base64-encoded password which can then be printed by using (cat).

#LEVEL 11
What the level asked for: Recover the password stored in the file data.txt, where all lowercase (a-z) and uppercase (A-Z) letters have been rotated by 13 positions
Logic used: *Used # ssh bandit11@bandit.labs.overthewire.org -p 2220 # with password "dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr".
            *# tr 'A-Za-z' 'N-ZA-Mn-za-m' < data.txt #
            *(tr) performs ROT13 substitution (shifts letters by 13 positions).

#LEVEL 12
What the level asked for: Decompress a nested hexdump.
Logic used: *Used # ssh bandit12@bandit.labs.overthewire.org -p 2220 # with password "7x16WNeHIi5YkIhWsfFIqoognUTyj9Q4".
            *# mktemp -d (create a temporary directory)
               cp data.txt <tmp_filelocation> (copy the file)
               cd <tmp_filelocation> (move to tmp directory using (cd))
               mv data.txt data (rename the file simpler by (mv))
               xxd -r data (xxd -r reverses a hexdump in binary) #
             *After this use (file) to check for ASCII TXT if not then use recursive decompression with tools like gzip/tar/bbzip2 to extract nested files.
              (cat) is used to read the file that shows ASCII TXT on using (file) on it.  
               

#LEVEL 13
What the level asked for: Log in as bandit14 using an SSH private key.
Logic used: *Used # ssh bandit13@bandit.labs.overthewire.org -p 2220 # with password "FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn".
            *WAS NOT ABLE TO DO THIS BECAUSE EVERYTHING WAS RESULTING IN PERMISSION DENIED.

#LEVEL 14
What the level asked for: Submit the current level's password to port 30000 on localhost.
Logic used: *Used # ssh bandit14@bandit.labs.overthewire.org -p 2220 # with password "MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS".
            *# cat /etc/bandit_pass/bandit14 | nc localhost 30000  #
            *nc (netcat) sends the password to port 30000

#LEVEL 15
What the level asked for: Submit the password to port 30001 using SSL encryption.
Logic used: *Used # ssh bandit15@bandit.labs.overthewire.org -p 2220 # with password "8xCjnmgoKbGLhHFAZlGE5Tmu4M2tKJQo".
            *# cat /etc/bandit_pass/bandit15 | openssl s_client -connect localhost:30001 -ign_eof  #
            *(openssl s_client) establishes an SSL connection.
             (-ign_eof) keeps the connection open until the server responds.
             
