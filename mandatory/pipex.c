/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 00:33:29 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/13 06:56:06 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_check_args(t_pipex *pipex, char **argv, int argc)
{
	//opens all files
	pipex->infile_fd = open(argv[1], O_RDONLY);
	pipex->outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (pipex->infile_fd < 0)
		pipex->invalid_infile = 1;
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	//for visual showcase of the contents of the fds and the bool
	//ft_printf("%i\n%i\n%i\n", pipex->infile_fd, pipex->outfile_fd, pipex->invalid_infile);
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
	//for visual showcase of the contents of the char***
	// int	j;
	// i = -1;
	// while (pipex->cmd_args[++i])
	// {
	// 	j = -1;
	// 	while(pipex->cmd_args[i][++j])
	// 	{
	// 		ft_printf("%s\n", pipex->cmd_args[i][j]);
	// 	}
	// 	ft_printf("\\0\n");
	// }
	// ft_printf("number of cmds : %i\n", pipex->commands);
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
	while(str[i])
		++i;
	return (i);
}

void	free_string2(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
	}
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
		return(1);
	}
	free(temp_path);
	return(0);
}

void	command_not_found(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->commands)
	{
		if (!pipex->cmd_paths[i])
		{
			ft_printf("command not found: %s\n", pipex->cmd_args[i][0]);
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
				break;
		}
	}
	command_not_found(pipex);
	free_string2(seperate_paths);
	//for visual showcase of the contents of the char**
	// i = -1;
	// while (++i < pipex->commands)
	// 	ft_printf("%s\n", pipex->cmd_paths[i]);
}

void	ft_cleanup(t_pipex *pipex)
{
	free_string3(pipex->cmd_args);
	free_string2(pipex->cmd_paths);
}

void	ft_exec(t_pipex *pipex)
{
	//dup2
	//fork
	//pipe
	//execve
	//wait
	//unlink
	//access
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
		//ft_exec(&pipex);
		ft_cleanup(&pipex);
	}
	else
		ft_printf("\033[0;31mError : Invalid Number of Arguments!\n\033[0m");
}
