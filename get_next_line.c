/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 05:00:30 by aalatzas          #+#    #+#             */
/*   Updated: 2023/10/31 11:33:22 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	*buffer;

	while (1)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!buffer)
			return (NULL);
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			free (buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		if ((i <= 0) || (ft_strchr(buffer, '\0') == NULL))
		{
			if ((i <= 0))
				return (ft_strjoin(everline, buffer));
			free(buffer);
			return (0);
		}
		if (i > 0)
			everline = ft_strjoin(everline, buffer);
		if (i <= 0 || ft_strchr(buffer, '\n') != NULL)
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
	while (everline[i] != '\0')
		i++;
	newline = malloc(i + 1 * sizeof(char));
	if (!newline)
		return (NULL);
	while (o < i && everline != NULL)
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
	return (everline);
}

char	*get_next_line(int fd)
{
	static char	*everline;
	char		*newline;

	newline = NULL;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (everline)
		{
			free (everline);
			everline = NULL;
		}
		return (NULL);
	}

	everline = greateline(fd, everline);
	if (!everline)
		exit(0);
	newline = cutline(everline, newline);
	everline = updateeverline(everline);
	return (newline);
}

// int main(void)
// {
// 	static int fd = -1;
// 	char *line;

// 	if (fd == -1)
// 	{
// 		fd = open("text.txt", O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror("Error opening the file");
// 			return 1;
// 		}
// 	}
// 	line = get_next_line(fd);
// 	printf("\nThe Line ------>: %s\n", line);
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		printf("\nThe Line ------->: %s\n", line);
// 	}
// 	if (line == NULL)
// 	{
// 		close(fd);
// 		fd = -1;
// 		return 0;
// 	}
// 	free(line);
// 	return 0;
// }
