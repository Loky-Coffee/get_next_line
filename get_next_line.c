/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 05:00:30 by aalatzas          #+#    #+#             */
/*   Updated: 2023/10/31 17:23:59 by aalatzas         ###   ########.fr       */
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
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;

	while (1)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
			return (NULL);
		buffer[i] = '\0';
		if (i <= 0)
		{
			if (i <= 0)
				return (ft_strjoin(everline, buffer));
			return (NULL);
		}
		if (i > 0)
		{
			temp = everline;
			everline = ft_strjoin(temp, buffer);
			free (temp);
		}
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
	while (everline[i] != '\0' && everline[i] != '\n') // Added check for a new line character
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
		return (NULL);
	newline = cutline(everline, newline);
	everline = updateeverline(everline);
	return (newline);
}

// int main(void)
// {
// 	int	fd = 0;
// 	char *line;

// 	fd = open("text.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("\nThe Line ------->:%s", line);
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		printf("\nThe Line ------->:%s", line);
// 		free (line);
// 	}
// 	close(fd);
// 	free(line);
// 	system("leaks a.out");
// 	return 0;
// }