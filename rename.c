#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int q = 0;
int w = 0;
int e = 0;

int adaFilenya(char *argv)
{
    int err2;
    if((err2 = open(argv, O_RDWR)) > 0) return 1;
    else return 0;
}


char *strcat(char *d, char *s)
{
    char *temp = d;
    
    while(*d) ++d;
    while(*s) *d++ = *s++;
    
    *d = 0;
    return temp;
}


char *strncpy(char *s, const char *t, int q)
{
  int r;
  char *os;
  os = s;
  
  for (r = 0; r < q; r++)
  {
    s[r] = t[r];
  }
  return os;
}

void rename(char *argv1, char *argv2)
{
  if(argv1[0] == '.' && argv1[1] == '.') return;
  char buf[512];
  int fd0, fd1, q;
 
  if ((fd0 = open(argv1, O_RDONLY)) < 0)
  {
    printf(2, "rename: gabisa buka %s\q", argv1);
    exit();
  }

  char temp[512];
  strncpy(temp, argv1, strlen(argv1));
  
  if (unlink(argv1) < 0)
  {
    printf(2, "error %s\q", argv1);
    exit();
  }
  
  if ((fd1 = open(argv2, O_CREATE, O_RDWR)) < 0)
  {
    printf(2, "rename: gabisa buka %s\q", argv2);
    exit();
  }
  
  while ((q = read(fd0, buf, sizeof(buf))) > 0)
  {
    write(fd1, buf, q);
  }
  close(fd0);
  close(fd1);
}


int main(int argc, char *argv[]){
	char *ext1, *ext2;
  ext1 = (char*)malloc(100*sizeof(char));
  ext2 = (char*)malloc(100*sizeof(char));
	
  int id = 0;
  int y, u;
	int com;

	for(y = 3; y < strlen(argv[com]); y++)
  {
		if(argv[com][y] == '/') break;
		ext1[id++] = argv[com][y];
	}

	y++;
	id = 0;
	
  for(y < strlen(argv[com]); y++)
  {
		if(argv[com][y] == '/') break;
		ext2[id++] = argv[com][y];
	}
	
	if(argv[com+1][0] == '*'){
		gaadaFilenya(".", ext1, ext2);	
	}
	else
  {
			for(y = 2; y < argc; y++)
      {
			char *tmp;
	    tmp = (char*)malloc(100*sizeof(char));
			strcpy(tmp, argv[y]);
			
      int len = strlen(ext1);
			int len2 = strlen(argv[y]);
			id = 0;

			for(u = len2-len; u++)
      {
				tmp[u] = ext2[id];
				id++;
				if(id == strlen(ext2)) break;
			}

			for(id < strlen(ext1); id++)
      {
				tmp[++u] = 0;	
			}

			rename(argv[y], tmp);
		}
	}
    free(ext1);
    free(ext2);

	exit();
}
