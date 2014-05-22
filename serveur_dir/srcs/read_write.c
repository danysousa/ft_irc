/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 15:29:03 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/22 12:10:47 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "../includes/serveur.h"

int		read_client(int sock, char *buff)
{
	int n = 0;

	if ((n = recv(sock, buff, BUF_SIZE, 0)) < 0)
	{
		error("recv");
		n = 0;
	}
	buff[n] = 0;
	return (n);
}

void	write_client(int sock, const char *buff)
{
	if (send(sock, buff, ft_strlen((char *)buff), 0) < 0)
		exit_error("send");
}

void	send_message_to_all_clients(t_client *clients, t_client sender, int actual, const char *buff, char from_server)
{
	int		i;
	char	message[BUF_SIZE + 1];

	message[0] = 0;
	i = 0;
	while (i < actual)
	{
		if (sender.sock != clients[i].sock)
		{
			if (from_server == 0)
			{
				ft_strncpy(message, sender.name, NAME_LEN);
				ft_strncat(message, " : ", sizeof message - ft_strlen(message) - 1);
			}
			ft_strncat(message, buff, sizeof message - ft_strlen(message) - 1);
			write_client(clients[i].sock, message);
		}
		i++;
	}
}
