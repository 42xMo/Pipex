/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 00:33:29 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/13 00:18:09 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_check_args(t_pipex *pipex, char **argv, int argc)
{
	//opens all files
	pipex->infile_fd = open(argv[1], O_RDONLY);
	pipex->outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT, 777);
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
	command_args = malloc(sizeof(char **) * ((argc - 3) + 1));
	while (++i < (argc - 3))
		command_args[i] = ft_split(argv[i + 2], ' ');
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

void	ft_parse_cmds(t_pipex *pipex, char **envp)
{
	char	*paths;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		++i;
	paths = (envp[i] + 5);
	pipex->cmd_paths = ft_split(paths, ':');
	//for visual showcase of the contents of the char**
	//i = -1;
	//while (pipex->cmd_paths[++i])
	//{
	//	ft_printf("%s\n", pipex->cmd_paths[i]);
	//}
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
void	ft_cleanup(t_pipex *pipex)
{
	free_string3(pipex->cmd_args);
	free_string2(pipex->cmd_paths);
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
		//while (commands)
		//	ft_exec();
		ft_cleanup(&pipex);
	}
	else
		ft_printf("\033[0;31mError : Invalid Number of Arguments!\n\033[0m");
}
