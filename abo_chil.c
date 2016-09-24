#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include "comon1.h"
#include "abo_chil.h"
void abo_chil(void)
{
	pid_t kidpid;
	int status;
	while ((kidpid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		printf("\nChild with pid %d exited normally\n", kidpid);
	}
	siglongjmp(env,1);
}