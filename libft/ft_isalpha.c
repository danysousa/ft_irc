/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 12:21:39 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/01 13:45:12 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_islower(int c)
{
	return ((c >= 'a') && (c <= 'z'));
}

static int		ft_isupper(int c)
{
	return ((c >= 'A') && (c <= 'Z'));
}

int				ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
