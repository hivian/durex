/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 12:22:42 by hivian            #+#    #+#             */
/*   Updated: 2017/06/08 14:45:09 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void		catch_sig(int sig)
{
	//char	str[256];
	(void)sig;
	//bzero(str, sizeof(str));
	remove(LOCK_PATH);
	remove(LOG_PATH);
	//snprintf(str, sizeof(str), "Process killed with value: %d", sig);
	//print_logs(str)
	//fprintf(stdout, "Process killed with value: %d", sig);
	pthread_exit(NULL);
	exit(EXIT_SUCCESS);
}

void		signal_handler()
{
	signal(SIGINT, catch_sig);
}
