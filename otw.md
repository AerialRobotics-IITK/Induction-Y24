level 0:
login into the bandit0 port 2220 by command ssh bandit0@bandit.labs.overthewire.org -p 2220, and password is bandit0.

level 1:
now command ls which shows all the files in the home depository and the file name is readme
now command cat readme which catenates the file readme and give us password for the next level

level 2:
first exit the previous port
now login to bandit 1 port 2220 with the similar command as in level 0 except we have to write bandit1 instead of bandit0 
and put in the password which we got from the previous level
now again command ls and file named - will come
to catenate we use the syntax cat ./- 
this gives us the password for the next level

level 3:
first exit from the previous port
now login to bandit 2 port 2220 
put in the pass we got
command ls and file named spaces in this filename will come
to catenate we use the syntax spaces\ in\ this\ filename
this gives us the pass

level 4:
again command ls and inhere directory comes
now command cd inhere to navigate into inhere
now command ls -la to see all the hidden files
now a hidden file named ...Hiding-From-You comes
now cat it to get the pass

level 5:
now command cd inhere and navigate into inhere
now command ls -la and many files will come
now to check the only human readable file , command file ./-* which checks types of all the files
now cat the file which ascii text type which is -file07 and get password

level 6:
now we have to find files which are human readable, not executable, and having size 1033 bytes
so we command find inhere -type f ! -executable -size 1033c
this shows all the files which satisfies the above parameters then we check for the human readable parameter on the files we get
and only file which satisfies is .file2 so we cat it and get the pass

level 7:
now to find the files which are owned by user bandit7 and group bandit 6 and has size33c
we command find / -size 33c -user bandit7 -group bandit6 and this gives us the path to the pass

level 8:
now the pass is next to the word millionth in data.txt
so we command grep 'millionth' data.txt which gives us the pass

level 9:
now we have to find thw which is not repeated and every other line is repeated
so we command sort data.txt | uniq -u which gives us the pass

level 10:
now we have to find the human readable string which is preceeded by many '=' and has the pass in it
so we command strings data.txt | grep '=' which gives us the string that has the pass

level 11:
now we have to decode the text  given in the file which is encoded in base64
first we command cat data.txt which gives us the encoded data then decode it by giving command echo "encoded text" | base64 --decode which gives us the pass

level 12:










