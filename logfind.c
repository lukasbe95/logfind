#include <stdlib.h>
#include <stdio.h>

#include "dbg.h"

#define DEFAULT_FILE "/home/lukas/logfind"

typedef struct Parsed_Args {
    char *arguments[];
    int is_or;

} Parsed_Args;

int check_logfile() {
    FILE *file;
    file = fopen(DEFAULT_FILE, "w+");
    if (file != NULL) {
      fclose(file);
      return 1;
    }
    return 0;
}

int main(int argc, char *argv[]){
    check(argc > 1, "There is nothing to find.");
    for(int i = 0; i < argc; i++){
      printf("%s\n", argv[i]);
    }
    printf("%d\n", check_logfile());
    check(check_logfile(), "Please create logfile in home directory.")
    return 0;
    error:
    return -1;
}
