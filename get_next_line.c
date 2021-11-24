#include "get_next_line.h"

char	*write_line(char *vrmn)
{
	int		i;
	char	*stroka;

	i = 0;
	stroka = (char *)malloc(sizeof(char) * (ft_strlen(vrmn) + 2));
	while (stroka && *vrmn != '\n')
	{
		stroka[i] = *vrmn;
		i++;
		vrmn++;
	}
	stroka[i] = '\0';
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
		buff[bwr] = '\0';
		vrmn = ft_strjoin(vrmn, buff);
		if (!vrmn)
			return (NULL);
		free(buff);
	}
	new_line = write_line(vrmn);
	return (new_line);
}

#include <fcntl.h>
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


// сначала читаем по размеру буффера, переносим все в статическую переменную vrmn, из нее в с помощью strjoin копируем все в конец  new_line и очищаем vrmn
// это все в цикле пока не дойдем до \n, затем пишем \n в строку(по сабджекту), возвращаем ее и переходим на новую