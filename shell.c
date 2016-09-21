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
               make_rg(onecmd,arr);// printf("arr[0]=%s|||\n",arr[0] );// printf("argment=%s|||\n",argment );
               // cheaking  it
               // int h = strlen(arr);
               // for (i=0;i<5;i++)
               // {
               //      printf("cheaking all arguments |||%s|||\n",arr[i]);
               // }
               //chk
               strcpy(Rtv_WD,"");
               if(strcmp(arr[0],"cd")==0){
                    //printf("cd****************\n");
                    char d[10000];
                    strcpy(d,arr[1]);
                    if(strcmp(d,"~")==0)
                    {
                         strcpy(Rtv_WD,"");
                         //printf("~~~~~\n");
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
               else if(strcmp(arr[0],"pwd")==0){
                    //printf("pwd****************\n");
                    printf("%s\n",PWD);

               }
               else if(strcmp(arr[0],"echo")==0){
                    //printf("echo****************\n");
                    char prt_word[1000]={'\0'};
                    char* cwd;
                    //printf("one arr[0]==%s\n",que[don_comm]);
                    cwd=strtok(que[don_comm]," ");
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
               else if(strcmp(arr[0],"exit")==0){
                    //printf("exit****************\n");
                    return 0;
               }
               else if(strcmp(arr[0],"pinfo")==0){
                    //printf("pinfo****************\n");
                    char path[1000]={'\0'};
                    strcat(path,"/proc/");
                    strcat(path,arr[1]);
                    strcat(path,"/status");
                    int ext_dir=access(path,F_OK);
                    if(ext_dir==-1)
                    {
                         printf("process does not exist\n");
                    }
                    else
                    {
                         int fo=open(path,O_RDONLY);
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
               else
               {
                    // printf("U re in else\n");
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
                         // printf("U re inn child****************\n");
                         // char *arr[3];
                         //arr[0]=arr[0];
                         // if(strlen(argment)>0)
                         // {
                         //      arr[1]=argment;
                         // }
                         // else
                         // {
                         //      arr[1]=NULL;
                         // }
                         // arr[2]=NULL;
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
