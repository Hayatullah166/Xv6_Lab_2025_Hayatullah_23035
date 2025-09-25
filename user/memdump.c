#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
memdump(char *fmt, char *data)
{
  while (*fmt) {
    switch (*fmt) {
      case 'i': {
        int *ip = (int *)data;
        printf("%d\n", *ip);
        data += sizeof(int);
        break;
      }
      case 'p': {
        long *lp = (long *)data;
        printf("%lx\n", *lp);   
        data += sizeof(long);
        break;
      }
      case 'h': {
        short *sp = (short *)data;
        printf("%d\n", *sp);
        data += sizeof(short);
        break;
      }
      case 'c': {
        char *cp = (char *)data;
        printf("%c\n", *cp);
        data += sizeof(char);
        break;
      }
      case 's': {
        char **strp = (char **)data;
        printf("%s\n", *strp);
        data += sizeof(char *);
        break;
      }
      case 'S': {
        char *str = (char *)data;
        printf("%s\n", str);
        data += strlen(str) + 1;
        break;
      }
      default:
        printf("Unknown format: %c\n", *fmt);
        break;
    }
    fmt++;
  }
}

int
main(int argc, char *argv[])
{
  if (argc == 1) {
  
    printf("Example 1:\n");
    int arr[2] = {61810, 2025};
    memdump("ii", (char *)arr);

  
    printf("Example 2:\n");
    char *s = "a string";
    memdump("s", (char *)&s);


    printf("Example 3:\n");
    char str2[] = "another";
    memdump("S", str2);


    printf("Example 4:\n");
    struct {
      char c;
      int x;
      int y;
      char z;
      char *p;
    } st = {'B', 1819438967, 100, 'z', "xyzzy"};
    memdump("ciicS", (char *)&st);

    printf("Example 5:\n");
    char str3[] = "hello";
    memdump("S", str3);
  } else {

    char buf[512];
    int n = read(0, buf, sizeof(buf));
    if (n > 0) {
      memdump(argv[1], buf);
    }
  }
  exit(0);
}
