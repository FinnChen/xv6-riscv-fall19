#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char const *argv[])
{
    int pid;
    int parent_fd[2];
    int child_fd[2];

    pipe(parent_fd);
    pipe(child_fd);

    pid = fork();
    if (pid == 0)
    {
        char child_read_buf[4];
        // wait until parent_fd[0] available
        read(parent_fd[0], child_read_buf, 4);
        printf("%d: received %s\n", getpid(), child_read_buf);
        write(child_fd[1], "pong", 4);
    } else {
        write(parent_fd[1], "ping", 4);
        char parent_read_buf[4];
        // wait until child_fd[0] available
        read(child_fd[0], parent_read_buf, 4);
        printf("%d: received %s\n", getpid(), parent_read_buf);
    }

    exit();
}
