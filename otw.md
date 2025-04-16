### Level 0 : 
ssh bandit0@bandit/labs.overthewire.org -p 2220 ( ssh used to remotely connect to machine )
when prompted for password we enter bandit0

### Level 1 : 
ls ( to list all the files present in the directory)
cat readme.md to see the contents of the file ( which contained the password for the next level ) 

### Level 2 : 
ls 
cat < - ( cannot use cat - ) 

### Level 3 : 
cat "spaces in the filename" ( cannot use cat spaces in the filename as it will treat each word as different file ) 

### Level 4 : 
cd inhere ( to change directory to inhere ) 
ls -a ( list all the files including the hidden files ) 
cat .hidden 

### Level 5 : 
cd inhere
file ./* ( used a wildcard instead of a filename to get the type for all the files ) 
cat < -file07

### Level 7 :
 file command used with:-type f(looking for a file), -user, -group, 2>/dev/null( to hide the error messages )
find / -user bandit7 -group bandit7 -type f 2>/dev/null / is used to search outside the directory 

### Level 8 : 
cat data.txt | grep millionth ( grep is used to find a particular word in the data ) 
 
### Level 9 : 
sort data.txt | uniq -u ( uniq command is used to find unique elements but the data needs to be sorted as it removes duplicate data)

### Level 10 : 
strings data.txt | grep === ( strings is used to filter all the strings from the data ) 

### Level 11 : 
cat data.txt 
base64 -d data.txt ( base634 - d is used to decode the encoded text ) 

### Level 12 : 
cat data.txt ( contains ROT13 enxrypted data ) 
cat data.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m' ( tr is used to replace old characters with new characters ) 


