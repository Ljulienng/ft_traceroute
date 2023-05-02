/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienngy <julienngy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:27:19 by jnguyen           #+#    #+#             */
/*   Updated: 2020/02/02 22:23:28 by julienngy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

static int			ft_strchr_gnl(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

static char			*ft_strnjoin_gnl(char const *s1, char const *s2, unsigned int n)
{
	int				i;
	int				j;
	int				size;
	char			*dest;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		size = 0;
	else
		size = ft_strlen(s1) + ft_strlen(s2);
	if (!(dest = malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i] && n > 0)
	{
		dest[j++] = s2[i++];
		n--;
	}
	dest[j] = '\0';
	free((void*)s1);
	return (dest);
}

int					get_next_line(int fd, char **line)
{
	static char		buffer[4097];
	char			buffer_temp[1];
	int				ret;
	int				ret2;

	ret = 1;
	if (fd <= -1 || line == NULL || (read(fd, buffer_temp, 0) < 0))
		return (-1);
	*line = ft_strdup("");
	while (ret && (ret2 = ft_strchr_gnl(buffer, '\n')) == -1)
	{
		if (!(*line = ft_strnjoin_gnl(*line, buffer, 4096)))
			return (-1);
		if ((ret = read(fd, buffer, 4096)) == 0)
		{
			return (0);
		}
		buffer[ret] = 0;
	}
	if (!(*line = ft_strnjoin_gnl(*line, buffer, ret2)))
		return (-1);
	if (ret)
		ft_strcpy(buffer, &buffer[ret2 + 1]);
	return (1);
}
// int		gnl_return(char **str, char **line, int fd, int ret)
// {
// 	if (ret < 0)
// 		return (-1);
// 	else if (ret == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
// 	{
// 		*line = ft_strnew(0);
// 		return (0);
// 	}
// 	return (get_new_line(str, line, fd, ret));
// }

// int		get_new_line(char **str, char **line, int fd, int ret)
// {
// 	char	*cur;
// 	int		len;

// 	len = 0;
// 	while (str[fd][len] != '\0' && str[fd][len] != '\n')
// 		len++;
// 	if (str[fd][len] == '\n')
// 	{
// 		*line = ft_substr(str[fd], 0, len);
// 		cur = ft_strdup(len + 1 + str[fd]);
// 		ft_strdel(&str[fd]);
// 		str[fd] = cur;
// 		if (*str[fd] == '\0')
// 			ft_strdel(&str[fd]);
// 	}
// 	else if (str[fd][len] == '\0')
// 	{
// 		if (ret == BUFFER_SIZE)
// 			return (get_next_line(fd, line));
// 		*line = ft_strdup(str[fd]);
// 		ft_strdel(&str[fd]);
// 		return (0);
// 	}
// 	return (1);
// }

// int		get_next_line(int fd, char **line)
// {
// 	static char		*str[1024];
// 	char			buff[BUFFER_SIZE + 1];
// 	char			*tmp;
// 	int				ret;

// 	if (!line || fd < 0 || BUFFER_SIZE == 0)
// 		return (-1);
// 	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
// 	{
// 		buff[ret] = '\0';
// 		tmp = str[fd];
// 		if (!(str[fd] = ft_strjoin(str[fd], buff)))
// 			str[fd] = ft_strnew(0);
// 		ft_strdel(&tmp);
// 		if (ft_strchr(buff, '\n'))
// 			break ;
// 	}
// 	return (gnl_return(str, line, fd, ret));
// }
