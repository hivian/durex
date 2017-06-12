/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 14:21:44 by hivian            #+#    #+#             */
/*   Updated: 2017/06/12 16:50:25 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void	print_logs(FILE *file, char *str)
{
	pthread_mutex_lock(&lock);
	fprintf(file, "%s\n", str);
	fflush(file);
	pthread_mutex_unlock(&lock);
}

void	print_logs_n(FILE *file, char *str)
{
	pthread_mutex_lock(&lock);
	fprintf(file, "%s", str);
	fflush(file);
	pthread_mutex_unlock(&lock);
}
