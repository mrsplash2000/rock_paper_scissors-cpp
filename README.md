## Introduction
This repository contains an example of Rock, Paper And Scissors game in C++ with a few extra features. These extra features include:
- Login And Register Users
- Keeping Track Of Each User's Statistics Throughout SQLite3 Database
- Encrypting Each User's Password Using OpenSSL Library And Storing The Hash In The Database
- Leaderboard Showing Top 3 Players

## How To Compile ?
In order to compile the code, you have to create a build directory and then build using the cmake commands. Here are the instructions based on platform:
### WINDOWS
On CMD within the project folder create a build directory using this command:

```mkdir build```

Go to that directory using the cd command:
 
```cd build```

Compile using these two commands:
  
```cmake ..```

```cmake --build .```

And for running the program, just type main.exe on cmd.

I will add instructions for Linux And Mac systems in the near future.

## History of changes
Below you will see the history of changes within each version.
### v1.0
- Added The Salt Mechanism
- Added Encryption Using The SHA256 Algorithm From The OpenSSL Library
### v1.1
- Changed salt generation function to work with ascii codes instead of using a long predefined charset
- Added a function to check and make sure username and passwords have a length greater than or equal to 7
- Added specific comments to organize and categorize the functions for better understanding and view
