/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:27:26 by hivian            #+#    #+#             */
/*   Updated: 2017/06/05 12:31:25 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

int g_total;

void		*connection_handler(void *context)
{
    int read_size;
    char buffer[4096];
	t_thread_params *c = (t_thread_params*)context;
	char str[256];

	bzero(str, sizeof(str));
	bzero(buffer, sizeof(buffer));
	char *message = "Password: ";
    send(c->sock , message, strlen(message), 0);
    while ((read_size = recv(c->sock, buffer, 4096, 0)) > 0)
    {
		snprintf(str, sizeof(str), "says: %s\n", buffer);
		print_logs(c->logs, str);
		write(c->sock , buffer , strlen(buffer));
    }
    if (read_size == 0)
    {
		g_total--;
		//snprintf(str, sizeof(str), "Client disconnected: %s:%d\n", e->client_ip, e->client_port);
		print_logs(c->logs,  "Client disconnected");
    }
    else if (read_size == -1)
    {
		print_logs(c->logs, "Recv error");
    }
    return 0;
}
