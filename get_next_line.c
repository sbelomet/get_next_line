/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:12:12 by sbelomet          #+#    #+#             */
/*   Updated: 2023/10/26 09:56:37 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		*(char *)s = '\0';
		s++;
		i++;
	}
}

void	*ft_calloc(int count, int size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

char	*read_to_break(char *stash, int fd)
{
	char	*buffer;
	int		nbchars;
	
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	nbchars = BUFFER_SIZE;
	while ((ft_strchr(buffer, '\n') == -1) && nbchars == BUFFER_SIZE)
	{
		nbchars = read(fd, buffer, BUFFER_SIZE);
		if (nbchars)
			stash = ft_strjoin(stash, buffer);
//		printf("stash: |%s|\n", stash);
		if ((!stash) || (*stash == '\0'))
		{
//			printf("not here right?\n");
			free(stash);
			free(buffer);
			return (NULL);
		}
//		printf("WHERE ARE YOU\n");
	}
//	printf("why\n");
	if (buffer)
		free(buffer);
//	printf("AAAAAAAAAAAAAAAAAA\n");
	return (stash);
}
char	*get_next_line(int fd)
{
	static char	*stash;
	char	*res;
	int		lentolb;

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE < 1)
		return (NULL);
	stash = read_to_break(stash, fd);
//	printf("MAYBEEEEE???\n");
	if ((!stash) || (*stash == '\0'))
	{
		free(stash);
		return (NULL);
	}
//	printf("HERE????\n");
	lentolb = 0;
	while (stash[lentolb] != '\n' && stash[lentolb])
		lentolb++;
	res = ft_substr(stash, 0, (size_t)lentolb + 1);
	if (!res)
		return (NULL);
	stash = ft_substr(stash, ft_strchr(stash, '\n') + 1, (size_t)(ft_strlen(stash) - lentolb));
	return (res);
}

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
}