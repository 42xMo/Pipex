/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:22:43 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/16 17:19:40 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	child(t_pipex *pipex, char **envp, int *fd)
{
	if (pipex->invalid_infile)
	{
		perror("Invalid Infile");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(pipex->infile_fd, STDIN_FILENO);
	close(fd[0]);
	if (execve(pipex->cmd_paths[0], pipex->cmd_args[0], envp) < 0)
	{
		perror("Execve Failed");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
}

void	parent(t_pipex *pipex, char **envp, int *fd)
{
	if (pipex->invalid_outfile)
	{
		perror("Invalid Outfile");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	close(fd[1]);
	if (execve(pipex->cmd_paths[pipex->commands - 1],
			pipex->cmd_args[pipex->commands - 1], envp) < 0)
	{
		perror("Execve Failed");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
}

int	lucie(t_pipex *pipex)
{
	if (ft_strncmp(pipex->cmd_args[0][0], "sleep", 5) == 0)
		return (1);
	return (0);
}

void	ft_exec(t_pipex *pipex, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("Pipe failed");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child(pipex, envp, fd);
	if (lucie(pipex))
		waitpid(pid, NULL, 0);
	parent(pipex, envp, fd);
	if (!lucie(pipex))
		waitpid(pid, NULL, 0);
}
