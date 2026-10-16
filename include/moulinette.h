#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int error;
    char **cmd;
    char *file;
} cmd;