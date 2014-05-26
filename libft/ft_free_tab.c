/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 12:21:39 by dsousa            #+#    #+#             */
/*   Updated: 2014/05/24 16:46:43 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_tab(void **tab)
{
	int		i;

	i = ft_tablen((char **)tab);
	if (tab)
	{
		while (i >= 0)
		{
			free(*tab);
			*tab = NULL;
			tab++;
			i--;
		}
		free(tab);
		tab = NULL;
	}
}
