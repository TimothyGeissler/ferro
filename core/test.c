#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int first_index_of(char *str, char key) {//index begins at 1
    char *e = strchr(str, key);
    int ans = (int) (e - str) + 1;
    if (ans >=0 && ans <= strlen(str)) {
        return ans;
    } else {
        return -1;
    }
}

int last_index_of(char *str, char key) {
    char *e = strrchr(str, key);
    int ans = (int) (e - str) + 1;
    if (ans >=0 && ans <= strlen(str)) {
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

int main(int argc, char const *argv[])
{
    char str[] = "HelloWorld";
    char key = 'l'; 
    int index = first_index_of(str, key);

    printf("Index: %d\n", index);

    char *sub = substring(str, 3, 6);
    printf("Substr: %s\n", sub);
    free(sub);

    int lio = last_index_of(str, key);
    printf("Last index of: %d\n", lio);
    

    char cmd[] = "print(HelloWorld)";
    char key_par = '(';
    char key_end = ')';
    int index_par = first_index_of(cmd, key_par);
    char *sub_cmd = substring(cmd, 0, index_par-2);
    printf("for cmd print() -> %s", sub_cmd);

    int last_index = last_index_of(cmd, key_end);
    char *data = substring(cmd, index_par, last_index - 2);
    printf("contents: %s", data);

    char* num = "6";
    int res;
    sscanf(num, "%d", &res);
    printf("Converted: %d\n", res);


    char *string = "\"hello\"";
    char quote = '"';
    printf("%d, %d, %ld\n", first_index_of(string, '"'), last_index_of(string, '"'), strlen(string));
    
    printf("%c\n", quote);
    return 0;
}
