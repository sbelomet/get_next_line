/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:12:12 by sbelomet          #+#    #+#             */
/*   Updated: 2023/10/25 15:41:14 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			nbchars;
	
	if (fd < 0)
		return (NULL);
//	printf("start\n");
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
//	printf("buffer: %s\n", buffer);
//	printf("stash: %s\n", stash);
	nbchars = BUFFER_SIZE;
	while ((ft_strchr(stash, '\n') == -1) && nbchars == BUFFER_SIZE)
	{
//		printf("in loop\n");
		nbchars = read(fd, buffer, BUFFER_SIZE);
//		printf("nbchars: %d\n", nbchars);
		stash = ft_strjoin(stash, buffer);
		if ((*stash == '\0') || (!stash))
		{
			free(stash);
			return (NULL);
		}
//		printf("stash content: %s\n", stash);
	}
	free(buffer);
	if (*stash == '\0')
	{
		free(stash);
		return (NULL);
	}

	char	*res;
	int		lentolb;

	lentolb = 0;
	while (stash[lentolb] != '\n' && stash[lentolb])
		lentolb++;
	res = ft_substr(stash, 0, (size_t)lentolb + 1);
	if (!res)
		return (NULL);
	stash = ft_substr(stash, ft_strchr(stash, '\n') + 1, (size_t)(ft_strlen(stash) - lentolb));
	return (res);
}
/*
int	main(void)
{
	int	fd;
	char	*res;
	int		i = 1;

	fd = open("test.txt", O_RDONLY);
	while (i < 10)
	{
		res = get_next_line(fd);
		if (res)
			printf("%d: |%s|\n", i, res);
		i++;
	}
}*/
