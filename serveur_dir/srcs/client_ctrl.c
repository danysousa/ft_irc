/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 16:23:33 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/23 16:10:34 by dsousa           ###   ########.fr       */
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

static void	init_client(t_server *server, int actual, char *name, int csock)
{
	int		i;

	i = 0;
	server->clients[actual].name = ft_strdup(name);
	server->clients[actual].sock = csock;
	server->clients[actual].nb_channel = 0;
	while (i < MAX_CHANNEL)
	{
		server->clients[actual].channel[i] = NULL;
		i++;
	}
}

int			new_client(t_server *server, int *actual, char *buff)
{
	int				csock;
	t_sockaddr_in	csin;
	socklen_t		sinsize;

	sinsize = sizeof(csin);
	csock = accept(server->sock, (t_sockaddr *)&csin, &sinsize);
	if (csock == SOCKET_ERROR)
	{
		error("accept");
		return (-1);
	}
	if (read_client(csock, buff) == -1 || *(unsigned int *)buff == 0)
		return (-1);
	while (check_pseudo(buff, server) == -1)
	{
		write_client(csock, "Pseudo already used");
		if (read_client(csock, buff) == -1)
			return (-1);
	}
	FD_SET(csock, &(server->rdfs));
	server->max = csock > server->max ? csock : server->max;
	init_client(server, *actual, buff, csock);
	(*actual)++;
	return (csock);
}
