/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:16:15 by aalatzas          #+#    #+#             */
/*   Updated: 2023/11/01 22:38:51 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*greateline(int fd, char *everline)
{
	int		i;
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;

	while (1)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
			return (NULL);
		if (i > 0)
		{
			buffer[i] = '\0';
			temp = everline;
			everline = ft_strjoin(temp, buffer);
			if (temp)
				free (temp);
			if (!everline)
				return (NULL);
		}
		if (i == 0 || ft_strchr(buffer, '\n') != NULL)
			break ;
	}
	return (everline);
}

char	*cutline(char *everline, char *newline)
{
	int	i;
	int	o;

	o = 0;
	i = 0;
	while (everline[i] != '\0' && everline[i] != '\n')
		i++;
	if (everline[i] == '\n')
		i++;
	newline = malloc(i + 1 * sizeof(char));
	if (!newline)
		return (NULL);
	while (o < i && everline[o] != '\0')
	{
		newline[o] = everline[o];
		o++;
	}
	newline[o] = '\0';
	return (newline);
}

char	*updateeverline(char *everline)
{
	char	*newline_position;

	newline_position = ft_strchr(everline, '\n');
	if (newline_position)
		ft_memmove (everline, newline_position + 1, \
		ft_strlen(newline_position + 1) + 1);
	else
		everline[0] = '\0';
	if (everline && (!(*everline) && everline[0] != '\n'))
	{
		free(everline);
		everline = NULL;
	}
	return (everline);
}

char	*get_next_line(int fd)
{
	static char	*everline[1024];
	char		*newline;

	newline = NULL;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		free (everline[fd]);
		everline[fd] = NULL;
		return (NULL);
	}
	everline[fd] = greateline(fd, everline[fd]);
	if (!everline[fd])
		return (NULL);
	newline = cutline(everline[fd], newline);
	if (!newline)
	{
		free(everline[fd]);
		everline[fd] = NULL;
		return (NULL);
	}
	everline[fd] = updateeverline(everline[fd]);
	return (newline);
}
