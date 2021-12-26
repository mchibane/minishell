/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:08:34 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/08 15:32:15 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envll	*envll_newnode(char *line)
{
	t_envll	*ret;
	char	**elems;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	elems = envp_split_line(line);
	if (!elems)
		return (NULL);
	ret->line = ft_strdup(line);
	ret->key = ft_strdup(elems[0]);
	ret->value = ft_strdup(elems[1]);
	ret->visible = true;
	ret->prev = NULL;
	ret->next = NULL;
	free_tab(elems);
	return (ret);
}

int	envll_addback(t_envll **start, t_envll *node)
{
	t_envll	*tmp;

	if (node)
	{
		if (!start)
			start = &node;
		if (!(*start))
		{
			*start = node;
			node->next = NULL;
			node->prev = NULL;
			return (0);
		}
		tmp = *start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->next = NULL;
		node->prev = tmp;
		return (0);
	}
	return (1);
}

void	envll_rm_node(t_envll *node)
{
	envll_del_data(node);
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	if (node)
		free(node);
}

void	envll_clear(t_envll	**start)
{
	t_envll	*tmp;

	if (start)
	{
		tmp = *start;
		while (tmp)
		{
			*start = tmp;
			tmp = (*start)->next;
			envll_rm_node(*start);
		}
	}
}

t_envll	*envp_to_llist(char **envp)
{
	t_envll	*start;
	int		i;

	i = 0;
	start = NULL;
	while (envp[i])
	{
		if (envll_addback(&start, envll_newnode(envp[i])))
			return (NULL);
		i++;
	}
	return (start);
}
