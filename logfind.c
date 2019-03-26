#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "dbg.h"

#define DEFAULT_FILE "/home/lukas/logfind"

int is_or(int array_size, char **arguments);
int print_file(char path[], int bool_print);
int search_or(char **keywords, char path_to_file[], int size);
int search_and(char **keywords, char path_to_file[], int size);
int
list_directory(char path[], char **keywords, int keywords_size)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char whole_path[256];
            strcpy(whole_path, path);
            strcat(whole_path, dir->d_name);
            if(is_or(keywords_size, keywords) == 0)
            {
                print_file(whole_path, search_or(keywords, whole_path, keywords_size));
            }
            else
            {
                print_file(whole_path, search_and(keywords, whole_path, keywords_size));
            }
        }
        closedir(d);

    }
    return 0;
}
int
check_argument(char *line, char arg[])
{
    if(strstr(line, arg) != NULL)
    {
        return 0;
    }
    return -1;
}
int
print_file(char path[], int bool_print)
{
    if (bool_print == 0) {
        printf("%s\n", path);
    }
    // if (bool_print == 0) {
    //     FILE *file;
    //     file = fopen(path, "r");
    //     char *line = NULL;
    //     size_t len = 0;
    //     ssize_t read;
    //     printf("FILENAME: %s\n\n", path);
    //     while ((read = getline(&line, &len, file)) != -1)
    //     {
    //         printf("%s", line);
    //     }
    //     fclose(file);
    //     return 0;
    // }
    // return -1;
    return 0;
}

int
check_logfile()
{
    FILE *file;
    file = fopen(DEFAULT_FILE, "w+");
    if (file != NULL) {
      fclose(file);
      return 1;
    }
    return 0;
}
int
is_or(int array_size, char **arguments)
{
    for (int i = 0; i < array_size; i++) {
        if(strcmp(arguments[i],"-o") == 0)
            return 0;
    }
    return -1;
}
char**
copy_array(char** array, size_t size)
{
    char **new_array = malloc((size+1)*sizeof(*new_array));
    for(int i = 0; i < size; i++)
    {
        size_t length = strlen(array[i]) + 1;
        new_array[i] = malloc(length);
        memcpy(new_array[i], array[i], length);
    }
    return new_array;
}
int
search_or(char **keywords, char path_to_file[], int size)
{
    char **local = copy_array(keywords, size);
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    file = fopen(path_to_file, "r");
    while ((read = getline(&line, &len, file)) != -1)
    {
        for (int i = 0; i < size; i++) {
            if(strcmp(local[i], "") == 0)
            {
                if (check_argument(line, local[i]) == 0)
                {
                    fclose(file);
                    free(local);
                    return 0;
                }
            }
        }
    }
    fclose(file);
    free(local);
    return -1;
}
int
search_and(char **keywords, char path_to_file[], int size)
{
    char **local = copy_array(keywords, size);
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    file = fopen(path_to_file, "r");
    while ((read = getline(&line, &len, file)) != -1)
    {
        for (int i = 0; i < size; i++) {
            if(strcmp(local[i], "") == 0)
            {
                if (check_argument(line, local[i]) == 0)
                {
                    free(local[i]);
                }
            }
        }
    }
    fclose(file);
    for(int j = 0; j < size; j++)
    {
        if (strcmp(local[j], "") != 0) {
            // free(local);
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]){
    check(argc > 1, "There is nothing to find.");
    char **key_words = malloc((argc)*sizeof(*key_words));
    for(int i = 1; i < argc; i++)
    {
        size_t length = strlen(argv[i]) + 1;
        key_words[i-1] = malloc(length);
        memcpy(key_words[i-1], argv[i], length);
    }
    free(key_words[0]);
    for (int j = 0; j < argc - 1; j++) //new array is smaller, so must be argc-1
    {
        if(strcmp(key_words[j], "") != 0)
        {
            printf("%d: %s\n", j+1, key_words[j]);
        }
    }
    // printf("%d\n", check_logfile());
    // check(check_logfile(), "Please create logfile in home directory.")
    // printf("%d\n", is_or(argc, argv));
    list_directory("/home/lukas/", key_words, argc - 1);
    return 0;
    error:
    return -1;
}
