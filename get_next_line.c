#include "get_next_line.h"
#include <string.h>

char	*write_line(char *stat)
{
	int		i;
	int		n;
	char	*stroka;

	i = 0;
	n = 0;
	while (stat && ft_strchr(stat, '\n') != 0)
		i++;
	stroka = (char *)malloc(sizeof(char) * (i + 2));
	if (!stroka)
		return (NULL);
	while (stroka && *stat != '\n' && n < (i + 1))
	{
		stroka[n] = stat[n];
		n++;
	}
	stroka[n] = '\0';
	if (stroka[0] == '\0')
	{
		free(stroka);
		return (NULL);
	}
	return (stroka);
}

char	*make_stat(char *stat, char *buff, int fd)
{
	int	bwr;
	char	*vrmn;
	while (!(ft_strchr(buff, '\n')) && buff)
	{
		bwr = read(fd, buff, BUFFER_SIZE);
		if (bwr == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bwr] = '\0';
		if (!stat)
			stat = ft_strdup("");
		vrmn = stat;
		stat = ft_strjoin(vrmn, buff);
		free(vrmn);
	}
	free(buff);
	return (stat);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	char		*buff;
	static char	*stat;	

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stat = NULL;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!buff)
		return (NULL);
	stat = make_stat(stat, buff, fd);
	if(!stat)
		return (NULL);
	new_line = write_line(stat);
	return (new_line);
}

/*#include <fcntl.h>
#include <stdio.h>

int	main ()
{
	int		fd;
	char	*new_line;

	fd = open("text.txt", O_RDONLY);
	new_line = get_next_line(fd);
	printf("%s\n", new_line);
	return (0);
}
*/