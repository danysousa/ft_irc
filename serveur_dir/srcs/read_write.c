/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 15:29:03 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/24 16:01:36 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "../includes/serveur.h"

int		read_client(int sock, char *buff)
{
	int n;

	n = 0;
	if ((n = recv(sock, buff, BUF_SIZE, 0)) < 0)
	{
		error("recv");
		n = 0;
	}
	buff[n - 1] = 0;
	return (n);
}

void	write_client(int sock, const char *buff)
{
	if (send(sock, buff, ft_strlen((char *)buff), 0) < 0)
		exit_error("send");
}

void	msg_all(t_msg msg, int actual, char *buffer, int serv_msg)
{
	int		i;
	char	*message;

	i = 0;
	if (!serv_msg)
	{
		message = ft_strjoin(msg.sender.name, " : ");
		message = ft_strjoin(message, buffer);
	}
	else
		message = ft_strdup(buffer);
	while (i < actual)
	{
		if (msg.sender.sock != msg.clients[i].sock
			&& check_channel(msg.sender, msg.clients[i]))
			write_client(msg.clients[i].sock, message);
		i++;
	}
	free(message);
}
