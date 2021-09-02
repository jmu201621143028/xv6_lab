#include "kernel/types.h"
#include "user/user.h"

int main(){
    int p_child[2];
    int p_parent[2];
    pipe(p_child);
    pipe(p_parent);
    char buf[20];
    memset(buf,0,20);
    if (fork() == 0)
    {
        // child
        write(p_child[1], "ping", 4);
        read(p_parent[0],buf,20);
        printf("%d: received %s\n",getpid(), buf);
    }
    else{
        // parent
        read(p_child[0],buf,20);
        printf("%d: received %s\n",getpid(), buf);
        write(p_parent[1], "pong", 4);
    }
    exit(0);    
}