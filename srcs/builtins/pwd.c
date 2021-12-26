/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:00:23 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/21 13:48:20 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_cmd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	if (!ret)
		return (1);
	if (write(1, ret, ft_strlen(ret)) == -1)
	{
		write_error("pwd");
		return (1);
	}
	write(1, "\n", 1);
	free(ret);
	return (0);
}
