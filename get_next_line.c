/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 05:00:30 by aalatzas          #+#    #+#             */
/*   Updated: 2023/10/31 01:28:18 by aalatzas         ###   ########.fr       */
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
	int	i;

	i = 1;
	everline = malloc(BUFFER_SIZE + 1);
	while (i)
	{
		if (ft_strchr(everline, '\n') != NULL)
			break ;
		i = read(fd, everline, BUFFER_SIZE);
		everline[i] = '\0';
		if (i <= 0)
			break ;
	}
	return (everline);
}

char	*cutline(char *everline, char *newline)
{
	int	i;
	int	j;
	int	o;

	o = 0;
	i = 0;
	while (everline[i] != '\n')
		i++;
	j = i;
	newline = malloc(i + 1 * sizeof(char));
	while (i > 0)
	{
		newline[o] = everline[o];
		o++;
		i--;
	}
	newline[ft_strlen(newline) + 1] = '\0';
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
	printf("\neverline IST 2: \n%s", everline);
	return (everline);
}

char	*get_next_line(int fd)
{
	static char	*everline;
	char		*newline;

	if (fd < 0 || read(fd, 0, 0))
		return (0);
	everline = greateline(fd, everline);
	newline = cutline(everline, newline);
	everline = updateeverline(everline);
	return (newline);
}

// int main(void)
// {
// 	char *a;

// 	int i;
// 	i = open("text.txt", O_RDONLY);
// 	a = get_next_line(i);
// 	printf("The Line: \n%s", a);
// 	close(i);
// 	return (0);
// }
