## Level 0

### pswd - bandit0

used ssh to login to the server for overthewire where bandit is played

## Level 1

### pswd - ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If

used ls to find readme file and used **cat** to read the contents

## Level 2

### pswd - 263JGJPfgU6LtdEvgfWU1XP5yac29mFx

used ls to find a file named '-' used ./- to specify the entire directory because passing only cat - can cause problems since - is commonly used to pass arguements to the function

## Level 3

### pswd - MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx

used quotations to specify the filename when passed as an arguement in cat

## Level 4

### pswd - 2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ

used **ls -a** to show all files including hidden ones then read the file using **cat ./...Hidden-From-You**

## Level 5

### pswd - 4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw

used file ./* to find the type of text in all files and read the file07 using cat since it contained ASCII characters

## Level 6

### pswd - HWasnPhtq9AVKe0dmk45nxy20cvUa6EG

executed **file */* | grep "ASCII text" | du -b -a | grep 1033** to extract all ascii text files of size 1033 since only 1 result showed, read that using cat and got the password

## Level 7

### pswd - morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj

used **find / -user bandit7 -group bandit6 -size 33c 2>/dev/null** we add the last part to hide all permission denied error messages

## Level 8

### pswd - dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc

**cat data.txt | grep millionth** returned the complete line containing millionth including the password

## Level 9

### pswd - 4CKMh1JI91bUIZZPXDqGanal4xvAg0JM

**sort data.txt | uniq -u** sort will sort the file allowing uniq to filter out repeating lines using the -u tag and return the only line appearing once

## Level 10

### pswd - FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey

**cat data.txt | strings | grep ==** strings will return all human readable lines and grep filters them

## Level 11

### pswd - dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr

**cat data.txt | base64 -d** decrypts the encoded text and returns password

## Level 12

### pswd - 7x16WNeHIi5YkIhWsfFIqoognUTyj9Q4

**cat data.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m'** translate command is used to execute rotation by 13 on the character skipping numerical values

## Level 13

### pswd - FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn

we know that first we extract the hexadecimal contents then on reading it using **xxd** we see gzip compressed files start with 1f 8b as their first few bytes hence we decrypt then we see 425a which is bzip2 we repeat this process and encounter .bin files indicating archive extracted using **tar -xf**

## Level 14

### pswd - MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS

first we find the location of the ssh key file using ls then we download it by logging out and accessing the server from our computer using scp (secure copy protocol) for transferring files between hosts over a network then we reduce permissions using chmod 700 and finally login using the sshkey.private with -i tag with ssh

## Level 15

### pswd - 8xCjnmgoKbGLhHFAZlGE5Tmu4M2tKJQo

submitted level 14 password using **nc localhost 30000** and entering the password when prompted
