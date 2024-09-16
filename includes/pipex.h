/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:06:06 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/16 04:43:47 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

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
	//int		here_doc;		// 1 if there is here_doc, 0 otherwise (bonus)
}			t_pipex;

void		*ft_calloc(size_t nmemb, size_t size);
int			count_words(char const *s, char c);
int			len_word(char const *s, char c, int index);
char		*get_word(char const *s, char c, int index);
char		**ft_split(char const *s, char c);

#endif