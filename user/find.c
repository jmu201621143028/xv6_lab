#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char * fmtname(char *path){
    char *p = path + strlen(path);
    while (path < p && *p != '/')
    {
        p--;
    }
    return ++p;
    
}
void find(char *path, char *filename)
{
    char buf[512];
    char *p;
    int fd;
    struct dirent de;
    struct stat st;
    
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return ;
    }
    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }
    switch (st.type)
    {
    case T_FILE:
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf("ls: path too long\n");
            break;
        }
        if (strcmp(fmtname(path), filename) == 0)
        {
            printf("%s\n",path);
        }
        else
        {
            close(fd);   //这个错误调试了两个多小时.
        }
        break;
    case T_DIR:
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)))
        {
            if (de.inum == 0)
            {
                continue;
            }
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            {
                continue;
            }
            
            strcpy(p, de.name);
            // DIRSIZ = 14.(这里当时是想写数组的长度的512,但是写错了),导致DIRSIZ - strlen(buf)的结果为负值。造成内存崩溃。
            // memset(buf + strlen(buf), 0, DIRSIZ - strlen(buf)); 
            find(buf, filename);
        }
        break;
    default:
        break;
    }
}

int main(int argc, char * argv[])
{
    if (argc == 3)
    {
        find(argv[1], argv[2]);
    }
    else
    {
        printf("error\n");
    }
    
    exit(0);
}