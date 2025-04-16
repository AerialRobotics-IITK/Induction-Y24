## Level 0 → Level 1

Task:  
You need to find the password for the next level. It’s in a file called readme in your home directory.  
Challenge:  
This one’s pretty basic, just about finding and reading a file.  
Commands Used:  
First, list the files  
ls

Then, just read the file:  
cat readme

The password will show up right there.

## Level 1 → Level 2

Task:  
The password is in a file named \- (just a single dash).  
Challenge:  
The dash is a special character, so you can’t just type cat \- or it won’t work.  
Commands Used:  
So, you gotta do it like this:  
cat ./-

That should print the password.

## Level 2 → Level 3

Task:  
Find the password in a file called spaces in this filename.  
Challenge:  
The filename has spaces, so you need to handle that.  
Commands Used:  
You can use quotes:  
`cat "spaces in this filename"`

## Level 3 → Level 4

Task:  
There’s a hidden file in the inhere directory with the password.  
Challenge:  
Hidden files start with a dot and don’t show up with a normal ls.  
Commands Used:  
Go into the directory and list everything:

cd inhere  
ls \-al

Then just read the hidden file (it’s probably called .hidden):

cat .hidden

## Level 4 → Level 5

Task:  
Find the only human-readable file in the inhere directory.  
Challenge:  
Most files are not readable, only one is.  
Commands Used:  
Check which file is readable:  
file ./\*

Then, when you find the right one (it’ll say ASCII text), do:  
cat ./-file07

(Your file name might be different, just use the one that’s readable.)

## Level 5 → Level 6

Task:  
There’s a file somewhere under inhere that’s human-readable, 1033 bytes, and not executable.  
Challenge:  
You have to search for it with the right options.  
Commands Used:  
Try this:  
find . \-type f \-size 1033c \! \-executable

Then, when you see the file, do:  
cat ./maybehere07/.file2

(Again, your file name might be different.)

## Level 6 → Level 7

Task:  
Find a file owned by user bandit7, group bandit6, and it’s 33 bytes.  
Challenge:  
You gotta search the whole system, but you’ll get a lot of permission errors.  
Commands Used:  
This will help:  
find / \-user bandit7 \-group bandit6 \-size 33c 2\>/dev/null

Then just cat the file you find.

## Level 7 → Level 8

Task:  
The password is in data.txt, next to the word millionth.  
Challenge:  
You need to find the right line.  
Commands Used:  
Just do:

grep millionth data.txt

Or if you want just the password:

grep millionth data.txt | awk '{print $2}'

## Level 8 → Level 9

Task:  
Find the only line in data.txt that occurs just once.  
Challenge:  
There’s a lot of repeated lines, only one is unique.  
Commands Used:  
Sort and filter:

sort data.txt | uniq \-u

## Level 9 → Level 10

Task:  
The password is in data.txt, but it’s hidden among a bunch of weird characters, and it’s got a bunch of \= signs before it.  
Challenge:  
You need to pull out the readable strings.  
Commands Used:  
Try this:

strings data.txt | grep '=='

## Level 10 → Level 11

Task:  
The password is base64 encoded in data.txt.  
Challenge:  
You need to decode it.  
Commands Used:  
Just run:

base64 \-d data.txt

## Level 11 → Level 12

Task:  
The password is in data.txt, but all the letters are rotated by 13 (ROT13).  
Challenge:  
You need to decode ROT13.  
Commands Used:  
This will do it:

cat data.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m'

## Level 12 → Level 13

Task:  
The password is in data.txt, but it’s a hexdump of a file that’s been compressed a bunch of times.  
Challenge:  
You have to reverse the hexdump and then keep decompressing.  
Commands Used:  
First, reverse the hexdump:

xxd \-r data.txt \> data

Then, check what kind of file it is:  
file data

Depending on what it says, you might need to do:  
mv data data.gz && gzip \-d data.gz  
mv data data.bz2 && bzip2 \-d data.bz2  
tar xf data.tar

Just keep checking the file type and decompressing until you get the password.

## Level 13 → Level 14

Task:  
You get a private SSH key. Use it to log in as bandit14 and read the password from /etc/bandit\_pass/bandit14.  
Challenge:  
You need to use the SSH key to log in.  
Commands Used:  
First, set the right permissions:

chmod 600 sshkey.private

Then log in:

ssh \-i sshkey.private bandit14@localhost \-p 2220

Once you’re in, just do:

cat /etc/bandit\_pass/bandit14

## Level 14 → Level 15

Task:  
Send the current password to port 30000 on localhost using netcat.  
Challenge:  
You need to use netcat to talk to a service.  
Commands Used:  
Just do:

echo "\<current\_password\>" | nc localhost 30000

