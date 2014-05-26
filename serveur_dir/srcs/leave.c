/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 14:06:38 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/24 16:45:23 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/serveur.h"

static int		leave_next(t_client *client, char *tmp, int i)
{
	if (client->channel[i] && tmp)
	{
		if (ft_strcmp(client->channel[i], tmp) == 0)
		{
			free(client->channel[i]);
			client->channel[i] = NULL;
			client->nb_channel--;
			return (-1);
		}
	}
	return (0);
}

static void		init_channels(t_client *client, t_server *server)
{
	int		i;

	(void)server;
	i = 0;
	while (i < MAX_CHANNEL)
	{
		if (client->channel[i])
			free(client->channel[i]);
		client->channel[i++] = NULL;
	}
	client->nb_channel = 0;
}

char			*ft_leave(char *buff, t_client *client, t_server *server)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (ft_strlen(buff) > 6)
	{
		if (buff[6] != ' ')
			return ("Invalid command");
		tmp = ft_strsub(buff, 7, ft_strlen(buff) - 7);
		while (i < MAX_CHANNEL)
		{
			if (leave_next(client, tmp, i++) == -1)
			{
				free(tmp);
				return ("Leaved with success");
			}
		}
		free(tmp);
		return ("Channel not found");
	}
	else
		init_channels(client, server);
	free(tmp);
	return ("All channels leaved");
}
