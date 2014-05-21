/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 16:48:18 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/21 14:49:40 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include "../includes/serveur.h"

static void		server(int sock)
{
	char buff[BUF_SIZE + 1];
	/* the index for the array */
	int actual = 0;
	int max = sock;
	/* an array for all clients */
	t_client clients[MAX_CLIENTS];

	fd_set rdfs;

	while (1)
	{
		int i = 0;
		FD_ZERO(&rdfs);

		/* add STDIN_FILENO */
		FD_SET(STDIN_FILENO, &rdfs);

		/* add the connection socket */
		FD_SET(sock, &rdfs);

		/* add socket of each client */
		for(i = 0; i < actual; i++)
		{
			FD_SET(clients[i].sock, &rdfs);
		}

		if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
			exit_error("select");

		/* something from standard input : i.e keyboard */
		if(FD_ISSET(STDIN_FILENO, &rdfs))
		{
			/* stop process when type on keyboard */
			break;
		}
		else if(FD_ISSET(sock, &rdfs))
		{
			/* new client */
			t_sockaddr_in csin;
			socklen_t sinsize = sizeof csin;
			int csock = accept(sock, (t_sockaddr *)&csin, &sinsize);
			if(csock == SOCKET_ERROR)
			{
				error("accept");
				continue;
			}

			/* after connecting the client sends its name */
			if(read_client(csock, buff) == -1)
			{
				/* disconnected */
				continue;
			}

			/* what is the new maximum fd ? */
			max = csock > max ? csock : max;

			FD_SET(csock, &rdfs);

			t_client c;
			c.sock = csock;
			strncpy(c.name, buff, NAME_LEN);
			clients[actual] = c;
			actual++;
		}
		else
		{
			int i = 0;
			for(i = 0; i < actual; i++)
			{
				/* a client is talking */
				if(FD_ISSET(clients[i].sock, &rdfs))
				{
					t_client client = clients[i];
					int c = read_client(clients[i].sock, buff);
					/* client disconnected */
					if(c == 0)
					{
						close(clients[i].sock);
						remove_client(clients, i, &actual);
						strncpy(buff, client.name, NAME_LEN);
						strncat(buff, " disconnected !", BUF_SIZE - strlen(buff));
						send_message_to_all_clients(clients, client, actual, buff, 1);
					}
					else
					{
						send_message_to_all_clients(clients, client, actual, buff, 0);
					}
					break;
				}
			}
		}
	}
	clear_clients(clients, actual);
	close(sock);
}

static void		clear_clients(t_client *clients, int actual)
{
	int		i;

	i = 0;
	while (i < actual)
	{
		close(clients[i].sock);
		i++;
	}
}

static void		remove_client(t_client *clients, int to_remove, int *actual)
{
	/* we remove the client in the array */
	memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(t_client));
	/* number client - 1 */
	(*actual)--;
}

static void		send_message_to_all_clients(t_client *clients, t_client sender, int actual, const char *buff, char from_server)
{
	int		i;
	char	message[BUF_SIZE + 1];

	message[0] = 0;
	i = 0;
	while (i < actual)
	{
		/* we don't send message to the sender */
		if(sender.sock != clients[i].sock)
		{
			if(from_server == 0)
			{
				strncpy(message, sender.name, BUF_SIZE);
				strncat(message, " : ", sizeof message - strlen(message) - 1);
			}
			strncat(message, buff, sizeof message - strlen(message) - 1);
			write_client(clients[i].sock, message);
		}
		i++;
	}
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

static int		read_client(int sock, char *buff)
{
	int n = 0;

	if ((n = recv(sock, buff, BUF_SIZE, 0)) < 0)
	{
		error("recv");
		/* if recv error we disonnect the client */
		n = 0;
	}
	buff[n] = 0;
	return (n);
}

static void		write_client(int sock, const char *buff)
{
	if (send(sock, buff, strlen(buff), 0) < 0)
		exit_error("send");
}

void			usage(char *str)
{
	printf("Usage: %s <port>\n", str);
	exit(-1);
}

int				main(int argc, char *argv[])
{
	int		sock;

	if (argc != 2)
		usage(argv[0]);
	sock = init_connection(ft_atoi(argv[1]));
	server(sock);
	return (0);
}
