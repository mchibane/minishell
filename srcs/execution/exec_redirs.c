/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:22:11 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/17 18:00:02 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

static int	handle_stdout(t_redir *redir)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (redir->fd == -1)
	{
		perror(redir->file);
		return (1);
	}
	dup2(redir->fd, STDOUT_FILENO);
	close(redir->fd);
	return (0);
}

static int	handle_append(t_redir *redir)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (redir->fd == -1)
	{
		perror(redir->file);
		return (1);
	}
	dup2(redir->fd, STDOUT_FILENO);
	close(redir->fd);
	return (0);
}

static int	handle_stdin(t_redir *redir)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd == -1)
	{
		perror(redir->file);
		return (1);
	}
	dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	return (0);
}

static int	handle_redir(t_redir *redir)
{
	if (redir->type == R_HERE_DOC || redir->type == R_STDIN)
		return (handle_stdin(redir));
	if (redir->type == R_STDOUT)
		return (handle_stdout(redir));
	if (redir->type == R_APPEND)
		return (handle_append(redir));
	return (0);
}

int	exec_redirs(t_cmd *cmd)
{
	t_redir	*tmp;
	int		status;

	status = 0;
	if (cmd->redirs)
	{
		tmp = cmd->redirs;
		while (tmp)
		{
			status = handle_redir(tmp);
			if (status)
				return (status);
			tmp = tmp->next;
		}
	}
	return (0);
}
