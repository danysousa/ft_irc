/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:08:49 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/17 20:51:24 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <libft.h>

# define	EOFT	(':')
# define	B_SIZE	(4096)
# define	PUTF	(1)
# define	CMD		(2)

int		send_msg(int socket, char *msg, int flag);
int		send_error(int socket, char *msg);

char	*get_pwd();
void	ft_ls(int cs);
int		ft_cd(int cs, char *dir, char *home);

int		ft_putf(int cs, char *buff, int size);


#endif
