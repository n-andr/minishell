/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:35:26 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 12:34:22 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	lnb;

	lnb = n;
	if (lnb < 0)
	{
		ft_putchar_fd('-', fd);
		lnb = lnb * -1;
	}
	if (lnb >= 10)
	{
		ft_putnbr_fd((lnb / 10), fd);
		ft_putnbr_fd((lnb % 10), fd);
	}
	else
		ft_putchar_fd((lnb + 48), fd);
}
/*
int	main(void)
{
	int	n = -10;

	ft_putnbr_fd(n, 1);
}
*/
