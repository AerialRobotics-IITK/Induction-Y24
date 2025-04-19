**Bandit Wargames Writeup Code**

Level 0:

ssh command

using code ssh <username@hostname> -- p 2220

given password bandit0

Level 0 -1:

Using cat command we read the contents of the readme file to gte the
required password.

cat readme gives us the content of the readme file

Level 1 - 2 :

We need to find a file with name -

We need to write command cat ./- in order to access the contents of the
file as directly using -- would result in an error as -- has a specific
function in linux shell.

263JGJPfgU6LtdEvgfWU1XP5yac29mFx

Level 2 -- 3:

We need to access contents of a file named spaces in the filename

We would use cat spaces\\ in\\ this\\ filename.

MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx

Level 3 -- 4:

We need to access content of a hidden file.

We use command cd inhere to change directory from home to inhere.

We then use ls -alps to list out all type of files.

We then choose the hiding from you file and read the contents using cat.

Level 4 -- 5:

We need to find the only human readable file.

For that, we need to access the type of file using find . -type f \|
xargs file command.

Xargs file→ passes those file paths to the *file* command, which detects
and prints each file\'s type

After ths we choose the file 007 as it is the only ASCII text type of
file

Then use cat filename to access the password.

Level 5 -- 6:

We need to use command find . -type f -size 1033c to get the file.

-size 1033c for the size and type f for the humamn readable condition.

Level 6 -- 7:

We need to use command cd inhere to change directory and then use ind /
-type f -user bandit7 -group bandit6 -size 33c 2\>/dev/null

\- user for the user

\- group for the group owner

\- 2\>/dev/null: to remove all permission denied files.

Level 7 -- 8:

We need to find the password next to the word "millionth"

So we use the command grep "millionth" data.txt

grep command to find all the files which contain the word.

Level 8 -- 9:

The password is the line which occurs only once.

We can use the sort filename.txt \| uniq -u command.

If there are double lines, sort brings them together, while uniq -u
prints the unique lines.

Level 9 -- 10:

Using strings command we access all the strings of the file and by using
the grep "==" we find strings preceded by ==

strings data.txt \| grep '=='

Level 10 -- 11:

We use the grep '=' command the get the most password looking like base
64 encoded data. Then we use the base64 -d command to get the password.

Strings data.txt \| grep '='

echo "base64 encoded" base64 -d

We're using echo to ****feed the Base64-encoded string into the base64
command****.

Level 11-- 12:

We need to find the rotated alphabets.

For that we use the tr command.

tr \'A-Za-z\' \'N-ZA-Mn-za-m\' \< data.txt

\'A-Za-z\' -- matches the upper case and lower case letters

'N-ZA-Mn-za-m\' -- Rotates them by 13 positions

tr translates the lines.

Level 12-- 13:

We use the following code for de-compressing the file:

mv data.bin final.gz (if its a gunzip compressed file)

We rename the file to final

Then we decompress it using gunzip.

Gunzip final.gz . Now we check for the file type, which if still needs
to be compressed, will require from us to repeat the same steps.

FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn

Level 13-- 14:

This level does not require any password but wants us to use our private
key instead of a password to login to level 14. For that, we need to
check first if our ssh key is private using cat sshkey.private.

Then we need to change the mode so that only **we **are able to read or
write the file. Then we can use the private key to login.

ssh -i sshkey.private bandit14@localhost -p 2220

**-i sshkey.private**: tells SSH to use ****your private key**** instead
of a password

**bandit14@localhost**: log in as **bandit14** on the ****same
machine****

Level 14 -- 15:

For this level we need to find a password to level 15-16 by giving a
localhost or password of level 14.

The password to level 14 could be accessed by cat
/etc/bandit_pass/bandit14

Then writing nc localhost 30000 would allow us to write our password.
