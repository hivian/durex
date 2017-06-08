/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:25:59 by hivian            #+#    #+#             */
/*   Updated: 2017/06/08 11:28:13 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void			*shell_handler(void *context)
{
	int			ret;
    //char		buffer[BUF_SIZE];
	char		str[256];
	t_thread_params	*c = (t_thread_params*)context;

	bzero(str, sizeof(str));
	//bzero(buffer, sizeof(buffer));
	while (1) {
		/*if (!fork()) {
			dup2(c->csock, STDOUT_FILENO);
			dup2(c->csock, STDERR_FILENO);
			setresuid(0, 0, 0);
			execl("/bin/ls", "ls", NULL, (char *)0);
			//system(buffer);
		} else {
			wait(NULL);
		}
		bzero(buffer, sizeof(buffer));*/
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
		print_logs(c->logs, "Recv error");
	c->shell_on = false;
	//pthread_exit(NULL);
}
