# Assignment_1
Bandit Wargame Level 0-15 @ overthewire.org

## Level 0
ssh bandit0@bandit.labs.overthewire.org -p 2220

## Level 0-1

ls -la
cat readme
lvl1 password- ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If

## Level 1-2

ls
cat ./-
lvl2 password- 263JGJPfgU6LtdEvgfWU1XP5yac29mFx

## Level 2-3

ls 
cat "spaces in this filename"
lvl3 password- MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx

##  Level 3-4

ls 
ls -la
cd inhere
ls
ls -la
cat ...Hiding-From-You

lvl 4 password- 2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ

## Level 4-5
ls
cd inhere
ls -la
file ./* (find the file having ASCII characters)
cat ./-file07    (has the key)
lvl5 password- 4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw
## Level 5-6

ls
cd inhere
ls
find . -size 1033c
cd maybehere07
ls
cat ./-file2

lvl6 password- HWasnPhtq9AVKe0dmk45nxy20cvUa6EG

## Level 6-7

find / -user bandit7 -group bandit6 -size 33c
cat /var/lib/dpkg/info/bandit7.password
(search for the file which satisfies given conditions)
lvl 7 password- morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj

## Level 7-8


ls
cat data.txt
cat data.txt | grep millionth
lvl 8 password- dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc

## Level 8-9

cat data.txt
cat data.txt | sort
cat data.txt | sort | uniq -u

lvl 9 password- 4CKMh1JI91bUIZZPXDqGanal4xvAg0JM
##  Level 9-10
ls
cat data.txt | grep =    (didnt work)
strings data.txt | grep =

lvl 10 password- FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey

## Level 10-11
ls
cat data.txt
cat data.txt | base64 --decode

lvl 11 password- dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr

## Level 11-12

ls
cat data.txt
cat data.txt | tr a-zA-Z n-za-mN-ZA-M

lvl 12 password- 7x16WNeHIi5YkIhWsfFIqoognUTyj9Q4
## Level 12-13
mkdir /tmp/hardtoguess1
cp data.txt /tmp/hardtoguess1
cd /tmp/hardtoguess1
ls
file data.txt
xxd -r data.txt d1

file d1
mv d1 d2.gz
gzip -d d2.gz

file d2
mv d2 d3.bz2
bzip2 -d d3.bz2

tar -xvf d4

//These blocks are repeated as necessary until the file commmand does not show the file's type as ASCII
lvl 13 password- FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn
## Level 13-14
ls
ssh bandit14@localhost -i sshkey.private -p 2220

## Level 14-15
cat /etc/bandit_pass/bandit14
lvl 14 password- MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS

nc localhost 30000
//paste lvl 14 password here

lvl 15 password- 8xCjnmgoKbGLhHFAZlGE5Tmu4M2tKJQo
