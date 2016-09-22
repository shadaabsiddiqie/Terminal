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
#include "shell_fun.h"
int main()
{
     char HomD[1000]={'\0'};
     getcwd(HomD,1000);
     char Rtv_WD[1000]={'\0'};
     char PWD[1000]={'\0'};
     int exit_stat=0;
     while(1)
     {
          //tern_name(Rtv_WD,PWD,HomD);
          strcpy(Rtv_WD,"");
          uid_t uid = geteuid();
          struct passwd *pw = getpwuid(uid);
          char com_name[1000];
          int p = gethostname(com_name,1000);
          getcwd(PWD,1000);
          int temp=0;
          int i;
          for(i=0;i<strlen(HomD);i++)
          {
               if(HomD[i]!=PWD[i])
               {
                    temp=1;
                    break;
               }
          }
          if (temp==0)
          {
               strcpy(Rtv_WD,"");
               Rtv_WD[2]='\0';
               Rtv_WD[0]=':';
               Rtv_WD[1]='~';
               for(i=0;i<strlen(PWD)-strlen(HomD);i++)
               {
                    Rtv_WD[i+2]=PWD[strlen(HomD)+i];
               }
               //printf("UUUUUUUUUUUU\n");
          }
          else
          {
               strcpy(Rtv_WD,"");
               strcat(Rtv_WD,":");
               strcat(Rtv_WD,PWD);
          }
          printf("<%s@%s%s>",pw->pw_name,com_name,Rtv_WD/*,PWD,HomD*/);
          //printf("rel=%s::pwd==%s::Hom==%s",Rtv_WD,PWD,HomD);
          char input[10000]={'\0'};
          scanf("%10000[^\n]",input);
          char nextline;
          scanf("%c",&nextline);
          char que[100][1000];
          char * pch;
          pch = strtok (input,";");
          int no_comm=0;
          while(pch!=NULL)
          {
               strcpy(que[no_comm],pch);
               pch = strtok(NULL,";");
               no_comm++;
               // printf("combain command -- %s\n " ,que[no_comm-1]);
          }
          int don_comm=0;
          while(don_comm<no_comm)
          {
               char *arr[10];

               for (i=0;i<10;i++)
               {
                    arr[i]=NULL;
               }

               char onecmd[1000]={'\0'};
               strcpy(onecmd,que[don_comm]);
               int and_stat = det_and(onecmd);
               int lent = strlen(onecmd);
               if(and_stat==1)
               {
                    onecmd[lent-1]='\0';
               }
               make_rg(onecmd,arr);

               strcpy(Rtv_WD,"");
               if(strcmp(arr[0],"cd")==0){
                    cmd_cd(arr[1],HomD);
               }
               else if(strcmp(arr[0],"pwd")==0){
                    //printf("pwd****************\n");
                    printf("%s\n",PWD);
               }
               else if(strcmp(arr[0],"echo")==0){
                    cmd_echo(que[don_comm]);
               }
               else if(strcmp(arr[0],"exit")==0){
                    //printf("exit****************\n");
                    return 0;
               }
               else if(strcmp(arr[0],"pinfo")==0){
                    cmd_pinfo(arr[1]);
               }
               else
               {
                    pid_t stat_fam=fork();
                    //char *arr[3];
                    int status;
                    if (stat_fam>0){
                         if(and_stat==0)
                         {
                              while(wait(&status)!=stat_fam){}
                              //printf("beforKILLKILL=%d\n",stat_fam);
                              kill(stat_fam,SIGKILL);
                              //printf("afterKILLKILL=%d\n",stat_fam);
                         }
                         else
                         {
                              printf("process with ID:-%d- Began in Background\n",(int)stat_fam);
                              waitpid(stat_fam,&status,WNOHANG);
                         }
                    }
                    else if(stat_fam==0)
                    {
                         if(execvp(arr[0],arr)<0)
                         {
                              printf("%s :COMMAND NOT FOUND\n",arr[0]);
                         }
                    }
               }
               strcpy(Rtv_WD,"");

               don_comm++;
          }
     }
     return 0;
}
