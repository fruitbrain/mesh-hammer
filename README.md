# Plum
Plum, a Lisp-powered Ultimate Modeler

## Build environment setup
### 1. Install MSYS2
  from https://msys2.github.io/.

  Follow all the instructions in there.

### 2. Install MinGW packages in MSYS2
Execute MinGW-w64 Win64 Shell.  
We can find it by typing "mingw-w64" in the windows button
or however they call it.

Brief how-to for the pacman package manager:

* Installing
  ```
  pacman -S <package-name1> <package-name2> ...
  ```

* Removing
  ```
  pacman -R <package-name1> <package-name2> ...
  ```

* Upgrading the whole system
  ```
  pacman -Su
  ```

* Searching
  ```
  pacman -Ss <query-string>
  ```

* Viewing package info
  ```
  pacman -Si <package-name>
  ```

* Searching from installed packages
  ```
  pacman -Qs <package-name>
  ```

Using above commands, install following packages:
- mingw-w64-x86_64-gcc
- mingw-w64-x86_64-make
- git
- tar (For extracting, may use AlZip crap as well)

### 3. Download and extract Chicken Scheme source tarball 
from http://code.call-cc.org/.
  
Recommended version: chicken-4.9.0.1.tar.gz
  
In the MSYS2 shell, go to the directory the tarball is in
by typing:

  ```
  cd C:/Users/<accountname>/<folder>
  ```
(note usage of *forward slash*)
  
Then, extract the tarball by typing:
  ```
  tar zxvf chicken-<verion>.tar.gz
  ```
(I have no idea either)

### 4. Build Chicken Scheme (the tricky part)
We are going to use the formerly installed mingw-w64 toolchains
to build Chicken.

To do so, 


## How to build
```
gcc -c fib.c
csc -o fib-user fib.o fib-user
```
