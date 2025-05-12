**Level 0 - Using Secure Shell Protocol**

It’s a cryptographic network protocol for operating network services securely over an unsecured network → used for remote login and command line execution

It’s speciality is that information is transmitted through an encrypted mechanism in a manner such that it is secure even if an observer has access to the entire data stream

Logged into the Bandit game SSH using the given username, password, server and port.

**Level 0 → Level 1 - Finding the password in a readme on home**

Found the password on a readme file in home and created a text file using the nano command to keep a list of passwords

**Level 1 →Level 2 - Finding the password in a readme on home with a catch**

As the file name is a hyphen, to tell the terminal that is not an option we can ask it to search in the directory using - ‘./’

**Level 2 → Level 3 - Accessing a readme with a multi-word title**

Just use double quotes to call the file with cat

**Level 3 → Level 4 - Hidden password**

Navigated to the directory with the password file, use -la option with ls to list all and then access the password

**Level 4 → Level 5 - Different file types in the directory**

We use file ./\* to check out the different file types and open the one with ASCII text

**Level 5 → Level 6 - Find a file of specific size**

Searched for a file of type 1033c : find -type f -size 1033c

**Level 6 → Level 7 - Search for a file with the required specifications**

find / -type f -user bandit7 -group bandit6 -size 33c 2>/dev/null

2>/dev/null is used to remove any permission denied flags

**Level 7 → Level 8 - Parse a text file to find the password next to a provided word**

Done using the grep command

**Level 8 → Level 9 - Parse text file to find line**

First sort and use uniq → sorting is crucial and must be done before uniq as uniq only removes adjacent duplicates

**Level 9 → 10 - extract human readable string**

Use strings command and then grep search for ‘==’

**Level 10 →11 - base64 encoded data**

Base64 is a way to encode binary data into a set of readable ASCII characters — usually used for transmitting data (like email attachments, images, or tokens) in systems that can only handle text. It uses 64 characters: A–Z, a–z, 0–9, +, and /. It often ends with = for padding.

Use base64 -d where d stands for decode

**Level 11 → Level 12 - character rotation**

This is a substitution cipher and the Rot13 cipher on being implemented twice returns the same letter.

For rot13, the translate command will help us where A-Z will be mapped to N-ZA-M, and similarly for lowercase characters

**Level 12 → Level 13 - hexdump file**

Hex Dump is a human readable representation of binary data Hex Dumps can be used to figure out the type of a file. Each file type has a magic number/file signature. You can find lists with a collection of these different file signatures online. T

Compression is a method of encoding that aims to reduce the original size of a file without losing information (or only losing as little as possible). An Archive File is a file that contains one or multiple files and their metadata. This can allow easier portability.

Make a directory in temp and copy the data.txt file from home to this

Then reverse the hexdump

1. Gzip compressed, data.bin renamed to data.gz then decompressed using gunzip command
2. Bzip2 compressed, data renamed to data.bz2 then decompressed using bunzip2 command
3. Gunzip again
4. Now we obtain a Posix Tar Archive file- gave it the correct extension and then extracted it

Process continued a few more times until an ASCII text file was obtained with the password

**Level 13 → Level 14 - SSH Private Key**

The public key is placed on the computers that should allow access (the remote host) to the user that owns the private key. Like with the password, it is important that only the user knows/owns the private key. The -i flag allows login with the private key.

scp is a command that uses SSH to transfer data over the network. The syntax to get a file from a remote host looks like the following: scp -P &lt;port&gt; &lt;user&gt;@&lt;IP&gt;:&lt;remotefilepath&gt; &lt;localfilepath&gt;. To send a file to a remote host, the local file path needs to stand at the beginning.

An alternative to this method is starting a simple web server with python. This is useful when you do not have ssh access. On the machine where the file is you need to start the webserver with the following command: python3 -m http.server (best is to do it in the directory of the file). On the receiving machine you then just have to send an HTTP request: wget http://&lt;ip&gt;:8000/&lt;pathtofile&gt;

Found the ssh private key in a file in the home, copied it to a local file then used it to log in as local host for level 14

**Level 14 → Level 15 - Find the password of the current level and submit to local host**

Localhost is a hostname and its IP address is ‘127.0.0.1’. It is used to access network services on the same device that is running these services.

nc or netcat is a command that allows to read and write data over a network connection. It can be used for TCP and UDP connections. To connect to a service (as client) on a network the command syntax is the following: nc &lt;host&gt; &lt;port&gt;. To create a server that listens to incoming packets, the command looks like this: nc -l &lt;port&gt;.

Password found in etc/bandit_pass/bandit14

Submitted to localhost using nc command

**Level 15 →Level 16 - Submit over local host and retrieve next pass using SSL encryption**

OpenSSL is a library for secure communication over networks. It implements the Transport Layer Security (TLS) and Secure Sockets Layer (SSL) cryptographic protocols that are, for example, used in HTTPS to secure the web traffic. openssl s_client is the implementation of a simple client that connects to a server using SSL/TLS.

Connected over SSL encryption, submitted the password and obtained the password for Level 16

GNU nano 2.3.1 File: bandit_notes.txt Modified

Level 1 password

ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If

Level 2 password

263JGJPfgU6LtdEvgfWU1XP5yac29mFx

level 3 password

MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx

Level 4 password

2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ

Level 5 password

4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw

Level 6 password

HWasnPhtq9AVKe0dmk45nxy20cvUa6EG

Level 7 password

morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj

Level 8 password

dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc

Level 9 password

4CKMh1JI91bUIZZPXDqGanal4xvAg0JM

Level 10 password

FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey

Level 11 password

dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr

Level 12 password

7x16WNeHIi5YkIhWsfFIqoognUTyj9Q4

Level 13 password

FO5dwFsc0cbaIiH0h8J2eUks2vdTDwAn

Level 14 password

MU4VWeTyJk8ROof1qqmcBPaLh7lDCPvS

Level 15 password

8xCjnmgoKbGLhHFAZlGE5Tmu4M2tKJQo

Level 16 password

kSkvUpMQ7lBYyCM4GBPvCvT1BfWRy0Dx
