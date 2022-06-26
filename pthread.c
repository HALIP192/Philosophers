/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:05:15 by ntitan            #+#    #+#             */
/*   Updated: 2022/06/26 18:05:16 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

int			ft_strlen(char *const str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		mutex_print(uintmax_t time, uint phil_num,
							char *const mes)
{
	static pthread_mutex_t	stdout_mutex = PTHREAD_MUTEX_INITIALIZER;
	static char				pattern[] = "[00000.000]:000000000 ";

	pthread_mutex_lock(&stdout_mutex);
	if (pattern[0] == 0)
	{
		pthread_mutex_unlock(&stdout_mutex);
		return ;
	}
	ft_putunbr(pattern + 1, (uint)time);
	ft_putunbr(pattern + 12, phil_num + 1);
	(void)write(1, pattern, 22);
	(void)write(1, mes, ft_strlen(mes));
	(void)write(1,"\n", 1);
	pthread_mutex_unlock(&stdout_mutex);
}

uintmax_t	take_forks(size_t phil_num, unsigned char take,
						t_data *restrict data)
{
	uintmax_t	time;

	if(take)
	{
		pthread_mutex_lock(data->fork + phil_num);
		if (data->phil_num == 1)
		{
			usleep(data->live_time + 100);
			return (0);
		}
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
					"has taken L fork ");
		pthread_mutex_lock(data->fork + (phil_num + 1) % data->phil_num);
		time = ft_time() - data->pthread_start[phil_num];
		mutex_print(time, phil_num, "has taken R fork ");
		return (time);
	}
	else
	{
		pthread_mutex_unlock(data->fork + phil_num);
		pthread_mutex_unlock(data->fork + (phil_num + 1) % data->phil_num);
		return (0);
	}
}

void	*phil_routine(size_t phil_num)
{
	t_data	*data;

	data = init_struct();
	data->pthread_start[phil_num] = ft_time();
	data->dt[phil_num] = data->live_time;
	while (data->eaten[phil_num] < data->eat_num && !check_stop(data))
	{
		data->dt[phil_num] = take_forks(phil_num, 1 , data) + data->live_time;
		mutex_print(data->dt[phil_num] - data->live_time, phil_num,
					"is eating");
		usleep(data->eat_time);
		take_forks(phil_num, 0, data);
		++data->eaten[phil_num];
		if (check_stop(data))
			return (NULL);
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
					"is sleeping");
		usleep(data->sleep_time);
		if (check_stop(data))
			return (NULL);
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
					"is thinking");
	}
	return (NULL);
}

void	*death(t_data *data)
{
	uint cnt;
	uint all_eat;

	cnt = 0;
	all_eat = 0;
	while(!check_stop(data) && all_eat < data->phil_num)
	{
		all_eat += data->eaten[cnt] >= data->eat_num;
		if (data->eaten[cnt] >= data->eat_num && ++cnt)
			continue ;
		if (ft_time() - data->pthread_start[cnt] > data->dt[cnt])
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			mutex_print(ft_time() - data->pthread_start[cnt], cnt,
						"died");
			return (NULL);
		}
		++cnt;
	}
	return (NULL);
}
