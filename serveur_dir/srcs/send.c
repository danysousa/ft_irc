/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 15:33:39 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/17 18:52:01 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <libft.h>
#include "../includes/serveur.h"

int		send_msg(int socket, char *msg, int flag)
{
	if (msg)
	{
		send(socket, msg, ft_strlen(msg), flag);
		// printf("send: [%s]\n", msg);
	}
	return (0);
}

int		send_error(int socket, char *msg)
{
	char	error[2];
	char	*tmp;

	error[0] = -1;
	error[1] = '\0';
	// printf("error: [%s]\n", msg);
	tmp = ft_strjoin(error, msg);
	send(socket, tmp, ft_strlen(tmp), 0);
	return (0);
}
