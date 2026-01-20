/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:58:37 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/04 15:56:30 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*delete_line(char *stash)
{
	char	*str;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	if (stash[i + 1] == '\0')
		return (free(stash), NULL);
	str = ft_strdup(&stash[i + 1]);
	if (!str)
		return (free(stash), NULL);
	return (free(stash), str);
}

char	*put_line(char *stash)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	if (!str)
		return (NULL);
	i += 1;
	while (i--)
		str[i] = stash[i];
	return (str);
}

char	*stash_extend(char *stash, char *buffer, size_t size)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	if (!temp)
		return (free(stash), NULL);
	free(stash);
	while (size--)
		buffer[size] = '\0';
	return (temp);
}

char	*read_fd(char *stash, int fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (stash[0] == '\0' || bytes_read == -1)
				return (free(stash), free(buffer), NULL);
			return (free(buffer), stash);
		}
		stash = stash_extend(stash, buffer, BUFFER_SIZE);
		if (ft_strchr(stash, '\n') != NULL)
		{
			free(buffer);
			break ;
		}
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[1024];

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	if (!stash[fd])
	{
		stash[fd] = ft_calloc(1, sizeof(char));
		if (!stash[fd])
			return (NULL);
	}
	if (!ft_strchr(stash[fd], '\n'))
		stash[fd] = read_fd(stash[fd], fd);
	if (!stash[fd] || stash[fd][0] == '\0')
		return (free(stash[fd]), NULL);
	line = put_line(stash[fd]);
	if (!line)
		return (free(stash[fd]), NULL);
	stash[fd] = delete_line(stash[fd]);
	return (line);
}
