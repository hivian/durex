/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:27:26 by hivian            #+#    #+#             */
/*   Updated: 2017/06/06 13:34:31 by hivian           ###   ########.fr       */
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

static void			handle_buffer(t_thread_params *c, char *buffer)
{
	char			salt[] = "A9";
	char const		*pass = "A9ydQdSSfi/JY";
	char			*message;
	char			str[256];

	char *trim = strtrim(buffer);
	bzero(str, sizeof(str));
	if (!trim)
	{
		print_logs(c->logs, "Malloc error");
		return ;
	}
	if (!strcmp(crypt(trim, salt), pass)) {
		message = "Authentication success.\n";
		snprintf(str, sizeof(str), "[Client %s:%d] %s",
			c->cli_ip, c->cli_port, message);
	} else {
		message = "Authentication failed.\n";
		snprintf(str, sizeof(str), "[Client %s:%d] %s",
			c->cli_ip, c->cli_port, message);
	}
	print_logs_n(c->logs, str);
	send(c->sock, message, strlen(message), 0);
	bzero(str, sizeof(str));
	bzero(buffer, BUF_SIZE);
	if (trim)
		free(trim);
}

void				*thread_handler(void *context)
{
    int				ret;
    char			buffer[BUF_SIZE];
	char			str[256];
	t_thread_params	*c = (t_thread_params*)context;

	bzero(str, sizeof(str));
	bzero(buffer, sizeof(buffer));
	char *message = "Password: ";
    send(c->sock, message, strlen(message), 0);
    while ((ret = recv(c->sock, buffer, BUF_SIZE, 0)) > 0)
		handle_buffer(c, buffer);
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
	pthread_exit(NULL);
	return (0);
}
