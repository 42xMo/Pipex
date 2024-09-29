/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:21:16 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/29 08:31:10 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# define BUFFER_SIZE 1000000

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		invalid_infile;
	int		invalid_outfile;
	char	**cmd_paths;
	char	***cmd_args;
	int		commands;
	int		cmd_not_found;
	int		here_doc;
}			t_pipex;

void	*ft_calloc(size_t nmemb, size_t size);
int		count_words(char const *s, char c);
int		len_word(char const *s, char c, int index);
char	*get_word(char const *s, char c, int index);
char	**ft_split(char const *s, char c);
void	ft_check_args(t_pipex *pipex, char **argv, int argc);
void	free_string3(t_pipex *pipex, char ***str);
void	ft_parse_args(t_pipex *pipex, char **argv, int argc);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strstrlen(char **str);
void	free_string2(char **str);
int		fill_cmd_paths(t_pipex *pipex, char	**seperate_paths, int i, int j);
void	free_paths(t_pipex *pipex, char **str);
void	ft_cleanup(t_pipex *pipex);
void	command_not_found(t_pipex *pipex);
void	ft_parse_cmds(t_pipex *pipex, char **envp);
void	child(t_pipex *pipex, char **envp, int *fd, int i);
void	parent(int *fd);
void	ft_exec(t_pipex *pipex, char **envp, int i);
void	assign_pipex(t_pipex *pipex, char **argv, int argc, char **envp);
char	*assign_path(char **envp);
char	*get_next_line(int fd);
void	heredoc(t_pipex *pipex, char *limiter);

#endif