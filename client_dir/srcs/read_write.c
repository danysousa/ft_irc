/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 14:08:18 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/24 15:56:14 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/client.h"

int			read_server(int sock, char *buffer)
{
	int		r;

	r = 0;
	if ((r = recv(sock, buffer, BUF_SIZE, 0)) < 0)
		exit_error("recv");
	buffer[r] = 0;
	return (r);
}

void		write_server(int sock, const char *buffer)
{
	char	*msg;

	msg = ft_strjoin(buffer, "\n");
	if (send(sock, msg, ft_strlen(msg), 0) < 0)
		exit_error("send");
	free(msg);
}

void		read_msg(char *buff)
{
	char	*p;

	read(0, buff, BUF_SIZE);
	if ((p = ft_strstr(buff, "\n")) != NULL)
		*p = 0;
	else
		buff[BUF_SIZE] = 0;
}

int			chk_char_name(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isprint(line[i]) && line[i] != ' ')
			i++;
		else
			return (0);
	}
	return (1);
}
