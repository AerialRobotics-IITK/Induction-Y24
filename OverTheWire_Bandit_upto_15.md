Level 0 :
**Username : bandit0**
```bash
ssh bandit0@bandit.labs.overthewire.org -p 2220
```
**password : bandit0**

### Level 0 to Level 1
```bash
ls -alps
```
> lists all the directory contents of bandit0
```bash
cat readme
```
> gives the password to the next level stored in the readme directory
exit and login to bandit1 using ssh as did in Level 0
**password : ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If**

### Level 1 to Level 2
```bash
ls -alps
```
> lists all the directory contents of bandit1
```bash
cat./-
```
> We cannot directly write cat - because then the compiler does not give output as there is no filename after - thats why we use ./ and then filename - and now we get the password for next level
exit and login to next level using ssh
**password : 263JGJPfgU6LtdEvgfWU1XP5yac29mFx**

### Level 2 to Level 3
```bash
ls -alps
```
> lists all the directory contents of bandit2
```bash
cat spaces\ in\ this\ filename
```
> \ takes in account the spaces in the name of the file "spaces in this filename" and hence we get the password for next level
exit and login to next level using ssh.
**password : MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx**

### Level 3 to Level 4
```bash
ls -alps
```
> lists all the directory contents of bandit3
```bash
cd inhere/
```
> changes the working directory to inhere
```bash
ls -alps
```
> lists all the directory contents of inhere
```bash
cat ...Hiding-From-You
```
> gives password of the next level from the hidden file
exit and login to next level using ssh
**password : 2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ**

### Level 4 to Level 5
```bash
ls -alps
```
> lists all the directory contents of bandit4
```bash
cd inhere/
```
> changes the working directory to inhere
```bash
ls -alps
```
> lists all the directory contents of inhere
```bash
file ./*
```
> finds the human readable file in inhere directory and indicates it as ASCII text
```bash
cat ./-file07
```
> gives the password from the human readable file for the next level
exit and login to next level using ssh
**password : 4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw**

### Level 5 to Level 6
```bash
ls -alps
```
> lists all the directory contents of bandit5
```bash
cd inhere/
```
> changes the working directory to inhere
```bash
ls -alps
```
> lists all the directory contents of inhere
```bash
find ~/inhere ! -executable -size 1033c
```
> finds the required file with size 1033 bytes and which is human readable and not executable
```bash
cat /home/bandit5/inhere/maybehere07/.file2
```
> gives the password stored in the file found above
exit and login to next level using ssh
**password : HWasnPhtq9AVKe0dmk45nxy20cvUa6EG**

### Level 6 to Level 7
```bash
find / -user bandit7 -group bandit6 -size 33c
```
> finds the file address of the file owned by user bandit7 and group bandit6 and of size 33 bytes
```bash
cat /var/lib/dpkg/info/bandit7.password
```
> gives the password stored in the file found above
**password : morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj**
exit and login to next level using ssh

### Level 7 to Level 8
```bash
ls -alps
```
> lists all the directory contents of bandit7
```bash
cat data.txt
```
> gives the contents of the file data.txt
```bash
grep millionth data.txt
```
> gives the password next to the word millionth in data.txt
exit and login to next level using ssh
**password : dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc**

### Level 8 to Level 9
```bash
ls -alps
```
> lists all the directory contents of bandit8
```bash
cat data.txt
```
> gives the contents of the file data.txt
```bash
sort data.txt | uniq -u
```
> sorts the lines in data.txt and prints only the unique line which is the password
exit and login to next level using ssh
**password : 4CKMh1JI91bUIZZPXDqGanal4xvAg0JM**

### Level 9 to Level 10
```bash
ls -alps
```
> lists all the directory contents of bandit9
```bash
cat data.txt
```
> gives the contents of the file data.txt
```bash
ls
```
```bash
file data
```
> shows the type of the file data which is gzip

```bash
strings data.txt
```
> converts data in data.txt in strings
```bash
strings data.txt | grep ===
```
> prints strings succeeded by === in data.txt
exit and login to next level using ssh
**password : FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey**

