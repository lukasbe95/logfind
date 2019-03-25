#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "dbg.h"

#define DEFAULT_FILE "/home/lukas/logfind"

int search_in_file(char path[], char filename[], int only_print);

int
list_directory(char path[])
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // printf("%s\n", dir->d_name);
            search_in_file(path, dir->d_name, 0);
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
search_in_file(char path[], char filename[], int only_print)
{
    char whole_path[256];
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    strcpy(whole_path, path);
    strcat(whole_path, filename);
    file = fopen(whole_path, "r");
    if (file != NULL)
    {
        printf("FILENAME: %s\n\n", whole_path);
        while ((read = getline(&line, &len, file)) != -1)
        {
            if(check_argument(line, "dupa") == 0)
            {
                printf("%s", line);
            }
        }
    }
    fclose(file);
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
is_or(int array_size, char *arguments[])
{
    for (int i = 0; i < array_size; i++) {
        if(strcmp(arguments[i],"-o") == 0)
            return 1;
    }
    return 0;
}
char**
copy_array(char** array, size_t size)
{
    //need to be tested
    char **new_array = malloc((size+1)*sizeof(*new_array));
    for(int i = 0; i < size; i++)
    {
        size_t length = strlen(argv[i]) + 1;
        new_array[i] = malloc(length);
        memcpy(new_array[i], array[i], length);
    }
    return new_array;
}
int
search_or(char **keywords, FILE *file)
{
    //need to be implemented
    return 0;
}
int
search_and(char **keywords, FILE *file)
{
    //need to be implemented
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
    // list_directory("/home/lukas/");
    return 0;
    error:
    return -1;
}
