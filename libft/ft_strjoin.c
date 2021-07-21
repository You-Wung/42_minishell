/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyou <tyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:04:17 by tyou              #+#    #+#             */
/*   Updated: 2021/06/30 22:14:42 by tyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size1;
	int		size2;
	int		i;
	char	*rt;

	if (s1 && s2)
	{
		i = 0;
		size1 = ft_strlen(s1);
		size2 = ft_strlen(s2);
		rt = malloc(size1 + size2 + 1);
		if (!rt)
			return (NULL);
		while (i < size1)
		{
			rt[i] = s1[i];
			i++;
		}
		i = -1;
		while (++i < size2)
			rt[size1 + i] = s2[i];
		rt[size1 + i] = '\0';
		return (rt);
	}
	return (NULL);
}
