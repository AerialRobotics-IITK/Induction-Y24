Level 0

Got error: Trying to log in to ssh server through Port 22

Learned how to log in through different port, by putting -p 2220

Went in bandit0, gave password as bandit0, accepted

Level 0-l

Used man and help to understand suggested commands

Showed home directory (contained file readme)

Printed out contents of file readme, got password

Went in bandit1, gave password, accepted

Level 1-2

Showed home directory (contained file -)

Tried to print out contents of file -, did not work

Instead it took text and printed it back out

Learned that hyphen reads from stdin and prints out

Used Ctrl+D to exit this mode

Learned that for accesing "file" -, we need to prefix ./ (as -- has
meaning as a command, ./ is used to treat it as a normal -)

Printed out contents of file -, got password

Went in bandit2, gave password, accepted

Level 2-3

Showed home directory (contained file "spaces in this filename")

Tried to print out contents of file "spaces in this filename", got error

Terminal considers each word to be a file and says file not found

Learned that enclosing full filename in quotes resolves space issue

Printed out contents of file "spaces in this filename", got password

Went in bandit3, gave password, accepted

Level 3-4

Showed home directory (contained directory inhere)

Went into directory inhere

Showed nothing

Learned that -al is use along wih ls, to list all files, including
hidden

Found file \...Hiding-From-You (. prefix denotes hidden file)

Printed out contents of file \...Hiding-From-You, got password

Went in bandit4, gave password, accepted

Level 4-5

Showed home directory (contained directory inhere)

Went into directory inhere

Showed multiple files (-file00 to -file09)

Learned that file command gives info on files, and ./\* with file gives
type of data of all files

Showed type of data, -file07 contains ASCII text, which is human
readable

Printed out contents of file -file07, got password (used ./, if it was
only -file07, terminal will think it is a command)

Went in bandit5, gave password, accepted

Level 5-6

Showed home directory (contained directory inhere)

Went into directory inhere

Showed multiple directories

Learned about find command, used to find a file based on some arguments,
-size finds file of given siz which is given by number followed by
letter prefix (c for bytes, b for halfbytes)

Returned .file2 in maybehere07 for command find -size 1033c

Printed out contents of the above file, got password

Went in bandit6, gave password, accepted

Also learned about cd .. to go prev directory and cd \~ to go home
directory

Level 6-7

Showed home directory (nothing present)

Learned that in find, / used for searching entire harddisk, . for
current directory and \~ for home directory of current user.

Also learned -user is used to find user, -group is used to find group
when used with size

Used these stuff to find password located in
/var/lib/dpkg/info/bandit7.password

Printed out contents of the above file, got password

Went in bandit7, gave password, accepted

Level 7-8

Showed home directory (contained file data.txt)

Printed contents of data.txt, very huge

Learned about grep command, which searches for stuff and patterns in
file

Also learned about pipe (\|), which takes stdout of one command and
feeds it as stdin of another command

Used cat data.txt \| grep millionth, found password

Went in bandit8, gave password, accepted

Level 8-9

Showed home directory (contained file data.txt)

Printed contents of data.txt, very huge

Learned about sort command, which sorts text in files and uniq -u
command, which finds text which are not repeated

Used cat data.txt \| sort \| uniq -u, found password

Went in bandit9, gave password, accepted

Level 9-10

Showed home directory (contained file data.txt)

Printed contents of data.txt, got gibberish

Learned about strings, to use instead of cat, to get human readable
stuff

Used strings and grep to find password, strings data.txt \| grep =,
found password in found text

Went in bandit10, gave password, accepted

Level 10-11

Showed home directory (contained file data.txt)

Printed contents of data.txt, got text which is not password

learned about --decode command, which is used to decode encoded data of
some specific base

Used cat data.txt \| base64 --decode, found password

Went in bandit11, gave password, accepted

Level 11-12

Showed home directory (contained file data.txt)

Printed contents of data.txt, got text which is not password

Learned about tr command, which translates or traces one set of letters
to the next

Used the command to implement rotate13 algo (move forward 13 letters)

cat data.txt \| tr abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM, found password

Went in bandit12, gave password, accepted

Level 12-13

Showed home directory (contained file data.txt)

Printed contents of data.txt, got gibberish

Learned about mkdir command to make a directory, and cp command to copy
file

Made a directory in /tmp and copied file data.txt to it

changed terminal path to this directory

used file command to check type, found to be ascii text

Throughout the process, all things learnt -

Learned about xxd command, which makes hexdump, and -r to reverse the
process

Learned about mv command, to rename file and give proper extension

Learned about gzip command to handle gzip files, and -d to decompress
gzip files

Learned about bzip2 command to handle bzip2 files, and -d to decompress

Learnt about tar archive file, command to handle it, and xvf parameter

\- checked filetype, depending on type command was used to decompress,
and given apprpriate extension using mv command until password is
received

Went in to bandit13, gave password, accepted
