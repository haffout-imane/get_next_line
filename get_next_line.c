/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:55:39 by ihaffout          #+#    #+#             */
/*   Updated: 2024/02/26 18:49:45 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_before_the_new_line(char *str)
{
	int		len;
	char	*line;

	len = 0;
	line = NULL;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		line = malloc(len + 2);
	else
		line = malloc(len + 1);
	if (!line)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
	{
		line[len] = str[len];
		len++;
	}
	if (str[len] == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

char	*ft_after_the_new_line(char *str)
{
	int		i;
	int		len;
	char	*rest;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (!str[len])
	{
		free(str);
		return (NULL);
	}
	rest = malloc(ft_strlen(str) - len);
	if (!rest)
	{
		free(str);
		return (NULL);
	}
	len++;
	while (str[len])
		rest[i++] = str[len++];
	rest[i] = '\0';
	free(str);
	return (rest);
}

char	*ft_string(int fd, char *str)
{
	char	*buffer;
	int		byte;
	char	*tmp;

	byte = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(str));
	ft_bzero(buffer, BUFFER_SIZE + 1);
	while (byte > 0 && !ft_strchr(buffer, '\n'))
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte < 0)
			return (ft_free(str));
		if (byte == 0)
			break ;
		buffer[byte] = '\0';
		tmp = ft_strjoin(str, buffer);
		free(str);
		if (!tmp)
			return (ft_free(buffer));
		str = tmp;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		str = ft_free(str);
		return (NULL);
	}
	str = ft_string(fd, str);
	if (!str)
		return (NULL);
	line = ft_before_the_new_line(str);
	if (!line || !*line)
	{
		free(line);
		free(str);
		str = NULL;
		return (NULL);
	}
	str = ft_after_the_new_line(str);
	return (line);
}
