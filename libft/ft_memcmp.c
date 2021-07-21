/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyou <tyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 00:07:41 by tyou              #+#    #+#             */
/*   Updated: 2021/06/30 21:59:05 by tyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i <= n)
	{
		if (*((char *)s1 + i) != *((char *)s2 + i))
			return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
		while (*((char *)s1 + i) == *((char *)s2 + i))
		{
			if (i == n - 1)
				return (0);
			i++;
		}
		if (*((char *)s1 + i) != *((char *)s2 + i))
			continue ;
		i++;
	}
	return (0);
}
