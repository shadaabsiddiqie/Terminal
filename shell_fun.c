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
          arr[i]=cmd;
          i++;
          cmd=strtok(NULL," ");
     }
}
void cmd_cd(char argument[],char HomD[])
{
     char d[10000];
     strcpy(d,argument);
     if(strcmp(d,"~")==0)
     {
          chdir(HomD);
     }
     else
     {
          chdir(d);
          if(errno == ENOENT)
          {
               fprintf(stderr,"%s:FILE DOES NOT EXIT\n",d);
          }
          else if(errno== ENOTDIR)
          {
               fprintf(stderr,"A component of %s is not a directory.\n",d);
          }
     }
}
void cmd_echo(char argument[])
{
     char prt_word[1000]={'\0'};
     char* cwd;
     //printf("one arr[0]==%s\n",que[don_comm]);
     cwd=strtok(argument," ");
     strcpy(prt_word,cwd);
     cwd=strtok (NULL," ");
     strcpy(prt_word,"");
     while(cwd!=NULL)
     {
          strcat(prt_word,cwd);
          strcat(prt_word," ");
          cwd=strtok (NULL," ");
     }
     //printf("all words:::%s\n",prt_word);
     int tmp1=0;
     int tmp2=0,j;
     char h='a';
     char h1[2]={'\0'};
     char sentence[10000]={'\0'};
     for(j=0;j<strlen(prt_word);j++)
     {
          h=prt_word[j];
          if(h=='\'')
          {
               tmp1++;
          }
          else if(h=='"')
          {
               tmp2++;
          }
          else
          {
               h1[0]=h;
               strcat(sentence,h1);
          }
     }
     //printf("tmp1=%d;tmp2=%d",tmp1,tmp2);
     if(tmp1%2==0 && tmp2%2==0)
     {
          printf("%s\n",sentence);
     }
     else
     {
          while(tmp1%2!=0 || tmp2%2!=0)
          {
               char ext_word[1000]={'\0'};
               printf(">");
               scanf("%1000[^\n]",ext_word);
               //printf("EXTRA WORD + |%s\n",ext_word);
               char nl;
               scanf("%c",&nl);
               int p;
               char p1='a';
               char p11[2]={'\0'};
               strcat(sentence,"\n");
               for(p=0;p<strlen(ext_word);p++)
               {
                    p1=ext_word[p];
                    if(p1=='\'')
                    {
                         tmp1++;
                    }
                    else if(p1=='"')
                    {
                         tmp2++;
                    }
                    else
                    {
                         p11[0]=p1;
                         // strcat(sentence,"\n");
                         strcat(sentence,p11);
                    }
               }
          }
          printf("%s\n",sentence);
          //printf("ERROE:not correct text to echo\n");
     }
}
void cmd_pinfo(char argument[])
{
     char path[1000]={'\0'};
     strcat(path,"/proc/");
     strcat(path,argument);
     strcat(path,"/status");
     int ext_dir=access(path,F_OK);
     if(ext_dir==-1)
     {
          printf("process does not exist\n");
     }
     else
     {
          int fo=open(path,O_RDONLY),i;
          char id_data[100000]={'\0'};
          read(fo,id_data,100000);
          char *id_brk;
          id_brk = strtok (id_data,"\n");
          while(id_brk!=NULL)
          {
               char id_info[1000]={'\0'};
               strcpy(id_info,id_brk);
               char ch_dat[10000]={'\0'};
               for(i=0;i<strlen(id_info);i++)
               {
                    if(id_info[i]==':')
                    {
                         break;
                    }
                    else
                    {
                         char id_st[2]={'\0'};
                         id_st[0]=id_info[i];
                         strcat(ch_dat,id_st);
                    }
               }
               if(strcmp(ch_dat,"Name")==0||strcmp(ch_dat,"State")==0||strcmp(ch_dat,"Pid")==0||strcmp(ch_dat,"VmSize")==0)
               {
                    printf("%s\n",id_info);
               }
               id_brk = strtok(NULL,"\n");
          }
     }
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
