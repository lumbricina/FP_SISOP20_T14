#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int a;

  for(a = 1; a < argc; a++){
    if(unlink(argv[a]) < 0){
      printf(2, "rm: %s gagal menghapus\n", argv[a]);
      break;

    }
    
  }

  exit();
}
