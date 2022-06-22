/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaslan <aaslan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:14:24 by aaslan            #+#    #+#             */
/*   Updated: 2022/06/22 23:27:12 by aaslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	void *dest_address;

	dest_address = dest;
	if (dest == src || n == 0)
		return (dest);
	while (0 < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		dest++;
		src++;
		n--;
	}
	return (dest_address);
}

size_t ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t src_length;

	src_length = ft_strlen(src);
	while (*src != '\0' && 1 < n)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	if (n != 0)
		*dest = '\0';
	return (src_length);
}

char *ft_strjoin(char *s1, char *s2)
{
	size_t s1_length;
	size_t s2_length;
	char *string;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof(char));
		*s1 = '\0';
	}
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	string = (char *)malloc((s1_length + s2_length + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	ft_memcpy(string, s1, s1_length);
	ft_strlcpy(string + s1_length, s2, s2_length + 1);

	return (string);
}

char *ft_get_line(char *str)
{
	char *line;
	int line_len;

	line_len = 0;
	while (str[line_len] != '\n')
		line_len++;
	line = (char *)malloc(sizeof(char) * (line_len + 2));
	line_len = 0;
	while (str[line_len] != '\n')
	{
		line[line_len] = str[line_len];
		line_len++;
	}
	line[line_len] = '\n';
	line[line_len + 1] = '\0';
	return (line);
}

char *ft_strdup(const char *s)
{
	char *copy_string;
	size_t s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	copy_string = (char *)malloc(s_len + 1);
	if (copy_string == NULL)
		return (NULL);
	ft_strlcpy(copy_string, s, s_len + 1);
	return (copy_string);
}

char *get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	static char *buffer;
	char *line = NULL;
	char *trash = NULL;

	int readed_byte = -1;

	char *temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));

	while (ft_strchr(temp, '\n') == NULL && readed_byte != 0)
	{
		readed_byte = read(fd, temp, BUFFER_SIZE);
		if (readed_byte == -1)
			return (NULL);
		buffer = ft_strjoin(buffer, temp);
	}
	free(temp);
	trash = buffer;
	line = ft_get_line(trash);
	buffer = ft_strdup(trash + ft_strlen(line));
	free(trash);
	return (line);
}

int main()
{
	int file_descriptor = open("note.txt", O_RDONLY);

	for (size_t i = 0; i < 4; i++)
	{
		printf("%s", get_next_line(file_descriptor));
	}

	close(file_descriptor);

	return (0);
}
