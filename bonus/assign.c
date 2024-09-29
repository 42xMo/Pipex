/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:26:23 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/29 06:38:43 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_check_args(t_pipex *pipex, char **argv, int argc)
{
	pipex->invalid_infile = 0;
	pipex->invalid_outfile = 0;
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->here_doc)
		pipex->outfile_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else
		pipex->outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (pipex->infile_fd < 0)
		pipex->invalid_infile = 1;
	if (pipex->outfile_fd < 0)
		pipex->invalid_outfile = 1;
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

void	ft_parse_cmds(t_pipex *pipex, char **envp)
{
	char	*paths;
	char	**seperate_paths;
	int		i;
	int		j;

	paths = assign_path(envp);
	seperate_paths = ft_split(paths, ':');
	pipex->cmd_paths = ft_calloc(sizeof(char *), pipex->commands + 1);
	i = -1;
	while (++i < pipex->commands)
	{
		if (!pipex->cmd_args[i] || !pipex->cmd_args[i][0])
		{
			pipex->cmd_paths[i] = NULL;
			continue ;
		}
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

void	assign_pipex(t_pipex *pipex, char **argv, int argc, char **envp)
{
	ft_check_args(pipex, argv, argc);
	ft_parse_args(pipex, argv, argc);
	ft_parse_cmds(pipex, envp);
}
