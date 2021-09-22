#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

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
    
}

int main(int argc, char const *argv[])
{
    char cmd[64];
    
    //printf("\n-> ");

    int cmd_size = 0;
    
    char c = '\n';

    while(1) {
        
        
        //printf("%c", c);
        if (c != '\n') {
            cmd[cmd_size] = c;
            printf("%s", cmd);
        }

        if(c == '\n') {
            //Clean string
            cmd[cmd_size] = '\0';
            //cmd_check(cmd);
            printf("Entered command: %s\n", cmd);
            //next prompt
            printf("->");
            cmd_size = 0; //reset counter
        
        }
        c = getchar();
        cmd_size++;
    }
    
    return 0;
}
