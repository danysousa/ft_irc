/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 16:05:01 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/23 16:07:06 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERV_DEFINE_H
# define SERV_DEFINE_H

# define INVALID_SOCKET			(-1)
# define SOCKET_ERROR			(-1)
# define CRLF					("\r\n")
# define MAX_CLIENTS			(100)
# define BUF_SIZE				(1024)
# define NAME_LEN				(9)
# define MAX_CHANNEL			(10)
# define CHOOSE_CMD				choose_cmd(buff, &(server->clients[i]), server)

#endif
