#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int n = uptime();
    printf("uptime: %d ticks\n", n);
    exit();
}