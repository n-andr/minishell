/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:53:59 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:22:55 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;

	memory = malloc(nmemb * size);
	if (memory == 0)
		return (memory);
	ft_bzero(memory, nmemb * size);
	return (memory);
}
/*
int main(void)
{
	void *r = ft_calloc(5, 8);
	free(r);
	return (0);
}
*/
