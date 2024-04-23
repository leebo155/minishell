/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:25:50 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/22 16:44:03 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*res;
	t_list	*new;
	void	*f_res;

	p = lst;
	res = NULL;
	while (p != NULL)
	{
		f_res = f(p->content);
		new = ft_lstnew(f_res);
		if (new == NULL)
		{
			del(f_res);
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, new);
		p = p->next;
	}
	return (res);
}
