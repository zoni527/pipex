/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:39:06 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/19 15:21:05 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*clear(t_list **lst, void *content, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*prev_node;
	void	*new_content;

	new_lst = NULL;
	prev_node = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
			return (clear(&new_lst, new_content, del));
		new_node = ft_lstnew(new_content);
		if (!new_node)
			return (clear(&new_lst, new_content, del));
		if (!new_lst)
			new_lst = new_node;
		lst = lst->next;
		if (!prev_node)
			prev_node = new_node;
		prev_node->next = new_node;
		prev_node = prev_node->next;
	}
	return (new_lst);
}

static void	*clear(t_list **lst, void *content, void (*del)(void *))
{
	if (*lst)
		ft_lstclear(lst, del);
	if (content)
		del(content);
	return (NULL);
}
