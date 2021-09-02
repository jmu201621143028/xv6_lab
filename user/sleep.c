#include "kernel/types.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
  if(argc == 2){  //argc == 1, 调试了两多小时.
      printf("nothing happens for a little while\n");
      int t = atoi(argv[1]);
      sleep(t);
      exit(0);
  }
  else{
      printf("error\n");
      exit(-1);
  }

}
