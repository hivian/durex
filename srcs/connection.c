/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 09:46:34 by hivian            #+#    #+#             */
/*   Updated: 2017/06/02 10:34:49 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

static t_sock_in		init_host()
{
	t_sock_in 			haddr;

	bzero((char *)&haddr, sizeof(haddr));
	haddr.sin_family = AF_INET;
	haddr.sin_addr.s_addr = INADDR_ANY;
	haddr.sin_port = htons(PORT);

	return haddr;
}

static int				create_socket(t_env *e)
{
	int hsock = socket(AF_INET, SOCK_STREAM, 0);
	if (hsock < 0) {
		fprintf(e->f_logs, "Failed initialization socket.");
		exit(EXIT_FAILURE);
	}

	int option = 1;
	if (setsockopt(hsock, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&option,sizeof(option)) < 0) {
		fprintf(e->f_logs, "Failed setting options to socket.");
		exit(EXIT_FAILURE);
	}
	return hsock;
}

int						create_server(t_env *e)
{
	e->haddr = init_host();
	e->hsock = create_socket(e);
	return (1);
}
