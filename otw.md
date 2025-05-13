OverTheWire (Levels 0–15)

Level 0
Task: Log into the Bandit server using SSH.
Solution: Connected using the command "ssh bandit0@bandit.labs.overthewire.org -p 2220" with the password 'bandit0'.

Level 1
Task: Locate and read a file named 'readme' in the home directory.
Solution: Ran "cat readme" to display the contents of the file, which contained the password.

Level 2
Task: Read a file that is named '-'.
Solution: Used "cat ./-" to tell the shell it's a file, not an option.

Level 3
Task: Find a hidden file inside the 'inhere' directory.
Solution: Used "ls -a inhere" to list hidden files and then "cat .hidden" to read its contents.

Level 4
Task: Find a non-executable file of exactly 1033 bytes in the 'inhere/' directory.
Solution: Ran "find inhere/ -type f -size 1033c ! -executable -exec cat {} \;" to locate and read it.

Level 5
Task: Similar to the previous level, but the target file is somewhere in a deeper directory structure.
Solution: Searched recursively using "find . -type f -size 1033c ! -executable -exec cat {} \;".

Level 6
Task: Look for a file that is 33 bytes in size, owned by user 'bandit7' and group 'bandit6'.
Solution: Used "find / -user bandit7 -group bandit6 -size 33c 2>/dev/null" to find and then "cat" to read it.

Level 7
Task: Read a file with spaces in its name.
Solution: Quoted the filename properly using "cat 'file with spaces in the name'".

Level 8
Task: Decode a password that is base64-encoded and stored in 'data.txt'.
Solution: Used the command "cat data.txt | base64 -d" to decode the contents.

Level 9
Task: Decrypt a password encoded with ROT13 (a simple Caesar cipher).
Solution: Ran "cat data.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m'" to convert it back to readable text.

Level 10
Task: Recover a password from a file presented as a hex dump.
Solution: Reversed the hex dump with "xxd -r data.txt" and filtered out printable characters using "strings".

Level 11
Task: Extract a password from a file that's base64 encoded and gzipped.
Solution: Decoded the file with "base64 -d", saved it as 'data.gz' and extracted it using "zcat".

Level 12
Task: Unpack a compressed file and encoded multiple times using different formats.
Solution: Used "base64 -d", followed by a sequence of tools like "gzip -d", "bzip2 -d", and "tar -xf" after identifying each layer with "file".

Level 13
Task: Log into the next level using a provided SSH private key.
Solution: Saved the key to a file, changed its permissions with "chmod 600", and connected using "ssh -i sshkey.private bandit13@bandit.labs.overthewire.org -p 2220".

Level 14
Task: Connect to a specific port on the server, send the password, and receive the next one.
Solution: Used "nc localhost 30000", pasted the password, and got the next one in response.

Level 15
Task: Similar to Level 14, but this time the connection is encrypted over SSL.
Solution: Ran "openssl s_client -connect localhost:30001", provided the password, and read the response for the next level.