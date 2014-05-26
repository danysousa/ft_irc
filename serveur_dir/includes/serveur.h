/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:08:49 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/23 16:12:31 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdio.h>
# include <netdb.h>
# include "serv_define.h"
# include "struct.h"

int		read_client(int sock, char *buffer);
void	write_client(int sock, const char *buffer);
void	msg_all(t_msg msg, int actual, char *buffer, int serv_msg);
void	clear_clients(t_client *clients, int actual);
int		new_client(t_server *server, int *actual, char *buff);
void	client_talking(t_server *server, int *actual, char *buff);
int		check_pseudo(char *buff, t_server *server);
int		chk_char_name(char *line);
int		check_channel(t_client sender, t_client dest);

/*
**	choose_cmd.c
*/
char	*choose_cmd(char *buff, t_client *client, t_server *server);

/*
**	cmd.c
*/
char	*ft_who(char *buff, t_client *client, t_server *server);
char	*ft_nick(char *buff, t_client *client, t_server *server);
char	*ft_join(char *buff, t_client *client, t_server *server);
char	*ft_msg(char *buff, t_client *client, t_server *server);

/*
**	leave.c
*/
char	*ft_leave(char *buff, t_client *client, t_server *server);

#endif
