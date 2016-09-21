#include "unistd.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "pwd.h"
#include <errno.h>
#include "signal.h"
int main()
{
     pid_t stat_fam=fork();
     char *arr[3];
     int status;
     if (stat_fam>0){

               while(wait(&status)!=stat_fam){}
               //printf("beforKILLKILL=%d\n",stat_fam);
               kill(stat_fam,SIGKILL);
               //printf("afterKILLKILL=%d\n",stat_fam);

     }
     else if(stat_fam==0)
     {
          char a[10]={'\0'};
          char b[10]={'\0'};
          char c[10]={'\0'};
          // a = "ls";
          a[0]='l';
          a[1]='s';
          // b = "-l";
          b[0]='-';
          b[1]='l';

          c[0]='-';
          c[1]='a';
          // c[1]='l';
          // b[4]='a';
          //execl(a,a,b,NULL);
          char*arr[9];
          int i;
          for(i=0;i<9;i++)
          {
               arr[i]=NULL;
          }
          arr[0]= a;
          arr[1]= b;
          arr[2]= c;
          arr[2]= NULL;
          arr[3]= NULL;
          execvp(arr[0],arr);
          // execl("ls", "ls", "-l", (char*) NULL);

     }
     return 0;
}
