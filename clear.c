#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void help(){
    printf(1,"clear : Membersihkan layar terminal\n");
}

int main(int argc,char *argv[])
{   printf(1,"\033[2J\033[1;1H\n");
    exit();
}
