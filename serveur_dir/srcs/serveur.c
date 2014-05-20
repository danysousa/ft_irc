/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 16:48:18 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/17 20:07:24 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

void		usage(char *str)
{
	printf("Usage: %s <port>\n", str);
	exit(-1);
}

int			create_server(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Bind error\n");
		exit(-42);
	}
	listen(sock, 42);
	return (sock);
}

void		soon(int cs)
{
	char				buff[B_SIZE];
	int					r;
	char				*home;

	home = get_pwd();

	printf("Listening new client on socket %d.\n", cs);
	while ((r = read(cs, buff, B_SIZE)) > 0)
	{
		buff[r] = '\0';
		printf("received %d bytes: [%d]\n", r, (int)(*buff));
		if ((int)(*buff) == PUTF)
			ft_putf(cs, buff, r);
		else if ((int)(*buff) == CMD)
			printf("Other cmd sent...\n");
		/*if (!ft_strcmp(buff, "ls"))
			ft_ls(cs);
		else if (!ft_strcmp(buff, "pwd"))
			send_msg(cs, get_pwd(), 0);
		else if (!ft_strncmp(buff, "cd ", 3) || !ft_strcmp(buff, "cd"))
			ft_cd(cs, buff, home);
		else if (!ft_strcmp(buff, "quit"))
			break ;
		else if (!ft_strncmp(buff, "put ", 4) || !ft_strcmp(buff, "put"))
			ft_putf_s(cs, buff);*/
		/*if (ft_strcmp())
		else
			send_error(cs, "invalid_cmd");*/
	}
	printf("Socket %d closed by client. Exiting...\n", cs);
}

int			main(int argc, char *argv[])
{
	int					sock;
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	pid_t				pid;

	signal(SIGCHLD, SIG_IGN);
	if (argc != 2)
		usage(argv[0]);
	sock = create_server(ft_atoi(argv[1]));
	while ((cs = accept(sock, (struct sockaddr *)&csin, &cslen)) > 0)
	{
		if ((pid = fork()) == -1)
			return (-1);
		if (pid == 0)
		{
			soon(cs);
			exit(0);
			return (0);
		}
	}
	close(cs);
	close(sock);
	return (0);
}
