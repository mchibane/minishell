/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:19:36 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/15 13:05:24 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

void	free_pipefd(int **pipefd, int cmd_nb)
{
	int	i;

	if (pipefd)
	{
		i = 0;
		while (i < cmd_nb - 1)
		{
			if (pipefd[i] == NULL)
				break ;
			free(pipefd[i]);
			i++;
		}
		free(pipefd);
	}
}

int	**get_pipefds(int cmd_nb)
{
	int	**ret;
	int	i;

	ret = malloc(sizeof(*ret) * (cmd_nb - 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < cmd_nb - 1)
	{
		ret[i] = malloc(sizeof(**ret) * 2);
		if (!ret[i])
		{
			free_pipefd(ret, cmd_nb);
			return (NULL);
		}
		pipe(ret[i]);
		i++;
	}
	return (ret);
}

void	close_pipes(int **pipefd, int cmd_nb)
{
	int	i;

	i = 0;
	while (i < cmd_nb - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

void	handle_pipefds(int **pipefd, int index, int cmd_nb)
{
	int	i;

	if (pipefd != NULL)
	{
		i = 0;
		while (i < cmd_nb - 1)
		{
			if (i != index)
				close(pipefd[i][1]);
			if (i + 1 != index)
				close(pipefd[i][0]);
			i++;
		}
		if (index != cmd_nb -1)
		{
			dup2(pipefd[index][1], STDOUT_FILENO);
			close(pipefd[index][1]);
		}
		if (index != 0)
		{
			dup2(pipefd[index - 1][0], STDIN_FILENO);
			close(pipefd[index - 1][0]);
		}
	}
}
