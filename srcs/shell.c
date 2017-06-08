/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:25:59 by hivian            #+#    #+#             */
/*   Updated: 2017/06/08 17:32:40 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void			*shell_handler(void *context)
{
	int			ret;
	char		buffer[BUF_SIZE];
	char		str[256];
	t_thread_params	*c = (t_thread_params*) context;

	bzero(str, sizeof(str));
	bzero(buffer, sizeof(buffer));
	//create_server(e);
	//c->shell_on = false;
	while ((ret = recv(c->csock, buffer, BUF_SIZE, 0)) > 0) {
		char *trim = strtrim(buffer);
		if (!trim)
		{
			print_logs(c->logs, "Malloc error");
			continue ;
		}
		if (!strcmp(trim, "exit")) {
			ret = 0;
			break ;
		}
		//
		/*if (fork()) {
			dup2(c->csock, STDOUT_FILENO);
			dup2(c->csock, STDERR_FILENO);
		} else {
			wait(NULL);
		}*/
		/*pthread_mutex_lock(&lock);
		dup2(c->csock, STDOUT_FILENO);
		dup2(c->csock, STDERR_FILENO);
		system(buffer);
		pthread_mutex_unlock(&lock);
		bzero(buffer, sizeof(buffer));*/
		//
		dup2(c->csock, STDOUT_FILENO);
		dup2(c->csock, STDERR_FILENO);
		//close(c->csock);
		pid_t pid = fork();
		if (!pid) {
			//setresuid(0, 0, 0);
			char *cmd[] = { "ls", "-l", (char *)0 };
			execve ("/bin/ls", cmd, NULL);
			send(c->csock, "Received\n", 9, 0);
		} else {
			int status;
			waitpid(pid, &status, 0);
		}
		dup2(c->save_out, STDOUT_FILENO);
		dup2(c->save_err, STDERR_FILENO);
		//close(c->save_out);
		//close(c->save_err);
	}
	if (ret == 0)
    {
		pthread_mutex_lock(&lock);
		c->total_connection--;
		pthread_mutex_unlock(&lock);
		snprintf(str, sizeof(str), "[Client %s:%d] disconnected.", c->cli_ip, c->cli_port);
		print_logs(c->logs, str);
    }
    else if (ret == -1)
		print_logs(c->logs, "Recv error");
	c->shell_on = false;
	close(c->csock);
	return (NULL);
}
