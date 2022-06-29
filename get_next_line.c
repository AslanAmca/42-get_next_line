/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaslan <aaslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:19:59 by aaslan            #+#    #+#             */
/*   Updated: 2022/06/29 14:11:10 by aaslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 1
// # endif

// #include <unistd.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <stdio.h>

// int	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (*s != '\0')
// 	{
// 		i++;
// 		s++;
// 	}
// 	return (i);
// }

// int	ft_has_line_feed(char *line)
// {
// 	while (*line != '\0')
// 	{
// 		if (*line == '\n')
// 			return (1);
// 		line++;
// 	}
// 	return (0);
// }

// char	*ft_create_empty_string(int size)
// {
// 	char	*string;

// 	string = (char *)malloc(sizeof(char) * size);
// 	if (string != NULL)
// 		*string = '\0';
// 	return (string);
// }

// char	*ft_add_buffer_to_string(char *string, char *buffer)
// {
// 	char	*new_str;
// 	int		len;
// 	int		i;

// 	if (string == NULL)
// 		string = ft_create_empty_string(1);
// 	len = ft_strlen(string) + ft_strlen(buffer);
// 	new_str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (new_str == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (string[i] != '\0')
// 	{
// 		new_str[i] = string[i];
// 		i++;
// 	}
// 	while (*buffer != '\0')
// 	{
// 		new_str[i] = *buffer;
// 		i++;
// 		buffer++;
// 	}
// 	new_str[i] = '\0';
// 	free(string);
// 	return (new_str);
// }

#include "get_next_line.h"

char	*ft_fill_string(char *string, int fd)
{
	char	*buffer;
	int		readed_byte;

	buffer = ft_create_empty_string(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	readed_byte = 61;
	while (readed_byte != 0 && ft_has_line_feed(buffer) == 0)
	{
		readed_byte = read(fd, buffer, BUFFER_SIZE);
		if (readed_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[readed_byte] = '\0';
		string = ft_add_buffer_to_string(string, buffer);
	}
	free(buffer);
	return (string);
}

char	*ft_get_first_line(char *string)
{
	char	*line;
	int		len;

	len = 0;
	while (string[len] != '\0' && string[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (line == NULL)
		return (NULL);
	len = 0;
	while (string[len] != '\0' && string[len] != '\n')
	{
		line[len] = string[len];
		len++;
	}
	if (string[len] == '\n')
	{
		line[len] = string[len];
		len++;
	}
	line[len] = '\0';
	return (line);
}

char	*ft_delete_first_line(char *string)
{
	char	*new_str;
	int		line_len;
	int		i;

	line_len = 0;
	while (string[line_len] != '\0' && string[line_len] != '\n')
		line_len++;
	if (string[line_len] == '\0')
	{
		free(string);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(string) - line_len + 1));
	if (new_str == NULL)
		return (NULL);
	line_len++;
	i = 0;
	while (string[line_len] != '\0')
		new_str[i++] = string[line_len++];
	new_str[i] = '\0';
	free(string);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*string;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	string = ft_fill_string(string, fd);
	if (string == NULL)
		return (NULL);
	if (*string == '\0')
	{
		free(string);
		string = NULL;
		return (NULL);
	}
	line = ft_get_first_line(string);
	string = ft_delete_first_line(string);
	return (line);
}

// int main()
// {
// 	int fd = open("empty", O_RDONLY);
// 	printf("%s",get_next_line(fd));
// 	return 0;
// }
