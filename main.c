#include "error/error.c"

int main()
{
    try {
        try {
            throw("Test 2");
        } catch (error) {
            printf("Got a error '%s' at %s in file %s:%d\n", error->message, error->func, error->file, error->line);
        }

        throw("Test");
    } catch (error) {
        printf("Got a error '%s' at %s in file %s:%d\n", error->message, error->func, error->file, error->line);
    }

    throw("Morre ai fi");
    printf("Ok!\n");

    return 0;
}