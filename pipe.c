#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include "pipe.h"
int pip(int no_pip,char *name[],char *var[],int lmt,int mxm,int idx)
{
    int fd[2*no_pip],i,j=0;
    char *tmp[100],*token;
    // printf("a\n");
    // printf("%d\n",mxm);
    // printf("%s\n",var[idx]);
    token = strtok(var[idx],"|");
    // printf("%s\n",token);
    while(token!=NULL)
    {
        tmp[j] = token;
        token = strtok(NULL,"|");
        j++;
    }
    tmp[j]=NULL;
    // for(i=0;i<mxm;i++)
    // {
    //     if(name[i][0] != '|')
    //     {
    //         // strcpy(tmp[j],name[i]);
    //         j++;
    //     }
    //     else{
    //         name[i]='\0';
    //         i++;
    //         break;
    //     }
    // }
    // printf("%s\n",tmp[0]);
    // execvp(tmp[0][0],tmp[0]);
    return 0;
}
