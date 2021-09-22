#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <string.h>

void print_ln(char c) {

}

char get_prefix(char cmd[]) {
    char prefix[64];
    for (int i = 0; i < 64; i++) {
        if (cmd[i] = '[') {
            break;
        }
        prefix[i] = cmd[i];
    }
    return prefix[0];
}

void cmd_check(char cmd[]) {
    //char pref = get_prefix(cmd);
    //printf("%c", pref);
    if (strcmp(cmd, "HelloWorld") == 0) {
        printf("Hi back");
    }
}

int main(int argc, char const *argv[])
{
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
            printf("Entered command: '%s'\n", cmd);
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
