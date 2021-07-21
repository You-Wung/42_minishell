/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyou <tyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 13:20:55 by tyou              #+#    #+#             */
/*   Updated: 2021/01/15 00:17:09 by tyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	c;

	s = (unsigned char *)ptr;
	c = (unsigned char)value;
	i = 0;
	while (i < num)
	{
		if (*(s + i) == c)
			return (s + i);
		i++;
	}
	return (NULL);
}
