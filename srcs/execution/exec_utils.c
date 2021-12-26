/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:18:59 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/15 13:19:22 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

int	get_cmd_nbr(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		ret;

	tmp = cmds;
	ret = 0;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}
