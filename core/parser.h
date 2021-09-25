/*int sumString(char *ptr, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        //printf("%s -> %d\n", (ptr + i), *(ptr + i));
        sum = sum + *(ptr + i);
    }
    return sum;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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