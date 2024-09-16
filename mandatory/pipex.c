/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 00:33:29 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/16 06:17:28 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_check_args(t_pipex *pipex, char **argv, int argc)
{
	pipex->invalid_infile = 0;
	pipex->invalid_outfile = 0;
	pipex->infile_fd = open(argv[1], O_RDONLY);
	pipex->outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (pipex->infile_fd < 0)
		pipex->invalid_infile = 1;
	if (pipex->outfile_fd < 0)
		pipex->invalid_outfile = 1;
}

void	free_string3(char ***str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			free(str[i][j]);
		free(str[i]);
	}
	free(str);
}

void	ft_parse_args(t_pipex *pipex, char **argv, int argc)
{
	char	***command_args;
	int		i;

	i = -1;
	pipex->commands = 0;
	command_args = malloc(sizeof(char **) * ((argc - 3) + 1));
	while (++i < (argc - 3))
	{
		command_args[i] = ft_split(argv[i + 2], ' ');
		++pipex->commands;
	}
	command_args[i] = NULL;
	pipex->cmd_args = command_args;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i >= n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	while (s[i] != '\0')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[++i] != '\0')
		res[i] = s1[i];
	while (s2[++j] != '\0')
		res[i + j] = s2[j];
	res[i + j] = '\0';
	return (res);
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

void	free_string2(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	fill_cmd_paths(t_pipex *pipex, char	**seperate_paths, int i, int j)
{
	char	*temp;
	char	*temp_path;

	temp = ft_strjoin(seperate_paths[j], "/");
	temp_path = ft_strjoin(temp, pipex->cmd_args[i][0]);
	free(temp);
	if ((access(temp_path, F_OK)) == 0)
	{
		pipex->cmd_paths[i] = temp_path;
		return (1);
	}
	free(temp_path);
	return (0);
}

void	free_paths(t_pipex *pipex, char **str)
{
	int	i;

	i = -1;
	while (++i < pipex->commands)
		free(str[i]);
	free(str);
}

void	ft_cleanup(t_pipex *pipex)
{
	if (pipex->cmd_args)
		free_string3(pipex->cmd_args);
	free_paths(pipex, pipex->cmd_paths);
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
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

void	ft_parse_cmds(t_pipex *pipex, char **envp)
{
	char	*paths;
	char	**seperate_paths;
	int		i;
	int		j;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		++i;
	paths = (envp[i] + 5);
	seperate_paths = ft_split(paths, ':');
	pipex->cmd_paths = ft_calloc(sizeof(char *), pipex->commands + 1);
	i = -1;
	while (++i < pipex->commands)
	{
		j = -1;
		while (++j < ft_strstrlen(seperate_paths))
		{
			if (fill_cmd_paths(pipex, seperate_paths, i, j))
				break ;
		}
	}
	command_not_found(pipex);
	free_string2(seperate_paths);
}

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
	if (execve(pipex->cmd_paths[0], pipex->cmd_args[0], envp) == -1)
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
	if (execve(pipex->cmd_paths[1], pipex->cmd_args[1], envp) == -1)
	{
		perror("Execve Failed");
		ft_cleanup(pipex);
		exit(EXIT_FAILURE);
	}
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
	waitpid(pid, NULL, 0);
	parent(pipex, envp, fd);
}

void	assign_pipex(t_pipex *pipex, char **argv, int argc, char **envp)
{
	ft_check_args(pipex, argv, argc);
	ft_parse_args(pipex, argv, argc);
	ft_parse_cmds(pipex, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc == 5)
	{
		assign_pipex(&pipex, argv, argc, envp);
		if (!pipex.cmd_not_found)
			ft_exec(&pipex, envp);
		ft_cleanup(&pipex);
	}
	else
		ft_printf("\033[0;31mError : Invalid Number of Arguments!\n\033[0m");
}
