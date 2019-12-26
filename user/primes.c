#include "kernel/types.h"
#include "user/user.h"

// pseudocode:
// p = get a number from left neighbor
// print p
// loop:
//     n = get a number from left neighbor
//     if (p does not divide n)
//         send n to right neighbor

void
primeproc(int fd)
{
    int sz, i, id, p, pfd[2];

top:
    sz = sizeof(int);

    // read a number from left neighbor(the parent process)
    if (read(fd, &p, sz) != sz) {
        return;
    }

    // at the process first run, print the prime number
    printf("prime %d\n", p);

    pipe(pfd);
    id = fork();
    if (id == 0)
    {
        // When fork a child process, it will inherit the parent process's
        // file descriptors. The fd and pfd[1] will not be used, so close 
        // them first.
        close(fd);
        close(pfd[1]);

        // will read from left neighbor(parent process)
        fd = pfd[0];
        goto top;
    }

    close(pfd[0]);

    while (1)
    {
        if (read(fd, &i, sz) != sz) {
            break;
        }
        if (i % p)
        {
            // send i to right neighbor(the child process forked above)
            write(pfd[1], &i, 4);
        }
    }
}

int 
main(int argc, char const *argv[])
{
    int fd[2];
    pipe(fd);

    int pid = fork();
    if (pid == 0)
    {
        close(fd[1]);
        primeproc(fd[0]);
    } 

    close(fd[0]);

    for (int i = 2; i < 35; i++)
    {
        write(fd[1], &i, sizeof(int));
    }
    
    exit();
}
