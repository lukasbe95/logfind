#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#include "dbg.h"

#define DEFAULT_FILE "/home/lukas/logfind"

int print_whole_file(char path[], char filename[]);

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
            printf("%s\n", dir->d_name);
            print_whole_file(path, dir->d_name);
        }
        closedir(d);

    }
    return 0;
}
int
print_whole_file(char path[], char filename[])
{
    char whole_path[256];
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    strcpy(whole_path, path);
    strcat(whole_path,filename);
    file = fopen(whole_path, "r");
    if (file != NULL)
    {
        printf("FILENAME: %s\n\n", whole_path);
        while ((read = getline(&line, &len, file)) != -1) {
            printf("%s", line);
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
int main(int argc, char *argv[]){
    check(argc > 1, "There is nothing to find.");
    // for(int i = 0; i < argc; i++){
    //   printf("%s\n", argv[i]);
    // }
    // printf("%d\n", check_logfile());
    check(check_logfile(), "Please create logfile in home directory.")
    // printf("%d\n", is_or(argc, argv));
    list_directory("/home/lukas/");
    return 0;
    error:
    return -1;
}
