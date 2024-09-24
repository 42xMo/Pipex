/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 00:33:29 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/20 16:30:54 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_cleanup(t_pipex *pipex)
{
	free_string3(pipex, pipex->cmd_args);
	free_paths(pipex, pipex->cmd_paths);
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
}

void	clean_exit(t_pipex *pipex)
{
	perror("Command Not Found");
	if (!pipex->cmd_paths[pipex->commands - 1])
	{
		ft_cleanup(pipex);
		exit(127);
	}
	else
	{
		ft_cleanup(pipex);
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc >= 5)
	{
		assign_pipex(&pipex, argv, argc, envp);
		if (!pipex.cmd_not_found)
		{
			ft_exec(&pipex, envp);
			ft_cleanup(&pipex);
		}
		else
			clean_exit(&pipex);
	}
	else
		ft_printf("\033[0;31mError : Invalid Number of Arguments!\n\033[0m");
}
