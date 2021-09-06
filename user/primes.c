#include "kernel/types.h"
#include "user/user.h"


void redirect(int k, int pd[])
{
    close(k);
    dup(pd[k]);
    close(pd[0]);
    close(pd[1]);
}

void cull(int p)
{
    int n;
    while (read(0, &n, sizeof(n)))
    {
        if (n % p != 0)
        {
            write(1, &n, sizeof(n));
        }
        
    }
    
}

void right()
{
    int pd[2], p;

    if (read(0, &p, sizeof(p)))
    {
        /* code */
        printf("prime %d\n", p);
        pipe(pd);
        if (fork())
        {
            //parent
            //return child pid
            redirect(0, pd);
            right();
        }
        else
        {
            redirect(1, pd);
            cull(p);   
        }
    }
    
}
int main(){
    int pd[2];
    pipe(pd);

    if (fork() == 0)
    {
        //child
        redirect(1, pd);
        for(int i = 2;i < 1000; ++i){
            write(1, &i, sizeof(i));
        }
    }
    else{
        //parent
        redirect(0, pd);
        right();
    }
    

    exit(0);
}