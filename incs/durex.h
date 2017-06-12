/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 14:25:26 by hivian            #+#    #+#             */
/*   Updated: 2017/06/12 17:10:26 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUREX_H
# define DUREX_H

# define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define DAEMON ""

int				x_int(int err, int res, char *str, char *file, int line);
void			*x_void(void *err, void *res, char *str, char *file, int line);

#endif
