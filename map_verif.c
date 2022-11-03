#include "so_long.h"

int ft_checkmap(int fd)
{
	char	*line;
	int		i;
	int		error;
	int		len;
	int		ln_number;

	i = 0;
	error = 0;
	line = get_next_line(fd);
	while (line[i] != '\n')
	{
		if (line[i] != '1')
			error = 1;
		i++;
	}
	ln_number++;
	printf("%s", line);
	len = (ft_strlen(line) - 1);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\n')
			break ;
		i = 0;
		while (line[i] != '\n')
		{	
			if (line[0] != '1' || line[len - 1] != '1')
			{
				error = 1;
			}
			i++;
		}
		printf("%s", line);
	}:
	while (line != NULL)
	{
		line = get_next_line(fd);

	}
	
	printf("%d\n", error);
	if (error == 1)
		printf("%s", "ERROR");
	
	return (0);
}

int main(void)
{
	int fd;
	fd = open("includes/map/map.ber", O_RDONLY);
	if (fd < 0)
	{
		printf("%s", "test");
	}
	
	ft_checkmap(fd);
}