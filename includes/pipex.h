/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:06:06 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/13 03:11:41 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../printf/ft_printf.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		infile_fd;			// fd of the infile
	int		outfile_fd;			// fd of the outfile
	int		invalid_infile;		// 1 if infile is invalid, 0 otherwise
	char	**cmd_paths;		// stores the path for the commands using envp
								// example : ["/bin/cat", "/usr/bin/wc"]
	char	***cmd_args;		// stores the commands and their args
								// example : [["cat"], ["wc","-l"]]
								// NULL TERMINATE the strings of course
	int		commands;			// number of commands
	//int		 here_doc;		// 1 if there is here_doc, 0 otherwise (bonus)
}			t_pipex;

void	*ft_calloc(size_t nmemb, size_t size);
int		count_words(char const *s, char c);
int		len_word(char const *s, char c, int index);
char	*get_word(char const *s, char c, int index);
char	**ft_split(char const *s, char c);

#endif