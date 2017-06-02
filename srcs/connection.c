/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 09:46:34 by hivian            #+#    #+#             */
/*   Updated: 2017/06/02 12:19:57 by hivian           ###   ########.fr       */
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
	if (setsockopt(hsock, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR),
	(char*)&option, sizeof(option)) < 0) {
		fprintf(e->f_logs, "Failed setting options to socket.");
		exit(EXIT_FAILURE);
	}
	return hsock;
}

void					get_client_ip(t_env *e)
{
	struct sockaddr_storage addr;
	socklen_t len = sizeof(addr);

	bzero(e->client_ip, sizeof(e->client_ip));
	getpeername(e->csock, (struct sockaddr*)&addr, &len);
	if (addr.ss_family == AF_INET) {
	    struct sockaddr_in *s = (struct sockaddr_in *)&addr;
	    e->client_port = ntohs(s->sin_port);
	    inet_ntop(AF_INET, &s->sin_addr, e->client_ip, sizeof(e->client_ip));
	} else {
	    struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
	    e->client_port = ntohs(s->sin6_port);
	    inet_ntop(AF_INET6, &s->sin6_addr, e->client_ip, sizeof(e->client_ip));
	}
}

void					create_server(t_env *e)
{
	e->haddr = init_host();
	e->hsock = create_socket(e);

	if ((e->bind = bind(e->hsock, (struct sockaddr *)&e->haddr, sizeof(e->haddr))) == -1)
	{
		fprintf(e->f_logs, "Failed binding socket");
		exit(EXIT_FAILURE);
	}
	if ((e->listen = listen(e->hsock, 3)) == -1)
	{
		fprintf(e->f_logs, "Failed listening socket");
		exit(EXIT_FAILURE);
	}
	e->haddr_size = sizeof(t_sock_in);
}
