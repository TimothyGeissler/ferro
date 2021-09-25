#include <stdio.h>
#include <stdlib.h>
//#include "parser.h"
#include <string.h>

void print_ln(char c) {

}

int first_index_of(char *str, char key) {//index begins at 1
    char *e = strchr(str, key);
    int ans = (int) (e - str) + 1;
    if (ans >=0 && ans <= strlen(str)) { //catch key not found
        return ans;
    } else {
        return -1;
    }
}

int last_index_of(char *str, char key) {
    char *e = strrchr(str, key);
    int ans = (int) (e - str) + 1;
    if (ans >=0 && ans <= strlen(str)) { //catch key not found
        return ans;
    } else {
        return -1;
    }
}

char* substring(char* str, int begin, int end) { //incluse
    char *substr;
    substr = malloc(sizeof(char) * 64);
    for (int i = begin; i <= end; i++) {
        substr[i - begin] = *(str + begin);
        str++;
    }
    return substr;
}

int get_command(char cmd[]) { //get command prefix before (), return corresponding cmd code
    char *command;
    char key = '(';
    int index = first_index_of(cmd, key);
    //printf("beginning index: %d", index);   
    command = substring(cmd, 0, index - 2);
    //printf("Command: %s", command);
    if (strcmp(command, "print") == 0) {
        //printf("Print op\n");
        return 1; //print code
    }
    return 0; //incorrect syntax
}



void printer(char cmd[]) {
    //get inbetween () for print function
    char paren_begin = '(';
    char paren_end = ')';
    int index1 = first_index_of(cmd, paren_begin);
    int index2 = last_index_of(cmd, paren_end);
    char * content = substring(cmd, index1, index2 - 2);
    printf("%s\n", content);
}

void cmd_check(char cmd[]) { //get command code & pass to execution function
    int pref;
    pref = get_command(cmd);
    //printf("Entered command: '%s'\nPrefix: %d", cmd, pref);
    printf("%c", pref);
    if (strcmp(cmd, "HelloWorld") == 0) {
        printf("Hi back");
    } if (pref == 1) {
        //printf("cmd code: 1 - print");
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
