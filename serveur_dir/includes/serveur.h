/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:08:49 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/21 13:34:37 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
#define SERVER_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
# define CRLF					("\r\n")
# define MAX_CLIENTS			(100)
# define BUF_SIZE				(1024)
# define NAME_LEN				(9)

typedef struct sockaddr_in		t_sockaddr_in;
typedef struct sockaddr			t_sockaddr;
typedef struct in_addr			t_in_addr;
typedef struct					s_client
{
	int							sock;
	char						name[NAME_LEN];
}								t_client;

static int read_client(int sock, char *buffer);
static void write_client(int sock, const char *buffer);
static void send_message_to_all_clients(t_client *clients, t_client client, int actual, const char *buffer, char from_server);
static void remove_client(t_client *clients, int to_remove, int *actual);
static void clear_clients(t_client *clients, int actual);

#endif
