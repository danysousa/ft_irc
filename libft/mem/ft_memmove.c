/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 16:26:38 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/21 16:26:43 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned const char	*dp;
	unsigned char		*sp;

	if (n > 0)
	{
		dp = (unsigned char *)src;
		sp = (unsigned char *)dest;
		if (!n)
			return (dest);
		if (dest <= src)
			return (ft_memcpy(dest, src, n));
		dp += n;
		sp += n;
		while (n--)
			*--sp = *--dp;
		return (dest);
	}
	return (dest);
}
