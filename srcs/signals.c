/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 12:22:42 by hivian            #+#    #+#             */
/*   Updated: 2017/06/05 12:25:19 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void		catch_sig(int sig)
{
	char	str[256];

	bzero(str, sizeof(str));
	remove(LOCK_PATH);
	remove(LOG_PATH);
	
	fprintf(stdout, "Process killed with value: %d", sig);
	exit(EXIT_SUCCESS);
}

void		signal_handler()
{
	signal(SIGHUP, catch_sig);
	signal(SIGINT, catch_sig);
	signal(SIGQUIT, catch_sig);
	signal(SIGILL, catch_sig);
	signal(SIGTRAP, catch_sig);
	signal(SIGABRT, catch_sig);
	signal(SIGBUS, catch_sig);
	signal(SIGFPE, catch_sig);
	signal(SIGUSR1, catch_sig);
	signal(SIGSEGV, catch_sig);
	signal(SIGUSR2, catch_sig);
	signal(SIGPIPE, catch_sig);
	signal(SIGALRM, catch_sig);
	signal(SIGTERM, catch_sig);
	signal(SIGCHLD, catch_sig);
	signal(SIGCONT, catch_sig);
	signal(SIGSTOP, catch_sig);
	signal(SIGTSTP, catch_sig);
	signal(SIGTTIN, catch_sig);
	signal(SIGTTOU, catch_sig);
	signal(SIGURG, catch_sig);
	signal(SIGXCPU, catch_sig);
	signal(SIGXFSZ, catch_sig);
	signal(SIGVTALRM, catch_sig);
	signal(SIGPROF, catch_sig);
	signal(SIGWINCH, catch_sig);
	signal(SIGIO, catch_sig);
	signal(SIGPWR, catch_sig);
	signal(SIGSYS, catch_sig);
}
