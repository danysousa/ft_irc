/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 15:51:39 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/23 15:55:56 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "../includes/serveur.h"

static void		remove_client(t_server *serv, int rm, int *actual)
{
	t_client	*clt;

	clt = serv->clients;
	ft_memmove(clt + rm, clt + rm + 1, (*actual - rm - 1) * sizeof(t_client));
	(*actual)--;
}

static void		msg_serv(t_server *server, int *actual, char *buff, int i)
{
	t_msg		msg;
	t_client	client;

	client = server->clients[i];
	close(server->clients[i].sock);
	remove_client(server, i, actual);
	ft_strncpy(buff, client.name, NAME_LEN);
	ft_strncat(buff, " disconnected !", BUF_SIZE - ft_strlen(buff));
	msg.clients = server->clients;
	msg.sender = client;
	msg_all(msg, *actual, buff, 1);
	ft_bzero(client.name, NAME_LEN);
}

void			client_talking(t_server *server, int *actual, char *buff)
{
	int			i;
	t_msg		msg;

	i = 0;
	while (i < *actual)
	{
		if (FD_ISSET(server->clients[i].sock, &(server->rdfs)))
		{
			if (read_client(server->clients[i].sock, buff) == 0)
				msg_serv(server, actual, buff, i);
			else if (buff[0] == '/')
				write_client(server->clients[i].sock, CHOOSE_CMD);
			else
			{
				msg.clients = server->clients;
				msg.sender = server->clients[i];
				msg_all(msg, *actual, buff, 0);
			}
			break ;
		}
		i++;
	}
}
