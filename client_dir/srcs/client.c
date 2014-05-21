/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:51:57 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/21 15:26:39 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/client.h"

static void		do_select(int sock, fd_set *rdfs)
{
	FD_ZERO(rdfs);
	FD_SET(STDIN_FILENO, rdfs);
	FD_SET(sock, rdfs);
	if (select(sock + 1, rdfs, NULL, NULL, NULL) == -1)
		exit_error("select");
}

static void		client(int sock, const char *name)
{
	char	buff[BUF_SIZE + 1];
	fd_set	rdfs;

	write_server(sock, name);
	while (42)
	{
		do_select(sock, &rdfs);
		if (FD_ISSET(STDIN_FILENO, &rdfs))
		{
			read_msg(buff);
			write_server(sock, buff);
		}
		else if (FD_ISSET(sock, &rdfs))
		{
			if (read_server(sock, buff) == 0)
			{
				ft_printf("Server disconnected !\n");
				break ;
			}
			ft_putendl(buff);
		}
	}
	close(sock);
}

static int		init_connection(const char *address, int port)
{
	int				sock;
	t_sockaddr_in	sin;
	struct hostent	*hostinfo;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		exit_error("socket");
	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		error("Unknown host %s.\n", address);
		exit(-1);
	}
	sin.sin_addr = *(t_in_addr *)hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	if (connect(sock, (t_sockaddr *)&sin, sizeof(t_sockaddr)) == SOCKET_ERROR)
		exit_error("connect");
	return (sock);
}

int				main(int argc, char **argv)
{
	int		sock;
	int		r;
	char	buff[NAME_LEN + 1];

	if (argc != 3)
	{
		ft_printf("Usage: %s <machine> <port>\n", argv[0]);
		exit(-1);
	}
	sock = init_connection(argv[1], ft_atoi(argv[2]));
	write(1, "What's your name ?: ", 20);
	r = read(0, buff, NAME_LEN);
	buff[r - 1] = '\0';
	client(sock, buff);
	return (0);
}
