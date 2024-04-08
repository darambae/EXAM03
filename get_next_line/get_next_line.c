/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:31:54 by dabae             #+#    #+#             */
/*   Updated: 2024/04/08 18:35:47 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // For read
#include <stdlib.h> // For malloc && free

#define BUFFER_SIZE 8192

char	*get_next_line(int fd)
{
	int		i;
	int		bytes;
	char	*buffer;
	char	character;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	i = 0;
	bytes = read(fd, &character, 1);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (bytes > 0)
	{
		buffer[i++] = character;
		if (character == '\n')
			break ;
		bytes = read(fd, &character, 1);
	}
	if ((bytes <= 0) && (i == 0))
		return (free(buffer), NULL);
	buffer[i] = '\0';
	return (buffer);
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
    int	fd;
    char	*line;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error\n");
        return (1);
    }
    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s\n", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}