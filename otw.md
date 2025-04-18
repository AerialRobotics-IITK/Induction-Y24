# LEVEL 0
**AIM** I was asked to access the bandit server hosting the game with username bandit0 and password bandit0 using ssh , all the required info was listed
**MY_SOL** Made a ssh connection to bandit0 , entered password , used ls to list files , then used cat to display content of a listed file named readme , there password for the level 1 was given


**AIM** Find password for the next succesive level ownwards

# LEVEL 1
ls -> a file named '-' appeared , cat - started taking input from user used Ctrl+D to end this and used ./- to force linux to read '-' as a filename 

# LEVEL 2
ls -> 'spaces in this filename' , cat 'spaces in this filename' breaked into multiple words then googled -> use quotes -> obtained password

# LEVEL 3
ls -la ->  a inhere file appeared , cat inhere , told that it was a directory , cd inhere , ls -la then ...hiding from you appeared , used strings to reveal hidden password

# LEVEL 4
ls -la -> inhere -> ls -> 10 files from 0  to 9 -> file ./* to check filetype of all -
> file 07 and 00 appeared different -> file07 was ascii so go for that and password cracked

# LEVEL 5
ls -la->inhere->20 dir -> each dir-> files -> nested loops -> outer loop run through each dir-> inner loop check if file of size 1033c , non - executable and human readable if file found print its content -> break 2

# LEVEL 6
Just applied the find criteria like size 33c , user bandit7 and group bandit 6 , got the path -> cat path and got password

#  LEVEL 7
ls -la -> found data.txt -> applied grep -i "millionth" data.txt to directly get password

# LEVEL 8
ls -la->found data.txt -> applied sort data.txt | uniq -c and extracted the string which had count 1

# LEVEL 9
in data.txt applied strings -> got some executable ascii text from binary file-> used that string that was preceeded by multiple =

# LEVEL 10
cat data.txt -> used a python program to decode the message to finally get password

# LEVEL 11
cat data.txt -> copied the text and again run a python program that rotates the alphabetical characters by 13

# LEVEL 12
One of the Hardest -> first copied data.txt to a newly created tmp dir yashr24 then  decode the hexadecimal to compressed files using xxd -r data.txt while(filetype!=ascii text)
{
    file filename
        if filename == gzip
           mv filename to filename.gz
           bzip -d filename.gz
        else if filename == bip2
            mv filename to filename.bzip2
            bzip2 -d filename.bz2
        else if filename == tar
            mv filename to filename.tar
            tar xf filename.tar
}
finally cat filename whose filetype is ascii text 

# LEVEL 13
ls -> sshkey.private -> cat and copied privatekey into a private.key on local machine then accessed bandit 14 using -i private.key

# LEVEL 14
used nc localhost 30000 to get the password for next level as told in instructions

# LEVEL 15
used ncat --ssl in localhost 30001 , entered password received from previous level and we get the password for the next level





## PASSWORDS##

# Bandit1
ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If
# Bandit2
263JGJPfgU6LtdEvgfWU1XP5yac29mFx
# Bandit3
MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx
# Bandit4
2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ
# Bandit5
4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw
# Bandit6
HWasnPhtq9AVKe0dmk45nxy20cvUa6EG 
# Bandit7
morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj
# Bandit8
dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc
# Bandit9
4CKMh1JI91bUIZZPXDqGanal4xvAg0JM
# Bandit10
FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey
# Bandit11
dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr
# Bandit12
7x16WNeHIi5YkIhWsfFIqoognUTyj9Q4
# Bandit13
FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn
# Banditt14
MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS
# Bandit15
8xCjnmgoKbGLhHFAZlGE5Tmu4M2tKJQo
# Bandit16
kSkvUpMQ7lBYyCM4GBPvCvT1BfWRy0Dx



