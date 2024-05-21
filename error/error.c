#include "error.h"

void __unsafe_throw__(const char *func, char *message, char *file, int line) {
    printf("Uncaught Error: %s\n\tat %s (%s:%d)", message, func, file, line);
    exit(EXIT_FAILURE);
}

void __safe_throw__(const char *func, char *message, char *file, int line) {
    Error *err = (Error *) malloc(sizeof(Error));

    err->message = message;
    err->func = func;
    err->file = file;
    err->line = line;

    __last_error__[__last_error_count__] = err;
    __last_error_count__ = (__last_error_count__ + 1) % MAX_STACK_ERROR;
}

Error *get_last_error() {
    if (__last_error_count__ == 0 && __last_error__[0] != NULL) {
        __last_error_count__ = MAX_STACK_ERROR - 1;
    }
    int index = --__last_error_count__;
    if (__last_error_count__ < 0) {
        __last_error_count__ = 0;
    }
    Error *error = __last_error__[index];
    __last_error__[index] = NULL;
    return error;
}