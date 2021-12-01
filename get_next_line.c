#include "get_next_line.h"
#include <string.h>

char	*free_all(char *prmn)
{
	free(prmn);
	return (NULL);
}

static char	*write_line(char *stat)
{
	int		i;
	char	*stroka;

	i = 0;
	while (stat && ft_strchr(stat, '\n') != 0)
		i++;
	stroka = (char *)malloc(sizeof(char) * (i + 2));
	if (!stroka)
		return (NULL);
	ft_strlcpy(stroka, stat, i + 2);
	if (stroka[0] == '\0')
		free_all(stroka);
	return (stroka);
}

static char	*new_stat(char *stat)
{
	char	*newstat;
	int		i;
	size_t	n;

	i = 0;
	n = 0;
	while (stat && stat[i] != '\n')
		i++;
	if (stat[i] == '\0')
		free_all(stat);
	newstat = (char *)malloc(sizeof(char) * (ft_strlen(stat) - i + 1));
	if (!newstat)
		return (NULL);
	ft_strlcpy(newstat, stat + i + 1, ft_strlen(stat) - i + 1);
	free(stat);
	return (newstat);
}

static char	*make_stat(char *stat, char *buff, int fd)
{
	int		bwr;
	char	*vrmn;

	bwr = 1;
	while (ft_strchr(buff, '\n') != 0 && buff)
	{
		bwr = read(fd, buff, BUFFER_SIZE);
		if (bwr == -1)
			free_all(buff);
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
	char		*newline;
	char		*buff;
	static char	*stat;	

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	newline = NULL;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!buff)
		free_all(buff);
	stat = make_stat(stat, buff, fd);
	if(!stat)
		return (NULL);
	newline = write_line(stat);
	stat = new_stat(stat);
	return (newline);
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