/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/22 10:55:34 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/22 18:22:07 by dsousa           ###   ########.fr       */
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

static char		*ft_join(char *buff, t_client *client, t_server *server)
{
	int		i;
	char	*tmp;

	(void)server;
	tmp = ft_strsub(buff, 6, ft_strlen(buff) - 6);
	i = 0;
	if (!chk_char_name(tmp))
		return ("Channel format invalid");
	while (i < MAX_CHANNEL)
	{
		if (client->channel[i] && tmp)
		{
			if (ft_strcmp(client->channel[i], tmp) == 0)
				return ("Channel already joined");
		}
		i++;
	}
	i = 0;
	while (client->channel[i])
		i++;
	if (client->nb_channel + 1 == MAX_CHANNEL)
		return ("Join limit: please leave a channel");
	client->channel[i] = ft_strdup(tmp);
	client->nb_channel++;
	return ("Channel join !");
}

static char		*ft_leave(char *buff, t_client *client, t_server *server)
{
	char	*tmp;
	int		i;

	i = 0;
	(void)server;
	if (ft_strlen(buff) > 6)
	{
		if (buff[6] != ' ')
			return ("Invalid command");
		tmp = ft_strsub(buff, 7, ft_strlen(buff) - 7);
		while (i < MAX_CHANNEL)
		{
			if (client->channel[i] && tmp)
			{
				if (ft_strcmp(client->channel[i], tmp) == 0)
				{
					client->channel[i] = NULL;
					client->nb_channel--;
					return ("Leave success");
				}
			}
			i++;
		}
		return ("Channel not found");
	}
	else
	{
		while (i < MAX_CHANNEL)
			client->channel[i++] = NULL;
		client->nb_channel = 0;
	}
	return ("All channels leaved");
}

char			*cmd(char *buff, t_client *client, t_server *server)
{
	int					i;
	static t_cmd		tb_cmd[5] =

	{
		{"/who", &ft_who, 4},
		{"/nick ", &ft_nick, 6},
		{"/join ", &ft_join, 6},
		{"/leave", &ft_leave, 6},
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
