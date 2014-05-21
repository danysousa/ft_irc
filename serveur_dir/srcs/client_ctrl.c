/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 16:23:33 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/21 17:57:00 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_client c;
	c.sock = csock;
	ft_strncpy(c.name, buff, NAME_LEN);
	server->clients[*actual] = c;
	(*actual)++;
	return (csock);
}

static void	remove_client(t_client *clients, int to_remove, int *actual)
{
	ft_memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(t_client));
	(*actual)--;
}

void		client_talking(t_server *server, int actual, char *buff)
{
	int		i;

	i = 0;
	while (i < actual)
	{
		if (FD_ISSET(server->clients[i].sock, &(server->rdfs)))
		{
			t_client client = server->clients[i];
			if (read_client(server->clients[i].sock, buff) == 0)
			{
				close(server->clients[i].sock);
				remove_client(server->clients, i, &actual);
				ft_strncpy(buff, client.name, NAME_LEN);
				ft_strncat(buff, " disconnected !", BUF_SIZE - ft_strlen(buff));
				send_message_to_all_clients(server->clients, client, actual, buff, 1);
			}
			else
				send_message_to_all_clients(server->clients, client, actual, buff, 0);
			break;
		}
		i++;
	}
}
