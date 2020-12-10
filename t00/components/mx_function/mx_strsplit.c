#include "mx_function.h"

static int mx_count_words(const char *str, char c) {
    if(!str) return -1;
    int count = 0;
    while(*str != '\0') {
        if(*str == c) {
            while(*str == c && *str != '\0')
                str++;
        }
        if (*str != c && *str != '\0')
            count++;
        while(*str != c && *str != '\0') {
            str++;
        }
    }
    return count;
}

static int mx_len_to_delim(char *str, char c) {
    int i = 0;
    if(!str) return 0;
    for (; str[i] != '\0' && str[i] != c; i++)
        ;
    return i;
}

char **mx_strsplit(const char *s, char c) {
    if(!s) return NULL;
    int len = strlen(s);
    if (len == 0)
        return NULL;
    char *start = (char *)s;
    char *finish = (char *)s +(len - 1);
    while(*start == c)
        start++;
    while(finish > start && *finish == c)
        finish--;
    if(start == finish) return NULL;
    char *str = start;
    int count = mx_count_words(s, c);
    char **arr = (char **) malloc(sizeof(char*) * (count + 1));
    int i = 0;
    while(str <= finish) {
        arr[i] = strndup(str, mx_len_to_delim(str, c));
        while(*str && *str != c)
            str++;
        while(*str && *str == c)
            str++;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}




