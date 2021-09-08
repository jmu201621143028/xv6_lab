#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"


void run_cmd(char **p, int k, int i,char args[MAXARG][MAXARG])
{
    int t = 0;
    for (t = 0; t <= i; t++)
    {
        p[k + t] = args[t];
    }
    p[k+t] = 0;
            
    if (fork() == 0) 
    {
        // child
        exec(p[0],p);
    }
    else
    {
        //parent
        wait(0);
    }
}

int main(int argc, char *argv[])
{
    /*
    argv[0] = "echo";
    argv[1] = "test";
    argv[2] = 0;
    exec(argv[0], argv);
    exit(0);
    */
    char args[MAXARG][MAXARG];
    memset(args, 0, MAXARG * MAXARG);
    char *p[MAXARG];
    int k;
    for(k = 0; k < argc-1; ++k)
    {
        p[k] = argv[k+1];
    }
    // 先copy xargs后边的命令和参数
    // 从管道内读取参数 
    int j = 0, i = 0;
    
    while (read(0, &args[i][j], sizeof(char)) > 0)
    {
        if(args[i][j] == ' ')
        {
            args[i][j] = 0;
            i++;
            j = 0;
        }
        else if (args[i][j] == '\n')
        {
            args[i][j] = 0;
            run_cmd(p, k, i, args);
            i = 0;j=0;
        }
        else
        {
            j++;
        }
    }
    if (i !=0 || j != 0)
    {
        /* code */
        run_cmd(p, k, i, args);
    }
    
    exit(0);
}