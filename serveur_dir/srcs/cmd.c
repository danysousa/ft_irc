/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/22 10:55:34 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/22 12:17:52 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/serveur.h"

static char		*ft_who(char *buff, t_client *client, t_server *server)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	(void)buff;
	while (i < MAX_CLIENTS)
	{
		if (server->clients[i].name)
		{
			if (count)
				write_client(client->sock, "\n");
			write_client(client->sock, server->clients[i].name);
			count++;
		}
		i++;
	}
	return (NULL);
}

static char		*ft_nick(char *buff, t_client *client, t_server *server)
{
	char		*tmp;

	(void)client;
	(void)server;
	tmp = ft_strsub(buff, 6, ft_strlen(buff) - 6);
	if (!chk_char_name(tmp))
		return ("Name format invalid");
	if (check_pseudo(tmp, server) == -1)
		return ("Name is already taken");
	free(client->name);
	client->name = ft_strdup(tmp);
	return (NULL);
}

char			*cmd(char *buff, t_client *client, t_server *server)
{
	int					i;
	static t_cmd		tb_cmd[3] =

	{
		{"/who", &ft_who, 4},
		{"/nick ", &ft_nick, 6},
		{NULL, NULL, 0}
	};
	i = 0;

	while (tb_cmd[i].name != NULL)
	{
		if (ft_strncmp(tb_cmd[i].name, buff, tb_cmd[i].len) == 0)
			return (tb_cmd[i].f(buff, client, server));
		i++;
	}
	return ("Command not found");
}
