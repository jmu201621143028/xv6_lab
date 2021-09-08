#include "kernel/types.h"
#include "user/user.h"

int main(){
    int p[2];
    char recv_buf[5];
    pipe(p);
    if (fork() == 0)
    {
        
        // child
        read(p[0], recv_buf, 5);
        printf("%d: received %s\n", getpid(), recv_buf);
        close(p[0]);

        write(p[1], "pong", 4);
        close(p[1]);
    }
    else{
        //
        write(p[1], "ping", 4);
        close(p[1]);

        wait(0);
        read(p[0], recv_buf, 5);
        printf("%d: received %s\n", getpid(), recv_buf);
        close(p[0]);
    }
    
    exit(0);    
}