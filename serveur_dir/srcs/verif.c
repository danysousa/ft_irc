/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:46:52 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/21 18:02:30 by dsousa           ###   ########.fr       */
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
		if (ft_strcmp(server->clients[i].name, buff) == 0)
			return (-1);
		i++;
	}
	return (0);
}
