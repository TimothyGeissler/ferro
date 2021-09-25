#include <stdio.h>
#include <stdlib.h>
//#include "parser.h"
#include <string.h>

struct data_sys {
    int type_code; //0 = int
    char *name; //variable name
    int index; //index in array
};

struct data_sys sys[256]; //track variables
int *integer_list; //int space
int sys_counter = 0;
int int_counter = 0;


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
    } else if (strcmp(command, "int") == 0) {
        return 2; //store int
    }
    return 0; //incorrect syntax
}

void print_sys() {
    for (int i = 0; i < sys_counter; i++) {
        printf("Index: %d, Type: %d, Name: %s\n", sys[i].index, sys[i].type_code, sys[i].name);
    }
}


char* get_contents_paren(char cmd[], char paren_begin, char paren_end) {
    //get inbetween ()
    //char paren_begin = '(';
    //char paren_end = ')';
    int index1 = first_index_of(cmd, paren_begin);
    int index2 = last_index_of(cmd, paren_end);
    char *content = substring(cmd, index1, index2 - 2);
    return content;
}

void printer(char cmd[]) {
    //get inbetween () for print function
    char *content = get_contents_paren(cmd, '(', ')');

    //check if string or var
    if (first_index_of(content, '"') == 1 && last_index_of(content, '"') == strlen(content)) {
        //is string - paren ""
        char *str = get_contents_paren(content, '"', '"');
        printf("%s\n", str);
    } else {
        //is a var
        //search sys
        int found = 0;
        //*fix segfault when uninit. var is called*
        for (int i = 0; i < 256; i++) {
            if (strcmp(sys[i].name, content) == 0) {
                //found entry
                if (sys[i].type_code == 0) {
                    //is an int
                    printf("%d\n", integer_list[sys[i].index]);
                    found = 1;
                }
                break;
            }
        }
        if (found == 0) {
            printf("Variable not initialized");
        }
    }

    
}

void assign_int(char cmd[]) {
    //get contents of ()
    char *content = get_contents_paren(cmd, '(', ')');
    //get variable name
    int comma_delimiter = first_index_of(content, ',');
    char *var = substring(content, 0, comma_delimiter - 2); //var = variable name
    //get variable value
    char *val = substring(content, comma_delimiter, strlen(content));
    int value;
    sscanf(val, "%d", &value);
    //printf("Contents for int assign: %s - > %s", val, var);
    //store in sys logger
    sys[sys_counter].type_code = 0;
    sys[sys_counter].name = var;
    sys[sys_counter].index = int_counter; 
    //store in heap
    integer_list[int_counter] = value;
    sys_counter++;
    int_counter++;
    print_sys();
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
    } else if (pref == 2) {
        assign_int(cmd);
    }
}

int main(int argc, char const *argv[]) {
    integer_list = (int*) malloc(sizeof(int) * 256); //reserve space for 256 ints

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
