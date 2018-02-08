/* 
 * File:   client.c
 * Author: jakeday
 *
 * Created on January 17, 2018, 9:57 PM
 *
 * Description: This file requests a connection and sends the name of the file to the server.
 * It then reads the input file and sends it in chuncks of 10 bytes to the server.
 * After sending the file, the client closes the connection and exits.
 *
 * Usage: To compile, open Terminal and type the following: "gcc -o client client.c"
 * To run, type: "./client <port number> <ip of server> <source file> <destination file>"
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define LENGTH 10

int main(int argc, char** argv) {
    int sockfd;
    struct sockaddr_in serv_addr;
    size_t bytes;
    char buff[LENGTH];
    
    if (argc != 5) {
        printf("Usage: <port number> <ip of server> <source file> <destination file>\n");
        return -1;
    }
    
    // zero out
    memset(buff, '0', LENGTH); // LENGTH = sizeof(buff)
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    // create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Could not create socket. %s\n", strerror(errno));
        return -1;
    }
    
    // setup
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    
    if (inet_pton(AF_INET, argv[2], &serv_addr.sin_addr) <= 0) {
        printf("inet_pton error occured. %s\n", strerror(errno));
        return -1;
    }
    
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Could not connect to server. %s\n", strerror(errno));
        return -1;
    }
    
    // send output file name to server
    write(sockfd, argv[4], strlen(argv[4]) + 1);
    
    // send file to server
    FILE *fr;
    fr = fopen(argv[3], "r");
    if (fr == NULL) {
        printf("File %s not found.\n", argv[3]);
        return -1;
    }

    while ((bytes = fread(buff, 1, LENGTH, fr)) != 0) {
        write(sockfd, buff, bytes);
    }
}

