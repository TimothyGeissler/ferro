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

int get_command(char *cmd, int is_from_file) { //get command prefix before (), return corresponding cmd code
    char *command;
    int index = first_index_of(cmd, '(');
    //printf("beginning index: %d", index);   
    if (is_from_file = 1) {
        //modified offset
        cmd = substring(cmd, 0, strlen(cmd) - 1);
    } 
    command = substring(cmd, 0, index - 2);
    //printf("Command: '%s'\n", command);
    if (strcmp(command, "print") == 0) {
        //printf("Print op\n");
        return 1; //print code
    } else if (strcmp(command, "int") == 0) {
        return 2; //store int
    } else if (strcmp(command, "memlist") == 0) {
        return 3; //list all memory adresses
    } else if (strcmp(command, "rem") == 0) {
        return 4; //delete mem from heap
    } else if (strcmp(command, "read") == 0) {
        return 5; //read file
    } else if (strcmp(command, "exec") == 0) {
        return 6; //execute file
    }
    return 0; //incorrect syntax
}


char* get_contents_paren(char *cmd, char paren_begin, char paren_end) {
    //get inbetween ()
    //char paren_begin = '(';
    //char paren_end = ')';
    int index1 = first_index_of(cmd, paren_begin);
    int index2 = last_index_of(cmd, paren_end);
    char *content = substring(cmd, index1, index2 - 2);
    return content;
}


void printer(char *cmd) {
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

void assign_int(char *cmd) {
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
}

//work on formatting
void memlist() {
    for (int i = 0; i < sys_counter; i++) {
        printf("Addr: %d\t Type: %d Var: %s\t Val:%d\n", sys[i].index, sys[i].type_code, sys[i].name,  integer_list[sys[i].index]);
    }
}

void rem_mem(char *cmd) {
    //get contents of rem
    char *cont = get_contents_paren(cmd, '(', ')');
    int is_addr = first_index_of(cont, '@');
    if (is_addr == -1) {
        //not an address, var name = cont
        
    } else {
        //is an address

    }

}

char *read_file(char *file_name) {
    char *buffer; //file buffer of 1024 bytes
    FILE *file;
    file = fopen(file_name, "r");
    size_t in_read;
    int display;
    char line_builder[64] = {};
    int count = 0;
    char done_code[6] = "--end";

    while (1) {
        display = fgetc(file);
        if (display == EOF) {
            //empty file
            break;
        }
        if (feof(file)) {
            break;
        }
        char ch = (char) display;
        if (display != 10) {
            line_builder[count] = ch;
        }
        if (display == 10) {
            //EOL reached
            //line_builder[count] = '\0';
            
        }
        if (strcmp(line_builder, done_code) == 0) {
            break;
        }
        
        count++;
    }
    buffer = line_builder;
    fclose(file);

    /*if (file) {
        while ((in_read == fread(buffer, 1, sizeof buffer, file)) > 0) {
            //fwrite(buffer, 1, in_read, stdout);
            printf("%s\n", fread(buffer, 1, sizeof buffer, file));
        }
        if (ferror(file)) {
            printf("Error reading file %s\n", file_name);
        }
        fclose(file);
    }*/
    //printf("File Buffer: '%s'\n", buffer);
    return buffer;
}

void cmd_check(char *cmd, int is_from_file);

void exec_from_file(char *filename) {
    char *line = read_file(filename);
    
    //line[strlen(line) - 1] = "\0"; //Remove EOL char
    char* commd = "print(\"HI from fe\")";
    //printf("Command from file: '%s'\n", commd);

    

    cmd_check(commd, 1);
}

void cmd_check(char *cmd, int is_from_file) { //get command code & pass to execution function
    int pref;
    pref = get_command(cmd, is_from_file);
    //printf("Entered command: '%s'\nPrefix: %d", cmd, pref);
    //printf("Pref: %d\n", pref);
    if (pref == 0) {
        printf("Incorrect Syntax");
    } else if (pref == 1) {
        //printf("cmd code: 1 - print");
        printer(cmd);
    } else if (pref == 2) {
        assign_int(cmd);
    } else if (pref == 3) {
        memlist();
    } else if (pref == 4) {
        rem_mem(cmd);  
    } else if (pref == 5) {
        read_file(get_contents_paren(cmd, '(', ')'));
    } else if (pref == 6) {
        exec_from_file(get_contents_paren(cmd, '(', ')'));
    }
}

int main(int argc, char const *argv[]) {
    integer_list = (int*) malloc(sizeof(int) * 256); //reserve space for 256 ints

    char *cmd = malloc(64 * sizeof(char));
    //char cmd[64];
    
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
            cmd_check(cmd, 0);
            //next prompt
            printf("->");
            cmd_size = 0; //reset counter
        
        }
        c = getchar();
        cmd[cmd_size] = c;
        cmd_size++;
    }
    free(cmd);
    
    return 0;
}
