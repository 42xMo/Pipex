/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:27:46 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/16 17:19:05 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_string3(t_pipex *pipex, char ***str)
{
	int	i;
	int	j;

	i = -1;
	while (++i < pipex->commands)
	{
		j = -1;
		if (str[i])
		{
			while (str[i][++j])
				free(str[i][j]);
			free(str[i]);
		}
	}
	free(str);
}

void	free_string2(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	free_paths(t_pipex *pipex, char **str)
{
	int	i;

	i = -1;
	while (++i < pipex->commands)
	{
		if (str[i])
			free(str[i]);
	}
	free(str);
}

void	command_not_found(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->cmd_not_found = 0;
	while (++i < pipex->commands)
	{
		if (!pipex->cmd_paths[i])
		{
			ft_printf("%s: Command Not Found\n", pipex->cmd_args[i][0]);
			pipex->cmd_not_found = 1;
			return ;
		}
	}
}

char	*assign_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		++i;
	return (envp[i] + 5);
}
