# OverTheWire Bandit Wargame Levels 0–15

## General  
**Enter a level using the command:**  
`ssh bandit12@bandit.labs.overthewire.org -p 2220` (here level12)

---

## Level 0  
**Given password is bandit0 then use cat to read the file readme**

---

## Level 1  
**Use ls - list of files and cat - displays the content of the file. Special syntax**  
`cat ./-` **for opening this file**

---

## Level 2  
**Use** `cat./””` **syntax for opening file with big names**

---

## Level 3  
1. **Use** `cd` **to change directory to inhere**  
2. **Use** `ls -a` **as it shows all files including hidden and then use** `cat`

---

## Level 4  
**Use** `file ./0*` **to get information about files and then open the file with ascii text**

---

## Level 5  
**Use** `find ./ -size 1033c 2>dev/null/` **to get the required file (2>/dev/null - dumps the waste files)**

---

## Level 6  
**Use** `find ./ -user bandit6 -user group 2>/dev/null`

---

## Level 7  
**Use** `cat data.txt | grep”millitonth”`  
**grep finds the next work to millionth and** `|` **is referred to as piping which is needed to execute multiple sequentially**

---

## Level 8  
**Use** `cat data.txt | sort | uniq -u`  
**first we need to sort because uniq can only detect adjacent duplicates and then it prints the line which is not repeated even once**

---

## Level 9  
**Use** `strings data.txt | grep”==”`  
**it prints all strings which are present in the txt file after two = signs. Since multiple = were mentioned we could use 2 = signs.**

---

## Level 10  
**Use** `cat data.txt | base64 -d` **as it decodes the base 64 data**

---

## Level 11  
**Use** `tr` **to decrypt the rotated positions of the alphabets. Here the data is encrypted using ROT13**

---

## Level 12  
**Use** `mkdir` **to create a temporary directory then change path of the file, decompress using** `xxd` **and then repeatedly decompress file using** `gzip2 -d` **`bzip -d` commands and `tar` commands.**

---

## Level 13  
**Use the command** `ssh -i sshkey.private -p 2220 bandit14@localhost`  
**which specifies the identity file to be used for authentication (sshkey.private in this case) and then using the account bandit14 logs into the localhost. Then use** `cat` **to write out the contents of the file** `/etc/bandit_pass/bandit14`

---

## Level 14  
**Use the command** `nc localhost 30000`  
**where the command nc tells you to connect to the port number 30000 on your local machine which is exactly what the level expects us to do.**

---

## Level 15  
**Use the command** `openssl s_client -connect localhost:30001`  
**Since the data is encrypted we establish a secure ssl connection and connect the local server on port 30001 to get the password for the next level.**
