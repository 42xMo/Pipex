/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:22:43 by mabdessm          #+#    #+#             */
/*   Updated: 2024/10/01 12:54:25 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	child(t_pipex *pipex, char **envp, int *fd, int i)
{
	if (!pipex->here_doc && pipex->invalid_infile)
	{
		perror("Invalid Infile");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (execve(pipex->cmd_paths[i], pipex->cmd_args[i], envp) < 0)
	{
		perror("Execve Failed");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
}

void	parent(t_pipex *pipex, int *fd, int pid)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}

void	ft_exec_last(t_pipex *pipex, char **envp, int i)
{
	if (pipex->invalid_outfile)
	{
		perror("Invalid Outfile");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	if (execve(pipex->cmd_paths[i], pipex->cmd_args[i], envp) < 0)
	{
		perror("Execve Failed");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
}

void	ft_exec(t_pipex *pipex, char **envp, int i)
{
	int		fd[2];
	pid_t	pid;

	if (i == pipex->commands - 1)
		ft_exec_last(pipex, envp, i);
	else
	{
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
			child(pipex, envp, fd, i);
		else
			parent(pipex, fd, pid);
	}
}
