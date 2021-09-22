int sumString(char *ptr, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        //printf("%s -> %d\n", (ptr + i), *(ptr + i));
        sum = sum + *(ptr + i);
    }
    return sum;
}