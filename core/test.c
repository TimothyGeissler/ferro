#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int first_index_of(char *str, char key) {//index begins at 1
    char *e = strchr(str, key);
    return (int) (e - str) + 1;
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
    char key = 'o'; 
    int index = first_index_of(str, key);

    printf("Index: %d", index);

    char *sub = substring(str, 3, 6);
    printf("Substr: %s", sub);
    free(sub);
    return 0;
}
