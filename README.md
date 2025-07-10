# Console-Banking-Application

A simple C++ console program that simulates a bank service where users can manage their accounts securely using password hashing(SHA-256).

---

## Features

- Create new back accounts
- Login using SHA-256 hashed passwords
- Basic Transaction: Deposit and Withdraw money
- View accounts
- Transaction Logs and tracking
- Storing important information in binary format(using `fread`, `fwrite`)
- Modular code with separate header and source files

---

## Dependecies

- `OpenSSL` - SHA-256 password hashing
- `ctime` - Displaying Log times

---

## Build Instruction

### Install OpenSSL

Linux : `sudo apt install libssl-dev`
Windows: `pacman -S mingw-w64-ucrt-x86_64-openssl`

### Build Command
`g++ main.cpp basic_info_manager.cpp secure_info_manager.cpp log_manager.cpp -o a -lssl -lcrypto`

### Run Command
`./a`

---

## About
This was an assignment for CSE-1201 course
