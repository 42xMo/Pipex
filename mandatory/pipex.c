/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 00:33:29 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/12 06:22:43 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_check_args(t_pipex *pipex, char **argv, int argc)
{
	//opens all files
	pipex->infile_fd = open(argv[1], O_RDONLY);
	pipex->outfile_fd = open(argv[argc - 1], O_WRONLY); 
	//if -1, use access() to know if file exists but doesnt have the rights or if it doesnt exist at all
	if (pipex->infile_fd == -1)
		pipex->invalid_infile = 1; // can it be invalid in other ways?
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
		while(str[i][++j])
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
	while (++i < ((argc - 3)))
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

void	ft_cleanup(t_pipex *pipex)
{
	free_string3(pipex->cmd_args);
}

void	assign_pipex(t_pipex *pipex, char **argv, int argc)
{
	ft_check_args(pipex, argv, argc);
	ft_parse_args(pipex, argv, argc);
	//ft_parse_cmds();		//to assign pipex->cmd_paths = ; //need to use envp
}

int	main(int argc, char **argv)
{
	t_pipex pipex;

	if (argc == 5)
	{
		assign_pipex(&pipex, argv, argc);
		//while (commands)
		//	ft_exec();
		ft_cleanup(&pipex);
	}
	else
		ft_printf("\033[0;31mError : Invalid Number of Arguments!\n\033[0m");
}
