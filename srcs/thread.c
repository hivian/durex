/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:27:26 by hivian            #+#    #+#             */
/*   Updated: 2017/06/06 10:05:52 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

pthread_attr_t		thread_init()
{
	pthread_attr_t	thread_attr;

	if (pthread_attr_init (&thread_attr) != 0) {
		fprintf (stderr, "pthread_attr_init error");
		exit(EXIT_SUCCESS);
    }

	if (pthread_attr_setdetachstate (&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
		fprintf (stderr, "pthread_attr_setdetachstate error");
		exit(EXIT_SUCCESS);
    }
	return (thread_attr);
}

void				*thread_handler(void *context)
{
    int ret;
    char buffer[BUF_SIZE];
	t_thread_params *c = (t_thread_params*)context;
	char str[BUF_SIZE + 256];
	char salt[] = "A9";
	char *const pass = "A9ydQdSSfi/JY"

	bzero(str, sizeof(str));
	bzero(buffer, sizeof(buffer));
	char *message = "Password: ";
    send(c->sock, message, strlen(message), 0);
    while ((ret = recv(c->sock, buffer, BUF_SIZE, 0)) > 0)
    {
		snprintf(str, sizeof(str), "[Client %s:%d] > %s", c->cli_ip, c->cli_port, buffer);

		char *toto = strdup(crypt(strtrim(buffer), salt));
		print_logs(c->logs, toto);
		fflush(c->logs);
		send(c->sock , buffer , strlen(buffer), 0);
		bzero(str, sizeof(str));
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
    {
		print_logs(c->logs, "Recv error");
		pthread_exit(NULL);
    }
	return (0);
}
