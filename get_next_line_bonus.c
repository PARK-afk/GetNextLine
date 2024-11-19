/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:17:07 by junsepar          #+#    #+#             */
/*   Updated: 2023/02/23 18:25:53 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*backup[256];

	if (fd == -1 || BUFFER_SIZE < 1 || 255 < fd)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = read_line(fd, buf, backup[fd], 1);
	free (buf);
	buf = NULL;
	if (line == NULL || *line == '\0')
	{
		free (backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	backup[fd] = need_backup(line);
	return (line);
}

char	*read_line(int fd, char *buf, char *backup, int n)
{
	char	*tmp;

	while (n)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
			return (NULL);
		if (n == 0)
			break ;
		buf[n] = '\0';
		if (backup == NULL)
			backup = ft_strdup("");
		tmp = backup;
		backup = ft_strjoin(tmp, buf);
		free (tmp);
		tmp = NULL;
		if (backup == NULL)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

char	*need_backup(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	tmp = ft_strdup(line + i + 1);
	if (tmp == NULL)
		return (NULL);
	line[i + 1] = '\0';
	return (tmp);
}
