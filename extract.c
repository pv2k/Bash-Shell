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
int extract(char str[],char *name[],int l1)
{
	int i;
	for(i=1;i<l1;i++)
		str[i-1]= name[1][i];
	str[i-1]='\0';
	return 0;
}