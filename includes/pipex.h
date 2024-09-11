/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:06:06 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/11 23:33:35 by mabdessm         ###   ########.fr       */
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
	char	**cmd_paths;		// 
	char	***cmd_args;		// 
	//int		commands;			// number of commands (bonus)
	//int		 here_doc;			// 1 if there is here_doc, 0 otherwise (bonus)
}			t_pipex;

#endif