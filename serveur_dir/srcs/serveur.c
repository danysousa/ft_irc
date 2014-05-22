/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 16:48:18 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/22 14:45:12 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include "../includes/serveur.h"

static void		init_fds(t_server *server, int actual)
{
	int		i;

	i = 0;
	FD_ZERO(&(server->rdfs));
	FD_SET(STDIN_FILENO, &(server->rdfs));
	FD_SET(server->sock, &(server->rdfs));
	while (i < actual)
		FD_SET(server->clients[i++].sock, &(server->rdfs));
}

static void		init_server(t_server *server, int sock)
{
	int		i;

	i = 0;
	server->max = sock;
	server->sock = sock;
	while (i < MAX_CLIENTS)
	{
		server->clients[i].name = NULL;
		i++;
	}
}

static void		server(int sock)
{
	char			buff[BUF_SIZE + 1];
	int				actual;
	t_server		server;

	actual = 0;
	init_server(&server, sock);
	while (1)
	{
		init_fds(&server, actual);
		if (select(server.max + 1, &server.rdfs, NULL, NULL, NULL) == -1)
			exit_error("select");
		if (FD_ISSET(STDIN_FILENO, &server.rdfs))
			break ;
		else if (FD_ISSET(server.sock, &server.rdfs))
		{
			if (new_client(&server, &actual, buff) == -1)
				continue ;
		}
		else
			client_talking(&server, &actual, buff);
	}
	clear_clients(server.clients, actual);
	close(server.sock);
}

static int		init_connection(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	t_sockaddr_in sin;

	if (sock == INVALID_SOCKET)
		exit_error("socket");

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	if (bind(sock,(t_sockaddr *) &sin, sizeof sin) == SOCKET_ERROR)
		exit_error("bind");

	if (listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
		exit_error("listen");
	return (sock);
}

int				main(int argc, char *argv[])
{
	int		sock;

	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(-1);
	}
	sock = init_connection(ft_atoi(argv[1]));
	server(sock);
	return (0);
}
