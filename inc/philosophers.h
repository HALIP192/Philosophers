/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pholosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:05:36 by ntitan            #+#    #+#             */
/*   Updated: 2022/06/26 14:10:36 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# ifdef __linux__
#  include <malloc.h>
#  include <stdint.h>
# else
#  include <stdlib.h>
# endif

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>

typedef struct s_data
{
	uint			phil_num;
	uint			live_time;
	uint			eat_time;
	uint			sleep_time;
	uint			eat_num;

	pthread_t		*pthreads;
	pthread_mutex_t	*fork;
	uint			*eaten;
	uint 			*dt;

	unsigned char	stop;
	pthread_mutex_t stop_mutex;
}	t_data;

int	main(int argc, char *const *argv);
unsigned char	start_parse(t_data *restrict data, char *const argv);
int	ft_atoi(const char *str);
t_data	*init_struct(void);


# define ULL (unsigned long long )
#endif