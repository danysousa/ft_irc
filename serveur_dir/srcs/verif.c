/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:46:52 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/22 18:27:06 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/serveur.h"

int		check_pseudo(char *buff, t_server *server)
{
	int		i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (server->clients[i].name)
		{
			if (ft_strcmp(server->clients[i].name, buff) == 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int		check_channel(t_client sender, t_client dest)
{
	int		i;
	int		j;

	i = 0;
	if (sender.nb_channel == 0 && dest.nb_channel == 0)
		return (1);
	while (i < MAX_CHANNEL)
	{
		j = 0;
		while (j < MAX_CHANNEL)
		{
			if (sender.channel[i] && dest.channel[j])
			{
				if (ft_strcmp(sender.channel[i], dest.channel[j]) == 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		chk_char_name(char *line)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(line);
	if (len >= NAME_LEN || len == 0)
		return (0);
	while (line[i])
	{
		if (ft_isprint(line[i]) && line[i] != ' ')
			i++;
		else
			return (0);
	}
	return (1);
}
