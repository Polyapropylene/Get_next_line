#include "get_next_line.h"

char	*write_line(char *vrmn)
{
	int		i;
	int		n;
	char	*stroka;

	i = 0;
	n = 0;
	while (vrmn && ft_strchr(vrmn, '\n') != 0)
		i++;
	stroka = (char *)malloc(sizeof(char) * (i + 2));
	if (!stroka)
		return (NULL);
	while (stroka && *vrmn != '\n' && n <= i)
	{
		stroka[n] = *vrmn;
		n++;
		vrmn++;
	}
	stroka[n] = '\0';
	stroka[n + 1] = '\n';
	return (stroka);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*buff;
	char		*vrmn;
	int			bwr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	vrmn = NULL;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!buff)
		return (NULL);
	while (!(ft_strchr(buff, '\n')) && buff)
	{
		bwr = read(fd, buff, BUFFER_SIZE);
		if (bwr == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bwr] = '\0';
		vrmn = ft_strjoin(vrmn, buff);
		if (!vrmn)
			return (NULL);
	}
	free(buff);
	new_line = write_line(vrmn);
	return (new_line);
}

#include <fcntl.h>
#include <stdio.h>

/*int	main ()
{
	int		fd;
	char	*new_line;

	fd = open("text.txt", O_RDONLY);
	new_line = get_next_line(fd);
	printf("%s\n", new_line);
	return (0);
}
*/