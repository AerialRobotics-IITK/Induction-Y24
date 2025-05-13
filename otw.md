# My Journey Through the Bandit Wargame

## Level 0
Started by connecting to the Bandit server using SSH (Secure Shell Protocol). SSH creates an encrypted tunnel for secure communication over unsecured networks. Successfully logged in using the provided username, password, server address, and port.

## Level 0 → Level 1
Found the password stored in a readme file in the home directory. Created a text file using the nano editor to keep track of passwords as I progressed through the levels.

## Level 1 → Level 2
Encountered a file named with just a hyphen (-), which the terminal normally interprets as an option flag. Solved this by using the './' prefix to specify it's a file in the current directory rather than an option.

## Level 2 → Level 3
Had to access a file with spaces in its name. Learned to use double quotes around the filename when using the cat command to read its contents.

## Level 3 → Level 4
Navigated to the specified directory and discovered the password was in a hidden file. Used the 'ls -la' command to list all files, including hidden ones that start with a dot.

## Level 4 → Level 5
Found multiple files in a directory with different file types. Used 'file ./*' to check the type of each file, then opened the one containing ASCII text to find the password.

## Level 5 → Level 6
Needed to locate a file of a specific size. Used the find command with size parameter: 'find -type f -size 1033c' to identify the correct file.

## Level 6 → Level 7
Searched for a file matching multiple criteria (owner, group, and size) using: 'find / -type f -user bandit7 -group bandit6 -size 33c 2>/dev/null'. Used '2>/dev/null' to suppress permission denied errors.

## Level 7 → Level 8
Had to parse a large text file to find a password next to a specific word. Used the grep command to filter out just the line containing that word.

## Level 8 → Level 9
Needed to find the only unique line in a file. Applied 'sort' first (crucial step) and then used 'uniq -u' to identify the non-repeating line, as uniq only works on adjacent duplicates.

## Level 9 → Level 10
Extracted human-readable strings from a binary file using the 'strings' command, then piped the output to grep to find lines containing '==' characters.

## Level 10 → Level 11
Encountered a base64 encoded file. Learned that base64 is commonly used for transmitting binary data in text-only systems. Decoded it using 'base64 -d' to reveal the password.

## Level 11 → Level 12
Found a file with text encrypted using character rotation (ROT13). Used the 'tr' (translate) command to shift each letter 13 positions in the alphabet.

## Level 12 → Level 13
Worked with a hexdump file that contained compressed data. Created a temporary directory, copied the file there, and reversed the hexdump. After identifying it as gzip-compressed using the 'file' command, began the decompression process.

Each level built on the previous ones, introducing new commands and concepts while reinforcing what I'd already learned about Linux file systems and command-line operations.
