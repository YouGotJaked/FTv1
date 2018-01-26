# File Transfer Version 1

This program consists of a client and server that communicate to transfer one file from the client to the server using TCP.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

To compile and run these programs, your machine must be running a Unix-based operating system such as Linux or macOS.

### Compiling with GCC

To compile a .c file, open up Terminal and navigate to the project directory:

```
cd /home/username/yourdirectory
```

Once in the correct directory, type in the following command with "program" being the name of the file being compiled:
```
gcc -o program program.c
```

To run your program, execute the following command:

```
./program
```

## File Descriptions

### server.c

This file requests a connection and sends the name of the file to the server. It then reads the input file and sends it in chuncks of 10 bytes to the server. After sending the file, the client closes the connection and exits.

### client.c
This file waits for a connection request from the client, receives the name of the file, opens the file, and waits for data. Once the client sends the data, the server receives the data in chunks of 5 bytes and writes to the output file.
