/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/22 10:55:34 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/24 16:47:29 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/serveur.h"

char	*ft_who(char *buff, t_client *client, t_server *server)
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
			if (check_channel(*client, server->clients[i]))
			{
				if (count)
					write_client(client->sock, "\n");
				write_client(client->sock, server->clients[i].name);
				count++;
			}
		}
		i++;
	}
	return (NULL);
}

char	*ft_nick(char *buff, t_client *client, t_server *server)
{
	char		*tmp;

	(void)client;
	(void)server;
	tmp = buff + 6;
	if (!chk_char_name(tmp))
		return ("Name format invalid");
	if (check_pseudo(tmp, server) == -1)
		return ("Name is already taken");
	free(client->name);
	client->name = ft_strdup(tmp);
	return ("Nickname changed !");
}

char	*ft_join(char *buff, t_client *client, t_server *server)
{
	int		i;
	char	*tmp;

	(void)server;
	tmp = buff + 6;
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

char	*ft_msg(char *buff, t_client *client, t_server *server)
{
	char	**tmp;
	char	*msg;
	int		i;

	i = 0;
	tmp = ft_strsplit(buff, ' ');
	if (ft_tabsize((void **)tmp) < 3)
		return ("Usage : /msg <nick> <message>");
	while (i < MAX_CLIENTS)
	{
		if (server->clients[i].name)
		{
			if (ft_strcmp(server->clients[i].name, tmp[1]) == 0)
			{
				msg = ft_strjoin(client->name, " whispers: ");
				msg = ft_strjoin(msg, buff + ft_strlen(tmp[1]) + 6);
				write_client(server->clients[i].sock, msg);
				free(msg);
				ft_free_tab((void **)tmp);
				return (NULL);
			}
		}
		i++;
	}
	return ("Nickname not found");
}
