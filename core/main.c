#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <string.h>

void print_ln(char c) {

}

int first_index_of(char *str, char key) {
    char *e = strchr(str, key);
    return (int) (e - str) + 1;
}

int string_indexof(char *token,char s){ //index of char in str
    if (!token || s=='\0')
        return 0;

    for (;*token; token++)
        if (*token == s)
            return 1;

    return 0;
}

int get_prefix(char cmd[]) { //get command prefix before (), return corresponding cmd code
    char prefix[64];
    char key = '(';
    int index = string_indexof(&key, *cmd);
    printf("index: %d", index);
    for (int i = 0; i < index; i++) {
        prefix[i] = cmd[i];
    }
    //printf("Command: %c\n", prefix[0]);
    if (strcmp(prefix, "print") == 0) {
        return 1; //print code
    }
    return 0; //incorrect syntax
}



void printer(char cmd[]) {
    //get inbetween () for print function
    char key = '(';
    int index = string_indexof(&key, *cmd);
    printf("index: %d", index);
    char content[64];
    for (int i = index; i < strlen(cmd) - index; i++) {
        content[i - index] = cmd[i]; 
    }
    printf("%s", content);
}

void cmd_check(char cmd[]) { //get command code & pass to execution function
    int pref;
    pref = get_prefix(cmd);
    //printf("Entered command: '%s'\nPrefix: %d", cmd, pref);
    printf("%c", pref);
    if (strcmp(cmd, "HelloWorld") == 0) {
        printf("Hi back");
    } if (pref == 1) {
        printf("cmd code: 1 - print");
        printer(cmd);
    }
}

int main(int argc, char const *argv[]) {
    char cmd[64];
    
    //printf("\n-> ");

    int cmd_size = 0;
    
    char c = '\n';

    while(1) {
        
        
        //printf("%c", c);
        /*if (c != '\n') {
            cmd[cmd_size] = c;
            printf("%s", cmd);
        }*/

        if(c == '\n') {
            //Clean string
            cmd[cmd_size - 1] = '\0';
            cmd_check(cmd);
            //next prompt
            printf("->");
            cmd_size = 0; //reset counter
        
        }
        c = getchar();
        cmd[cmd_size] = c;
        cmd_size++;
    }
    
    return 0;
}
