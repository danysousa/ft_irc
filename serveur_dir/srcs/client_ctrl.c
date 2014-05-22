/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 16:23:33 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/22 14:44:41 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "../includes/serveur.h"

void		clear_clients(t_client *clients, int actual)
{
	int		i;

	i = 0;
	while (i < actual)
	{
		close(clients[i].sock);
		i++;
	}
}

int			new_client(t_server *server, int *actual, char *buff)
{
	int				csock;
	t_sockaddr_in	csin;
	socklen_t		sinsize;

	sinsize = sizeof csin;
	csock = accept(server->sock, (t_sockaddr *)&csin, &sinsize);
	if(csock == SOCKET_ERROR)
	{
		error("accept");
		return (-1);
	}
	if (read_client(csock, buff) == -1)
		return (-1);
	while (check_pseudo(buff, server) == -1)
	{
		write_client(csock, "Pseudo already used");
		if (read_client(csock, buff) == -1)
			return (-1);
	}
	FD_SET(csock, &(server->rdfs));
	server->max = csock > server->max ? csock : server->max;
	server->clients[*actual].name = ft_strdup(buff);
	server->clients[*actual].sock = csock;
	(*actual)++;
	return (csock);
}

static void	remove_client(t_server *serv, int rm, int actual)
{
	t_client	*clt;
	int			i;
	int			newmax;
	int			save;

	clt = serv->clients;
	ft_memmove(clt + rm, clt + rm + 1, (actual - rm - 1) * sizeof(t_client));
	actual--;
	i = 0;
	if ((clt + rm)->sock == serv->max)
	{
		save = serv->max;
		serv->max = serv->sock;
		while (i < actual)
		{
			newmax = serv->clients[i].sock;
			serv->max = newmax > serv->max ? newmax : serv->max;
			i++;
		}
	}
}

void		client_talking(t_server *server, int *actual, char *buff)
{
	int			i;
	t_client	*client;
	char		*tmp;

	i = 0;
	while (i < *actual)
	{
		if (FD_ISSET(server->clients[i].sock, &(server->rdfs)))
		{
			client = &(server->clients[i]);
			if (read_client(server->clients[i].sock, buff) == 0)
			{
				close(server->clients[i].sock);
				remove_client(server, i, *actual);
				(*actual)--;
				ft_strncpy(buff, client->name, NAME_LEN);
				ft_strncat(buff, " disconnected !", BUF_SIZE - ft_strlen(buff));
				send_message_to_all_clients(server->clients, *client, *actual, buff, 1);
				ft_bzero(client->name, NAME_LEN);
			}
			else if (buff[0] == '/')
			{
				if ((tmp = cmd(buff, client, server)))
					write_client(client->sock, tmp);
			}
			else
				send_message_to_all_clients(server->clients, *client, *actual, buff, 0);
			break;
		}
		i++;
	}
}
