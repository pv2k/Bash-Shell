#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include "comon2.h"
#include "cmd.h"
#include "extract.h"
int cmd(char *name[],int bg,int lmt,char pres_dir[])
{
	pid_t pid;
	int flg,l1,i,flg_cd;
	if(name[1]!=NULL){
		l1=strlen(name[1]);
	}
	char *cg,ct[l1],dir[1000];
	if(bg==1)
		setpgid(0,0);
	pid=fork();
		if(pid==0)
		{
			if(strcmp(name[0],"cd")==0)
			{
				if(name[1]==NULL)
				{
					flg_cd=chdir(org_dir);
				}
				else
					flg_cd = chdir(name[1]);
				if(flg_cd<0){
					fprintf(stderr,"bash: cd: %s: ",name[1]);
					perror("");					
				}
				return 3;
			}
			else if(strcmp(name[0],"echo")==0)
			{
				if(name[1][0]=='$')
				{
					extract(ct,name,l1);
					// printf("%s %d %d\n",ct,strlen(ct),l1);
					// printf("a\n");
					// strncpy(cg,name[1]+1,name[1]+l1);
					// printf("%s\n",cg);
					printf("%s\n",getenv(ct));
				}
				else if(name[1][0]=='"' || name[1][0]=='\'')
				{
					extract(ct,name,l1-1);
					printf("%s\n",ct);
				}
				else
					printf("%s\n",name[1]);
			}
			else if(strcmp(name[0],"pwd")==0){
				cg=getcwd(dir,sizeof(dir));
				printf("%s\n",dir);
			}
			else if(strcmp(name[0],"exit")==0){
				return 0;
			}
			else if(strcmp("pinfo",name[0])==0)
			{
				FILE *fp;
				flg=0;
				char buf1[1256],buf2[1256];
				int pid;
				char var[1256],state;
				long unsigned int size;
				if(lmt==1)
				{
					sprintf(buf1,"/proc/%d/stat",getpid());                                 //open the stat and exe files
					sprintf(buf2,"/proc/%d/exe",getpid());
				}
				else
				{
					sprintf(buf1,"/proc/%s/stat",(name[1]));
					sprintf(buf2,"/proc/%s/exe",(name[1]));
				}
				if((fp=fopen(buf1,"r"))!=NULL)
				{
					/*scan the stat file*/
					fscanf(fp,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&pid,&state,&size);  
					fclose(fp);
					printf("pid -- %d\nProcess Status -- %c\nmemory -- %lu\n",pid,state,size);
					readlink(buf2,var,1256);
					if(strstr(var,pres_dir))
					{
						char fi[1000]="~";
						strcat(fi,var+strlen(pres_dir));
						printf("Executable Path -- %s\n",fi);                           //print print the stuff
					}
					else
						printf("Executable Path -- %s\n",var);
				}
				else
					fprintf(stderr,"No such process\n");
			}
			else
				flg=execvp(name[0],name);
			if(flg<0){
				fprintf(stderr,"%s: Command not found\n",name[0]);
				// printf("%s: Command not found\n",name[0]);
			}
		}
		else if(pid > 0 && bg!=1)
		{
			wait(NULL);
		}
		else if(pid>0 && bg==1)
		{
			printf("pid is %d\n",pid);
		}
		else if(pid<0)
		{
			printf("unable to create child process\n");
		}
	return 3;
}