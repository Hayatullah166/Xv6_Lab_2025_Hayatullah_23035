#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int
match(char *path, char *name)
{
  char *p;
  for(p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  return strcmp(p, name) == 0;
}

void runexec(char *cmd[], char *file)
{
  char *argv[MAXARG];
  int i = 0;

  for(; cmd[i]; i++)
	argv[i] = cmd[i];
 argv[i++] = file;
 argv[i] = 0;
 
  if(fork() == 0){
    exec(argv[0], argv);
    fprintf(2, "exec %s failed\n", argv[0]);
    exit(1);
  } 
    wait(0);
  }


void
findexec(char *path, char *name, int execmode, char *cmd[])
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "findexec: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "findexec: cannot stat %s\n", path);
    close(fd);
    return;
  }

  if(st.type == T_FILE){
    if(match(path, name)){
      if(execmode)
        runexec(cmd, path);
      else
        printf("%s\n", path);
    }
  } else if(st.type == T_DIR){
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
      printf("findexec: path too long\n");
      close(fd);
      return;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      findexec(buf, name, execmode, cmd);
    }
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  if(argc < 3){
    fprintf(2, "usage: findexec <path> <filename> [-exec cmd ...]\n");
    exit(1);
  }

  int execmode = 0;
  char *cmd[MAXARG];
  int cmdstart = 0;

  for(int i = 3; i < argc; i++){
    if(strcmp(argv[i], "-exec") == 0){
      execmode = 1;
      cmdstart = i + 1;
      break;
    }
  }

  if(execmode){
    int j = 0;
    for(int i = cmdstart; i < argc && j < MAXARG-1; i++){
      cmd[j++] = argv[i];
    }
    cmd[j] = 0;
    findexec(argv[1], argv[2], 1, cmd);
  } else {
    findexec(argv[1], argv[2], 0, 0);
  }

  exit(0);
}
