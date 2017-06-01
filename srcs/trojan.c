/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trojan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 15:20:54 by hivian            #+#    #+#             */
/*   Updated: 2017/06/01 16:40:52 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void		lock_file(FILE *f_logs) {
	FILE	*lockfile = fopen(LOCK_PATH, "w+");

	if (fileno(lockfile) == -1) {
		fprintf(f_logs, "Could not open PID lock file %s, exiting\n", LOCK_PATH);
        exit(EXIT_FAILURE);
	}
	if (lockf(fileno(lockfile), F_TLOCK, 0) == -1) {
		fprintf(f_logs, "Could not lock PID lock file %s, exiting\n", LOCK_PATH);
        exit(EXIT_FAILURE);
	}
}

void		trojan()
{
	FILE *f_logs= NULL;
	pid_t process_id = 0;
	pid_t sid = 0;
	process_id = fork();
	if (process_id < 0)
	{
		printf("fork failed!\n");
		exit(1);
	}
	if (process_id > 0)
	{
		printf("process_id of child process %d \n", process_id);
		exit(0);
	}
	umask(027);
	sid = setsid();
	if(sid < 0)
	{
		exit(1);
	}
	chdir("/");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	f_logs = fopen ("/var/log/durex.log", "w+");
	lock_file(f_logs);
	while (1)
	{
		sleep(1);
		fprintf(f_logs, "Logging info...\n");
		fflush(f_logs);
	}
	fclose(f_logs);
}
