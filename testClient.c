#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "echoClient.h"

int main(int argc, char **argv){
    printf("Send -1 to STOP or 1 to proceed!!\n");
    char input[3];

    if(fgets(input, 3, stdin) != NULL){
        // printf("%s\n", input);
        // printf("%d\n", strcmp(input, "-1"));
        while(strcmp(input, "-1") != 0){
            if(passMessage(argv[1]) == 0){
                printf("Successful termination!!");
            }else {
                break;
            }
            printf("Send -1 to STOP or 1 to proceed!!\n");
        }
    }
    return 0;
}