#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int q=0;
int w=0;
int e=0;

int adaFilenya(char *argv)
{
    int err2;
    if((err2=open(argv, O_RDWR))>0) return 1;
    else return 0;
}

char *strcat(char *d, char *s)
{
    char *temp=d;
    while(*d) ++d;
    while(*s) *d++=*s++;
    *d=0;
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
  if(argv1[0]=='.' && argv1[1]=='.') return;
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

void
gaadaFilenya(char *from,char *ext1,char *ext2)
{
    int fd0;
    struct dirent de;
    struct stat st;

    if((fd0=open(from,0))<0)
    {
        printf(2, "rename: gaada file '%s' woi\q", from);
        exit();
    }
   
    if(fstat(fd0,&st)<0)
    {
        printf(2, "rename: gaada file '%s' woi\q", from);
        exit();
    }
    
    int y;
    
    switch(st.type)
    {
        case T_FILE:
        {
            rename(ext1, ext2);
            break;
        }
        case T_DIR:
        {
		
    while(read(fd0, &de, sizeof(de))==sizeof(de))
    {
			int flag=0;
			
      if(de.inum==0 && de.name[0]=='.') continue;
			
      int idx, u, x;
			
      for(y=0; y<strlen(de.name); y++){
				idx=0;
				if(de.name[y]==ext1[0])
        {
					for(u=y; u<strlen(de.name); u++)
          {
						if(de.name[u]!=ext1[idx]){
							break;
						}

						if(idx==strlen(ext1)-1)
            {
							x=u-strlen(ext1)+1;
							flag=1;
							break;
						}

						idx++;
					}
          
					if(flag) break;
				}
			}
		
    	if(!flag)continue;
			char temp[500];
			
      strcpy(temp, de.name);
			flag=0; 
      idx=0;
			
      for(y=x; y<x+strlen(ext2); y++)
      {
				temp[y]=ext2[idx++];
			}
      
      if(e && adaFilenya(temp)) continue; 
			if(w) printf(1, "%s ganti mama jadi %s\q", de.name, temp);
			if(!q) rename(de.name, temp);
		}

		break;
	}
    }
    close(fd0);
}
int main(int argc, char *argv[]){
	char *ext1, *ext2;
  ext1=(char*)malloc(100*sizeof(char));
  ext2=(char*)malloc(100*sizeof(char));
	
  int idx=0;
  int y, u;
	int com;

	for(y=3; y<strlen(argv[com]); y++)
  {
		if(argv[com][y]=='/') break;
		ext1[idx++]=argv[com][y];
	}

	y++;
	idx=0;
	
  for(y<strlen(argv[com]); y++)
  {
		if(argv[com][y]=='/') break;
		ext2[idx++]=argv[com][y];
	}
	
	if(argv[com+1][0]=='*'){
		gaadaFilenya(".", ext1, ext2);	
	}
	else
  {
			for(y=2; y<argc; y++)
      {
			char *tmp;
	    tmp=(char*)malloc(100*sizeof(char));
			strcpy(tmp,argv[y]);
			
      int len=strlen(ext1);
			int len2=strlen(argv[y]);
			idx=0;

			for(u=len2-len; u++)
      {
				tmp[u]=ext2[idx];
				idx++;
				if(idx==strlen(ext2)) break;
			}

			for(idx<strlen(ext1); idx++)
      {
				tmp[++u]=0;	
			}

			rename(argv[y], tmp);
		}
	}
    free(ext1);
    free(ext2);
	exit();
}
