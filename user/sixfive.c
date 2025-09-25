#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char sep[] = " -\r\t\n./,";   

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(2, "Usage: sixfive <file>\n");
    exit(1);
  }

  int fd = open(argv[1], 0);   
  if (fd < 0) {
    fprintf(2, "sixfive: cannot open %s\n", argv[1]);
    exit(1);
  }

  char buf[1];
  char numbuf[32];   
  int nidx = 0;

  while (read(fd, buf, 1) == 1) {
    char c = buf[0];

    if (strchr(sep, c) != 0) {   
      if (nidx > 0) {
        numbuf[nidx] = '\0';
        int num = atoi(numbuf);
        if (num % 5 == 0 || num % 6 == 0) {
          printf("%d\n", num);
        }
        nidx = 0;  
      }
    } else {
      if (c >= '0' && c <= '9') {
        if (nidx < sizeof(numbuf) - 1) {
          numbuf[nidx++] = c;
        }
      }
    }
  }

  
  if (nidx > 0) {
    numbuf[nidx] = '\0';
    int num = atoi(numbuf);
    if (num % 5 == 0 || num % 6 == 0) {
      printf("%d\n" , num);
    }
  }

  close(fd);
  exit(0);
}
