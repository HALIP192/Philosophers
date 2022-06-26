/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:01:26 by ntitan            #+#    #+#             */
/*   Updated: 2022/06/26 17:01:33 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

uintmax_t	ft_time(void)
{
	static struct timeval	t_val;

	gettimeofday(&t_val, NULL);
	return(t_val.tv_sec * 1000 + t_val.tv_usec);
}
