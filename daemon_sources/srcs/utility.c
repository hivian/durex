/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 09:36:17 by hivian            #+#    #+#             */
/*   Updated: 2017/07/17 17:09:18 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

pthread_attr_t		thread_init()
{
	pthread_attr_t	thread_attr;

	if (pthread_attr_init(&thread_attr) != 0) {
		fprintf (stderr, "pthread_attr_init error");
		exit(EXIT_SUCCESS);
    }

	if (pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
		fprintf (stderr, "pthread_attr_setdetachstate error");
		exit(EXIT_SUCCESS);
    }
	return (thread_attr);
}

char				*strtrim(char const *s)
{
	char	*str;
	size_t	len;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	len = strlen(s);
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	str = strndup(s, len);
	return (str);
}

void				strdel(char **as)
{
	if (as != NULL)
	{
		free(*as);
		*as = NULL;
	}
}
