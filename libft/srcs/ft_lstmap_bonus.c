/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:33:04 by julienngy         #+#    #+#             */
/*   Updated: 2019/11/21 11:32:22 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*tmp;

	if (!f || !lst)
		return (NULL);
	if (!(tmp = ft_lstnew(f(lst->content))))
		return (NULL);
	list = tmp;
	while ((lst = lst->next))
	{
		if (!(tmp->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (list);
}