### Level 10 to Level 11
```bash
ls -alps
```
> lists all the directory contents of bandit10
```bash
cat data.txt
```
> gives the contents of the file data.txt
```bash
base64 -d data.txt
```
> decodes the base64 encoded data in data.txt
exit and login to next level using ssh
**password : dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr**

### Level 11 to Level 12
```bash
ls -alps
```
> lists all the directory contents of bandit11
```bash
cat data.txt
```
> gives the contents of the file data.txt
```bash
cat data.txt | tr [a-zA-Z] [n-za-mN-ZA-M]
```
> rotates every letter in data.txt by 13 places to give the password
exit and login to next level using ssh
**password : 7x16WNeHIi5YkIhWsfFIqoognUTyj9Q4**

### Level 12 to Level 13
```bash
ls
```
> lists all the directory contents of bandit12
```bash
cat data.txt
```
> gives the contents of the file data.txt
mkdir /tmp/pssd (creates a new directory pssd under /tmp)
```bash
cp data.txt /tmp/pssd
```
> copies contents of data.txt to /tmp/pssd
```bash
cd /tmp/pssd
```
> changes working directory to /tmp/pssd
```bash
ls
```
> lists all the directory contents of /tmp/pssd
```bash
xxd -r data.txt > data
```
> creates a hexdump of data.txt to data
```bash
ls
```
```bash
file data
```
> Shows the type of file "data" is
```bash
mv data file.gz
```
> renames data to file.gz
```bash
ls
```
```bash
gzip -d file.gz
```
> compresses gzip type file.gz
```bash
ls
```
```bash
file file
```
> Shows the type of "file" after compression
```bash
mv file file.bz2
```
> Renames file to file.bz2
```bash
bzip2 -d file.bz2
```
> Compresses bzip2 type file.bz2
```bash
ls
```
```bash
file file
```
> Shows the type of "file" after compression
```bash
mv file file.gz
```
> renames data to file.gz
```bash
gzip -d file.gz
```
> compresses gzip type file.gz
```bash
ls
```
```bash
file file
```
> Shows the type of "file" after compression
```bash
mv file file.tar
```
> renames data to file.tar
```bash
tar xf file.tar
```
> Creates a compressed archive of file.tar
```bash
ls
```
```bash
rm file.tar
```
> removes file.tar
```bash
rm data.txt
```
> removes data.txt
```bash
ls
```
```bash
file data5.bin
```
> Shows the type of "data5.bin"
```bash
mv data5.bin data.tar
```
> renames data5.bin to data.tar
```bash
tar xf data.tar
```
> Creates a compressed archive of data.tar
```bash
ls
```
```bash
file data6.bin
```
> Shows the type of "data6.bin"
```bash
mv data6.bin data.bz2
```
> renames data6.bin to data.bz2
```bash
bzip2 -d data.bz2
```
> Compresses bzip2 type data.bz2
```bash
ls
```
```bash
file data
```
> Shows the type of "data" after compression
```bash
mv data data.tar
```
> renames data to data.tar
```bash
ls
```
```bash
tar xf data.tar
```
> Creates a compressed archive of data.tar
```bash
ls
```
```bash
file data8.bin
```
> Shows the type of "data8.bin"
```bash
mv data8.bin data.gz
```
> renames data8.bin to data.gz
```bash
gzip -d data.gz
```
> compresses gzip type data.gz
```bash
ls
```
```bash
file data
```
> Shows the type of "data" after compression
```bash
cat data
```
> gives the password stored in "data"
exit and login to next level using ssh
**password : FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn**

### Level 13 to Level 14
```bash
ls
```
> lists all the directory contents of bandit13
```bash
ssh -i sshkey.private bandit14@localhost -p 2220 (sshkey.private helps us login to the next level)
```

### Level 14 to Level 15
```bash
cat /etc/bandit_pass/bandit14
```
> gives the password for the current level as specified in the previous level
**password for level 14: MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS**
```bash
nc localhost 30000 then enter password found above and this gives password for next level.
```
**password for level 15: 8xCjnmgoKbGLhHFAZlGE5Tmu4M2tKJQo**

THE END!!!!!!!!!