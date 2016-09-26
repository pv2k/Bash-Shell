#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include "extract.h"
#include "cmd.h"
#include "abo_chil.h"
#include "comon2.h"
#include "comon1.h"
#include "pipe.h"
sigjmp_buf env;
char org_dir[1000];
int main()
{ 										//need to module it
	char dir[1000],*cwd,sys_name[30],*usr_name;				//use errors
	int flg=0,bg;
	cwd=getcwd(dir,sizeof(dir));        // use exits
	strcpy(org_dir,dir);
	usr_name = getenv("USER");
	gethostname(sys_name,30);
	// printf("<Zoro@UBUNTU:~>");
	while(1)
	{
		char str[100],*token,*tok,*name[100],concat[100],*var[100],*var1[100];
		int i=0,j,res;
		bg=0;
		if(strcmp(dir,org_dir)==0)
			printf("<%s@%s:~>",usr_name,sys_name);
		else if (flg==1)
			printf("<%s@%s:~%s>",usr_name,sys_name,concat);
		else
			printf("<%s@%s:%s>",usr_name,sys_name,dir);
		fgets(str,100,stdin);
		str[strlen(str)-1]='\0';
		// printf("a\n");
		tok = strtok(str,";");
		while(tok!=NULL)
		{
			var[i]=tok;
            var1[i] = tok;
			tok = strtok(NULL,";");
			i++;
		}
		var[i]=NULL;var1[i]=NULL;
        printf("%s\n",var[0]);
		for(int x=0;x<i;x++)
		{
			j=0;
			token = strtok(var1[x]," ");
			while(token!=NULL)
			{
				name[j] = token;
				token = strtok(NULL," ");
				j++;
			}
			name[j] = NULL;
			int ox = strlen(name[j-1]);
			cwd=getcwd(dir,sizeof(dir));
            printf("%s\n",var[0]);
			if(name[j-1][0]=='&')
			{
				bg = 1;
				name[j-1] = NULL;
				res=cmd(name,var,bg,j,i,dir,x);
				struct sigaction sa;
				sigfillset(&sa.sa_mask);
				sa.sa_handler=(void *)abo_chil;
				sa.sa_flags=0;
				sigaction(SIGCHLD,&sa,NULL);
				sigsetjmp(env,1);
			}
			else if(name[j-1][ox-1]=='&')
			{
				bg = 1;
				name[j-1][ox-1]='\0';
				res=cmd(name,var,bg,j,i,dir,x);
			}
			else
				res=cmd(name,var,bg,j,i,dir,x);
			if(res==0)
				return 0;
			cwd=getcwd(dir,sizeof(dir));
			int l2=strlen(dir);
			int l1=strlen(org_dir);
			if(l2>l1){
				char *to = (char*) malloc(l1);
				char *cut=(char*) malloc(l2);
				strncpy(to,dir+0,l1);
				strncpy(cut,dir+l1,l2);
				// printf("%s\n",cut);
				if(strcmp(org_dir,to)==0)
				{
					flg=1;
					strcpy(concat,cut);
				}
				else
					flg=0;
			}
			else
				flg=0;
		}
	}
	return 0;
}
