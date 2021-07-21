/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyou <tyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:18:37 by tyou              #+#    #+#             */
/*   Updated: 2021/06/30 22:14:14 by tyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*rt;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s1[size])
		size++;
	rt = (char *)malloc(size + 1);
	if (!rt)
		return (0);
	while (i < size)
	{
		rt[i] = s1[i];
		i++;
	}
	rt[i] = '\0';
	return (rt);
}
