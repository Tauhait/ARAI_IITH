#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "echoClient.h"

#define MAXLINE 100 /*max text line length*/
#define SERV_PORT 5000 /*port*/

int sockfd;

int isValid(char *msg){
    // printf("%s\n", msg);
    int strLen = strlen(msg);
    // printf("%d\n", strLen);
    if(strLen != (MAXLINE - 1)){
        perror("Message length should be 8 chars!!");
        return 1;
    }
    int idx;
    for(idx = 0; idx < 8; idx++){
        // printf("%d\n", msg[idx] - '0');
        if((msg[idx] - '0') != 0 && (msg[idx] - '0') != 1){
            perror("Message chars should be either 0/1!!");
            return 1;
        }
    }
    return 0;
}
int createSocket(const char *ipAddr){
    struct sockaddr_in servaddr;
    //Create a socket for the client
    //If sockfd < 0 there was an error in the creation of the socket
    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Problem in creating the socket");
        return 2;
    }
        
    //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= inet_addr(ipAddr);
    servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
        
    //Connection of the client to the socket 
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("Problem in connecting to the server");
        return 3;
    }
    return 0;
}
int sendCommand(){
     char recvline[MAXLINE];
     //char sendline[MAXLINE];
     char sendline[MAXLINE] = "A,F,0,0,0,1,0,1,L,1,W\r\n";
     //printf("Type your command: ");
     
     //while (fgets(sendline, MAXLINE, stdin) != NULL){
     while(1){
        //if(isValid(sendline) != 0){
        //    return 1;
        //} 
        send(sockfd, sendline, strlen(sendline), 0);    
        if(recv(sockfd, recvline, MAXLINE,0) == 0){
            //error: server terminated prematurely
            perror("The server terminated prematurely"); 
            return 4;
        }
        printf("%s", "String received from the server: ");
        fputs(recvline, stdout);
        //printf("\nType your next command: ");
        //fgets(sendline, MAXLINE, stdin);//Needed to eat up carriage return
    }
    return 0;
}
int passMessage(const char *ipAddr){

    if(createSocket(ipAddr) != 0){
        perror("ERROR during socket creation!!");
        return 1;
    }
    printf("%s\n", "Socket has been created!!");
    if(sendCommand() != 0){
        perror("ERROR sending message!!");
        return 1;
    }
    return 0;
}
