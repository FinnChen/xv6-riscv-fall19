#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc <= 1) {
        exit();
    }
    int n = atoi(argv[1]);
    sleep(n);
    exit();
}