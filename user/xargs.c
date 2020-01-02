#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: xargs command [arguments]\n");
        exit();
    }
    char *new_argv[MAXARG];
    for (int i = 0; i < argc - 1; i++)
    {
        new_argv[i] = argv[i+1];
    }
    
    char s[512];
    while (gets(s, sizeof(s)) && *s)
    {
        char *p = s;
        int j;
        for (j = argc - 1; j < MAXARG; j++)
        {
            while (*p == ' ' || *p == '\t' || *p == '\n')
            {
                p++;
            }
            if (!*p)
            {
                break;
            }
            new_argv[j] = p;
            while (*p != ' ' && *p != '\t' && *p != '\n')
            {
                p++;
            }
            if (*p)
            {
                *p = '\0';
                p++;
            }
        }
        while (j < MAXARG)
        {
            new_argv[j] = 0;
            j++;
        }       

        int pid = fork();
        if (pid == 0)
        {
            exec(argv[1], new_argv);
        }
        else if (pid < 0)
        {
            fprintf(2, "fork error\n");
        }
        else
        {
            wait();
        }
    }
    
    
    exit();
}
