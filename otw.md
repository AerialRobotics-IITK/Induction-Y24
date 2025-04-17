#  Bandit Walkthrough – OverTheWire

##  Initial SSH Login

```bash
ssh bandit0@bandit.labs.overthewire.org -p 2220
```



## Level 0 >> 1

- Read the `readme` file using `cat`.
- **Password:** `ZjLjTmM6FvvyRnrb2rfNWOZOTa6ip5If`

---
##  Initial SSH Login

```bash
ssh bandit1@bandit.labs.overthewire.org -p 2220
```

## Level 1 >> 2

- File name is `-`, which conflicts with stdin/stdout.
- Use `cat ./-` to read it.
- **Password:** `263JGJPfgU6LtdEvgfWU1XP5yac29mFx`

---
##  Initial SSH Login

```bash
ssh bandit2@bandit.labs.overthewire.org -p 2220
```

## Level 2 >> 3

- Filename has spaces.
- Use `ls` to get the name, and wrap it in quotes: `cat "file name here"`.
- **Password:** `MNk8KNH3Usiio41PRUEoDFPqfxLPlSmx`

---
##  Initial SSH Login

```bash
ssh bandit3@bandit.labs.overthewire.org -p 2220
```

## Level 3 >> 4

- Look for a hidden file in the `inhere` directory.
- Use `ls -a` to view hidden files.
- **Password:** `2WmrDFRmJIq3IPxneAaMGhap0pFhF3NJ`

---
##  Initial SSH Login

```bash
ssh bandit4@bandit.labs.overthewire.org -p 2220
```

## Level 4 >> 5

- Find a human-readable file in `inhere`.
- Use:
  ```bash
  find . | xargs -I '{}' file '{}'
  ```
- Look for `ASCII text`, then use `cat`.
- **Password:** `4oQYVPkxZOOEOO5pTW81FB8j8lxXGUQw`

---
##  Initial SSH Login

```bash
ssh bandit5@bandit.labs.overthewire.org -p 2220
```

## Level 5 >> 6

- Target file: non-executable, human-readable, size = 1033 bytes.
- Use:
  ```bash
  find . -type f -size 1033c ! -executable -exec file {} \; | grep "ASCII text"
  ```
- Then `cat` the correct file.
- **Password:** `HWasnPhtq9AVKe0dmk45nxy20cvUa6EG`

---
##  Initial SSH Login

```bash
ssh bandit6@bandit.labs.overthewire.org -p 2220
```

## Level 6 >> 7

- Just login.
- **Password:** `morbNTDkSW6jIlUc0ymOdMaLnOlFVAaj`

---
##  Initial SSH Login

```bash
ssh bandit7@bandit.labs.overthewire.org -p 2220
```

## Level 7 >> 8

- Look for a line with the word `millionth` in `data.txt`.
- Use:
  ```bash
  grep "millionth" data.txt
  ```
- **Password:** `dfwvzFQi4mU0wfNbFOe9RoWskMLg7eEc`

---
##  Initial SSH Login

```bash
ssh bandit8@bandit.labs.overthewire.org -p 2220
```

## Level 8 >> 9

- Find the **unique** line in `data.txt`.
- Use:
  ```bash
  sort data.txt | uniq -u
  ```
- **Password:** `4CKMh1JI91bUIZZPXDqGanal4xvAg0JM`

---
##  Initial SSH Login

```bash
ssh bandit9@bandit.labs.overthewire.org -p 2220
```

## Level 9 >> 10

- Find the password among encoded strings with `=====` prefix.
- Use:
  ```bash
  strings data.txt | grep "====="
  ```
- **Password:** `FGUW5ilLVJrxX9kMYMmlN4MgbpfMiqey`

---
##  Initial SSH Login

```bash
ssh bandit10@bandit.labs.overthewire.org -p 2220
```

## Level 10 >> 11

- Base64-encoded string.
- Decode with:
  ```bash
  echo "encoded string" | base64 -d
  ```
- **Password:** `dtR173fZKb0RRsDFSGsg2RWnpNVj3qRr`

---
##  Initial SSH Login

```bash
ssh bandit11@bandit.labs.overthewire.org -p 2220
```

## Level 11 >> 12

- File is encoded with ROT13 cipher.
- Decode with:
  ```bash
  cat data.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m'
  ```
- **Password:** `7x16WNeHIi5YkIhWsfFIqoognUTyj9Q4`
