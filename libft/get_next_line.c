/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:35:12 by lde-taey          #+#    #+#             */
/*   Updated: 2024/04/20 15:24:03 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line_to_stash(int fd, char *stash, char *buffer)
{
	ssize_t	bytesread;
	char	*temp;

	bytesread = 1;
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free (buffer);
			return (NULL);
		}
		else if (bytesread == 0)
			break ;
		buffer[bytesread] = '\0';
		temp = stash;
		if (temp == 0)
			temp = ft_strdup("");
		stash = ft_strjoin(temp, buffer);
		free (temp);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

char	*create_and_end_line(char *ext_stash)
{
	char		*newstash;
	ssize_t		i;

	i = 0;
	while (ext_stash[i] != '\0' && ext_stash[i] != '\n')
		i++;
	if (ext_stash[i] == '\0' || ext_stash[1] == '\0')
		return (NULL);
	newstash = ft_substr(ext_stash, i + 1, ft_strlen(ext_stash) - i - 1);
	if (!newstash)
		return (NULL);
	ext_stash[i + 1] = '\0';
	if (newstash[0] == '\0')
	{
		free(newstash);
		newstash = NULL;
	}
	return (newstash);
}

char	*get_next_line(int fd)
{
	static char		*stash = NULL;
	char			*line;
	char			*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = read_line_to_stash(fd, stash, buffer);
	if (!line || *line == '\0')
	{
		free (buffer);
		return (NULL);
	}
	free (buffer);
	stash = create_and_end_line(line);
	return (line);
}
