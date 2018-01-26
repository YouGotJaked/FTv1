/* 
 * File:   server.c
 * Author: jakeday
 *
 * Created on January 17, 2018, 9:58 PM
 *
 * Description: This file waits for a connection request from the client, receives
 * the name of the file, opens the file
 *
 * Usage: To compile, open Terminal and type the following: "gcc -o server server.c"
 * To run, type: "./server <port number>"
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define LENGTH 5

int main(int argc, char** argv) {
    int listenfd  = 0, connfd = 0, n;
    struct sockaddr_in serv_addr;
    char data_buff[LENGTH], name_buff[16];
    FILE *fp;

    if (argc != 2) {
        printf("Usage: %s <port number>\n", argv[0]);
        return -1;
    }
    
    // zero out server
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(data_buff, '0', LENGTH);

    // setup
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1])); 
    
    //create socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Could not create socket. %s\n", strerror(errno));
        return -1;
    }
    
    // bind socket
    if ((bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("Could not bind socket. %s\n", strerror(errno));
        return -1;
    }
    
    // listen
    if (listen(listenfd, 10) < 0) {
        printf("Could not open socket for listening. %s\n", strerror(errno));
        return -1;
    }
    
    while (1) {
        // accept
        if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) < 0) {
            printf("Could not open socket. %s\n", strerror(errno));
            return -1;
        }
        
        // get file name from client
        while (read(connfd, name_buff, sizeof(name_buff)) > 0) {
            fp = fopen(name_buff, "wb");
            if (fp == NULL) {
                return -1;
            } else {
                break;
            }
        }
        
        // read data from client
        while ((n = read(connfd, data_buff, LENGTH)) > 0) {
            fwrite(data_buff, sizeof(char), n, fp);
        }
	
        fclose(fp);
        close(listenfd);
        return 0;
    }
}
