#include "get_next_line.h"

// char	*write_line(char *new_line, char )
// {
	// new_line = strjoin(new_line, vrmn);
	// return (new_line);
// }

char	*get_next_line(int fd)
{
	static char	*new_line;
	char	*vrmn;
	int			bwr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	vrmn = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!vrmn)
		return (NULL);
	while (!(ft_strchr(vrmn, '\n')) && vrmn)
	{
		bwr = read(fd, vrmn, BUFFER_SIZE);
		vrmn[bwr] = '\0';
		new_line = ft_strjoin(new_line, vrmn);
		vrmn = NULL;
	}
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