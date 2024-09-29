/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 05:45:50 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/29 07:51:12 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*return_and_free(char *str1, char *str2)
{
	free(str1);
	return (str2);
}

char	*ft_read_and_return(int fd, char *buffer, char *line)
{
	int	i;
	int	j;

	j = read(fd, buffer, BUFFER_SIZE);
	while (j > 0)
	{
		buffer[j] = '\0';
		line = ft_strjoin_and_free(line, buffer);
		i = -1;
		while (buffer[++i])
		{
			if (buffer[i] == '\n')
				return (return_and_free(buffer, line));
		}
	}
	free(buffer);
	if (j == 0 && line[0] == '\0')
		return (return_and_free(line, NULL));
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = (char *)ft_calloc(sizeof(char), 1);
	if (!line)
		return (return_and_free(buffer, NULL));
	return (ft_read_and_return(fd, buffer, line));
}
