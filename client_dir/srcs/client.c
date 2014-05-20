/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:51:57 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/17 20:54:12 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void	usage(char *str)
{
	printf("Usage: %s <address> <port>\n", str);
	exit(-1);
}

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Connect error\n");
		exit(-42);
	}
	return (sock);
}

void	prompt(char *addr, int port, char ok)
{
	ft_printf("%C%C%s:%d", YELLOW, B_BLACK, addr, port);
	if (ok == -1)
		ft_printf(" %C>%C%C>%C ", RED, RESET, BLACK, RESET);
	else
		ft_printf(" %C>%C%C>%C ", GREEN, RESET, BLACK, RESET);
}

void	rep(char *buf, int r)
{
	buf[r] = '\n';
	if (buf[0] != -1)
		printf("%s\n", buf);
	else
		ft_printf("%C%s%C\n", RED, buf + 1, RESET);
}

void	send_file(char *buff, char *file, int sock, int fd)
{
	int		r;
	int		magic;
	char	eof;

	magic = PUTF;
	eof = EOF;
	send(sock, (char *)(&magic), 4, 0);
	send(sock, file, ft_strlen(file) + 1, 0);
	while ((r = read(fd, buff, B_SIZE)))
	{
		send(sock, buff, r, 0);
	}
	send(sock, &eof, 1, 0);
}

void	ft_putf_c(int sock, char *buff)
{
	int		fd;
	char	**cmd;

	cmd = ft_strsplit(buff, ' ');
	if ((fd = open(cmd[1], O_RDONLY)) != -1)
		send_file(buff, cmd[1], sock, fd);
	/*if ((r = recv(sock, buff, 1024, 0)) > 0)
		rep(buff, r);*/
	/*if (buff[0] == -1)
		return ;*/
}

int		main(int argc, char *argv[])
{
	int					port;
	int					sock;
	int					r;
	char				buff[B_SIZE + 1];

	if (argc != 3)
		usage(argv[0]);
	port = ft_atoi(argv[2]);
	sock = create_client(argv[1], port);
	prompt(argv[1], port, '0');
	while ((r = read(1, buff, B_SIZE)) > 0)
	{
		buff[r - 1] = '\0';
		if (!ft_strcmp(buff, "quit"))
			break ;
		if (!ft_strncmp(buff, "put ", 4) || !ft_strcmp(buff, "put"))
			ft_putf_c(sock, buff);
		else if ((r = recv(sock, buff, B_SIZE, 0)) > 0)
			rep(buff, r);
		write(sock, buff, r);
		prompt(argv[1], port, buff[0]);
	}
	close(sock);
	return (0);
}
