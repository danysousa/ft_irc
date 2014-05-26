/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 11:51:15 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/23 11:51:36 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	exit_error(char *error)
{
	ft_putstr_fd(ANSI_COLOR_RED, 2);
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(ANSI_COLOR_RESET, 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(-42);
}
