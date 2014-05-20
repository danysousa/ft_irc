/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:51:49 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/17 20:51:29 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <libft.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>

# define	B_SIZE	(4096)
# define	EOFT	(':')
# define	PUTF	(1)
# define	CMD		(2)

#endif
