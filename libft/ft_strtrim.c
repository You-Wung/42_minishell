/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyou <tyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:16:24 by tyou              #+#    #+#             */
/*   Updated: 2021/06/30 22:15:26 by tyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size_s1;
	char	*rt;

	size_s1 = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 != '\0' && ft_strchr(set, *s1))
		s1++;
	while (s1[size_s1])
		size_s1++;
	while (size_s1 && ft_strchr(set, s1[size_s1]))
		size_s1--;
	rt = ft_substr((char *)s1, 0, size_s1 + 1);
	return (rt);
}
