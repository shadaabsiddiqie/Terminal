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
// #include "signal.h"
// #include "shell_fun.h"
void make_rg(char input[] , char * arr[])
{
     char comd[1000];
     int len = strlen(input);
     if(input[len-1]=='&')
     {
          input[len-1]='\0';
     }
     char *cmd =strtok(input," ");
     strcat(comd,cmd);
     arr[0]=cmd;
     // #include <errno.h>
     cmd = strtok(NULL," ");
     int tmp=0;
     // char and[2]={'\0'};
     char arg[1000]={'\0'};
     // and[0]='&;';
     int i = 1;
     while(cmd!=NULL)
     {

          // char wod[10000];
          //strcpy(arg,cmd);
          // arr[i]=arg;
          arr[i]=cmd;
          i++;
          //strcpy(wod,cmd);
          // if(wod[0]=='-')
          // {
          //      tmp=1;
          // }
          cmd=strtok(NULL," ");
     }
     // char ts[10000]={'\0'};
     // if(tmp==1)
     // {
     //      char *cm = strtok(arg,"-");
     //      char arg_fre[10000]={'\0'};
     //      while(cm!=NULL)
     //      {
     //           ///if(strcmp(cmd,"&")!=0)
     //           ///{
     //                strcat(arg_fre,cm);
     //           //}
     //           cm = strtok(NULL,"-");
     //      }
     //      strcpy(arg,arg_fre);
     //      sprintf(ts,"-%s",arg);
     //      strcpy(arg,ts);
     // }

}
int det_and(char input[])
{
     int len = strlen(input);
     if(input[len-1]=='&')
     {
          // input[len-1]='\0';
          return 1;
     }
     else
     {
          return 0;
     }
}
// int main()
// {
//      char *arr[100];
//      int i;
//      for (i=0;i<100;i++)
//      {
//           arr[i]=NULL;
//      }
//      char input[10000]={'\0'};
//      scanf("%10000[^\n]",input);
//      printf("%s\n",input );
//      make_rg(input,arr);
//      for (i=0;i<10;i++)
//      {
//           // printf("%s\n",arr[i]);
//      }
//
// }
