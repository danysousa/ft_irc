/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 13:56:11 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/23 15:57:00 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/serveur.h"

char	*choose_cmd(char *buff, t_client *client, t_server *server)
{
	int					i;
	static t_cmd		tb_cmd[6] =

	{
	{"/who", &ft_who, 4},
	{"/nick ", &ft_nick, 6},
	{"/join ", &ft_join, 6},
	{"/leave", &ft_leave, 6},
	{"/msg ", &ft_msg, 5},
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
