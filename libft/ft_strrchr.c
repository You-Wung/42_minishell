/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyou <tyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 21:17:09 by tyou              #+#    #+#             */
/*   Updated: 2021/06/30 22:15:17 by tyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	size;

	size = 0;
	while (s[size])
		size++;
	if ((char)c == '\0')
		return ((char *)s + size);
	while (size)
	{
		if (s[size] == c)
			return ((char *)s + size);
		size--;
	}
	if (s[size] == (char)c)
		return ((char *)s);
	return (NULL);
}
