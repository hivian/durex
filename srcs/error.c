/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 14:21:44 by hivian            #+#    #+#             */
/*   Updated: 2017/06/01 14:26:52 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

int		x_int(int err, int res, char *str, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n",
		str, file, line, strerror(errno));
		exit (1);
	}
	return (res);
}

void	*x_void(void *err, void *res, char *str, char *file, int line)
{
  if (res == err)
    {
      fprintf(stderr, "%s error (%s, %d): %s\n",
	      str, file, line, strerror(errno));
      exit (1);
    }
  return (res);
}
