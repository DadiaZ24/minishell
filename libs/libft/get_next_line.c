/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:53:50 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/07/03 20:25:55 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_data(char *stash, char *buffer)
{
	free(stash);
	free(buffer);
	return (NULL);
}

char	*read_from_file(int fd, char *stash)
{
	char	*buffer;
	int		read_size;

	read_size = BUFFER_SIZE;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	*buffer = 0;
	while (read_size != 0 && !ft_strchr(buffer, '\n'))
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			return (free_data(stash, buffer));
		buffer[read_size] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	if (read_size == -1 || *stash == '\0')
		return (free_data(stash, buffer));
	free(buffer);
	return (stash);
}

char	*leftovers(char *stash)
{
	char	*leftover;

	leftover = ft_strndup(stash + ft_strclen(stash, '\n') + 1,
			ft_strclen(stash, '\0') - ft_strclen(stash, '\n'));
	free (stash);
	if (!leftover)
		return (NULL);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*new_line;
	char		*tmp;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE));
	if (!tmp)
		return (NULL);
	if (!stash)
		if (read(fd, tmp, BUFFER_SIZE < 1))
			return (free(tmp), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	free(tmp);
	if (!stash)
		stash = NULL;
	stash = read_from_file(fd, stash);
	if (!stash)
		return (NULL);
	new_line = ft_strndup(stash, ft_strclen(stash, '\n'));
	if (!new_line)
		return (NULL);
	stash = leftovers(stash);
	if (!stash)
		free(stash);
	return (new_line);
}
