/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:20:43 by ntitan            #+#    #+#             */
/*   Updated: 2022/06/26 14:55:59 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

t_data	*init_struct(void)
{
	static t_data	data;

	return(&data);
}

int ft_malloc_(t_data *restrict data)
{
	data->dt = (uintmax_t *)malloc(sizeof(uintmax_t) * data->phil_num);
	data->pthreads = (pthread_t *)malloc(sizeof(pthread_t) *
			(data->phil_num+ 1));
	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->phil_num);
	data->eaten = (uint *)malloc(sizeof(uint) * data->phil_num);
	data->pthread_start = (uintmax_t *)malloc(sizeof(uintmax_t) * data->phil_num);
	if ((uintmax_t)data->dt & (uintmax_t)data->pthreads & (uintmax_t)
			data->fork & (uintmax_t)data->eaten & (uintmax_t)data->pthread_start)
		return(0);
	ft_free_(data);
	return (1);
}

void	ft_free_(t_data *restrict data)
{
	free(data->pthreads);
	free(data->pthread_start);
	free(data->dt);
	free(data->fork);
	free(data->eaten);
}

int	check_stop(t_data *restrict data)
{
	int	ret;

	pthread_mutex_lock(&data->stop_mutex);
	ret = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (ret);
}

void	ft_putunbr(char *dest, uint n)
{
	dest[8] = n % 10 + 48;
	n /= 10;
	dest[7] = n % 10 + 48;
	n /= 10;
	dest[6] = n % 10 + 48;
	n /= 10;
	dest[4] = n % 10 + 48;
	n /= 10;
	dest[3] = n % 10 + 48;
	n /= 10;
	dest[2] = n % 10 + 48;
	n /= 10;
	dest[1] = n % 10 + 48;
	n /= 10;
	dest[0] = n % 10 + 48;
}