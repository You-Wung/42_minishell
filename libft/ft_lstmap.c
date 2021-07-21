/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyou <tyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 23:58:55 by tyou              #+#    #+#             */
/*   Updated: 2021/06/30 21:54:41 by tyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*nxt;

	nxt = ft_lstnew(f(lst->content));
	if (!nxt)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	lst = lst->next;
	ret = nxt;
	while (lst)
	{
		nxt = ft_lstnew(f(lst->content));
		if (!nxt)
		{
			ft_lstclear(&ret, del);
			ft_lstclear(&lst, del);
			break ;
		}
		ft_lstadd_back(&ret, nxt);
		lst = lst->next;
	}
	return (ret);
}
