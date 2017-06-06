/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:25:59 by hivian            #+#    #+#             */
/*   Updated: 2017/06/06 17:22:46 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void		run(int fd_client)
{
	//int toto = dup(fd_client);
	pid_t pid = fork();
	if (pid == 0) {
		dup2(STDOUT_FILENO, fd_client);
		dup2(STDERR_FILENO, fd_client);
		/*char *args[2];
		args[0] = "/bin/ls";
		args[1] = NULL;*/
		//execl("/bin/ls", "/bin/ls", NULL);
		system("/bin/ls");
	} else {
		wait(NULL);
	}
	//dup2(toto, fd_client);
	char *message = "toto\n";
	send(fd_client, message, strlen(message), 0);
}
