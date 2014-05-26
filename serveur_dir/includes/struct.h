/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 16:04:35 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/23 16:08:30 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct sockaddr_in		t_sockaddr_in;
typedef struct sockaddr			t_sockaddr;
typedef struct in_addr			t_in_addr;

typedef struct					s_client
{
	int							sock;
	char						*name;
	int							nb_channel;
	char						*channel[MAX_CHANNEL];
}								t_client;

typedef struct					s_server
{
	int							sock;
	int							max;
	fd_set						rdfs;
	t_client					clients[MAX_CLIENTS];
}								t_server;

typedef struct					s_cmd
{
	char						*name;
	char						*(*f)(char *, t_client *, t_server *);
	int							len;
}								t_cmd;

typedef struct					s_msg
{
	t_client					*clients;
	t_client					sender;
}								t_msg;

#endif
