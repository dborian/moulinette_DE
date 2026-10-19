#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    int error;
    char **cmd;
    char *file;
} cmd;

typedef struct {
    char *ex00;
} shell00;