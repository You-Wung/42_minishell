/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyou <tyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:44:17 by tyou              #+#    #+#             */
/*   Updated: 2021/06/30 22:14:53 by tyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		len;
	size_t		s_dst;
	size_t		s_src;

	s_dst = ft_strlen(dst);
	s_src = ft_strlen(src);
	len = s_dst + s_src;
	if (size <= s_dst)
		return (s_src + size);
	while (*dst)
		dst++;
	i = 0;
	while (i < size - s_dst - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
