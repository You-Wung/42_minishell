/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyou <tyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:34:38 by tyou              #+#    #+#             */
/*   Updated: 2021/06/30 20:42:00 by tyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nxt;
	t_list	*save;

	if (*lst)
	{
		nxt = *lst;
		while (nxt->next != NULL)
		{
			del(nxt->content);
			save = nxt->next;
			free(nxt);
			nxt = save;
		}
		del(nxt->content);
		free(nxt);
		*lst = NULL;
	}
}
