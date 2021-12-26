/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:53:29 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 17:28:32 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

static void	unlink_redirs(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == R_HERE_DOC)
			unlink(tmp->file);
		tmp = tmp->next;
	}
}

void	unlink_hd(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		unlink_redirs(tmp->redirs);
		tmp = tmp->next;
	}
}
