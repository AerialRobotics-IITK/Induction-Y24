# level 0
we need to connect to the host in this level.
we use ls to list the files
and then cat readme to read the file and see the password
ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If

# level 1

cat ./- i the command we use in this level to read the file - in the home directory
263JGJPfgU6LtdEvgfWU1XP5yac29mFx

# level 2
cat "spaces in this file name"
MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx
# level 3
 
cd inhere/
ls -al
cat .hidden
2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ
# level 4
cd inhere/
find . -type f | xargs file
 and now read the file which has ASCII text type
 4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw
# level 5 
cd inhere/
find . -type f -size 1033c ! -executable
will give the file location and the file which satisfy the parameter
HWasnPhtq9AVKe0dmk45nxy20cvUa6EG
# level 6
find / -type f -user bandit7 -group bandit6 -size 33c
 will get the file with the password
morbNTDkSW6jIlUc0ymOdMaLnOlFVAa

# level 7
as in this file there are quite a lot of strings so we will use the strings command to ease our task

strings data.txt | grep "millionth"

and you will get the passsword next to the word millionth
dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc
# level 8
 here will use the commands of uniq and sort to sort the content 

 sort data.txt | uniq -c

 here -c tells us the count of a particular unique string and we will check the word woth only 1 occurunce that is the pass
FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey
# level 9

 strings data.txt | grep "="

i t will give the password next to equals
FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey
# level 10
 cat data.txt 
 it will show a base64 encoded data to decrypt it
 base64 -d data.txt 
 
 will give the pass
 dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr
# level 11
  we will use rot 13 method to decrypt it
  data.txt  | tr 'A-Za-z'  'N-ZA-Mn-za-m'
  7x16WNeHIi5YkIhWsfFIqoognUTyj9Q4
  
# level 12
cat data.txt
 we will see that its a hex dump file 
 now we will try to reverse the hex dump file

mkdir /temp/aayush 
cp data.txt /tmp/aayush
cd /tmp/aayush
ls
xxd -r data.txt > data
ls
 we will see that now we have created a file named data which is not a hex dump anymore  lets see the file type of the file
file data
we will get a file with the extension of gzip so we move the data file with a new extension .gz
mv data file.gz
gzip -d file.gz
file file
mv file file.bz2
bzip2 -d file.bz2
file file
mv file file.gz
gzip -d file.gz
file file
 now its a tar archive 
mv file file.tar
tar xf file.tar
ls
file data7.bin
mv data7.bin data.tar
tar xf data.tar
ls
file data6.bin
mv data6.bin data.bz2
bzip2 -d data.bz2
ls
file data
mv data data.tar
tar xf data.tar
ls
file data8.bin
mv data8.bin data.gz
gzip2 -d data.gz
ls
file data
cat data
 NOW this will give us the pass
 FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn
#level 13
ls 
 we will get the sshkey.private which is a private key
ssh -i sshkey.private bandit14@localhost -p 2220
 now we are in bandit 14 
cat etc/bandit_pass/bandit14
 and WE will get the pass
MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS
#level 14
we will use the netap command
nc localhost 30000 # hit enter
MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS
and now entered the password for the previous level
and we will get the password for the next level 
 
