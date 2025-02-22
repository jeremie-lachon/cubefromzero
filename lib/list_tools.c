/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:59:39 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/22 17:04:43 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	listfree(t_list *list)
{
	if (list)
	{
		listfree(list->next);
		free(list->data);
	}
	free(list);
	return (0);
}

int	listaddfront(t_list **list, t_list *new)
{
	new->next = *list;
	*list = new;
	return (0);
}

t_list	*listnew(void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (perror("Error\n"), NULL);
	new->data = data;
	new->next = 0;
	return (new);
}

int	listsize(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int	maxsize(t_list *list)
{
	int	maxlen;
	int	len;

	maxlen = -1;
	while (list)
	{
		len = ft_strlen((char *)list->data);
		if (len > maxlen)
			maxlen = len;
		list = list->next;
	}
	return (maxlen);
}
