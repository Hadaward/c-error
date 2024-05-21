#ifndef C_ERROR_H
#define C_ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_ERROR 30

typedef struct Error {
    const char *func;
    char *message;
    char *file;
    int line;
} Error;

static Error *__last_error__[MAX_STACK_ERROR];
static int __last_error_count__ = 0;

void __unsafe_throw__(const char *func, char *message, char *file, int line);
void __safe_throw__(const char *func, char *message, char *file, int line);
Error *get_last_error();

#define try for(void (*__unsafe_throw__)(const char *func, char *message, char *file, int line) =__safe_throw__;__unsafe_throw__!=NULL;__unsafe_throw__=NULL)
#define catch(name) for (Error *name = get_last_error(); name != NULL; name = NULL)
#define throw(message) ({\
    const char *func = __func__;\
    char *file = __FILE__;\
    int line = __LINE__;\
    __unsafe_throw__(func,message,file,line);\
})
#endif