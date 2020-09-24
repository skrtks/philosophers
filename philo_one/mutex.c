/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Philosophers                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: samkortekaas <samkortekaas@student.codam.nl> +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 09:50:34 by samkortekaas  #+#    #+#                 */
/*   Updated: 2020/05/08 13:50:58 by samkortekaas  ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philosophers.h"

void	destroy_mutexes(t_data *data, int pos)
{
	int	i;

	pthread_mutex_destroy((&data->write_mutex));
	pthread_mutex_destroy((&data->eat_mutex));
	i = 0;
	while (i < pos)
	{
		pthread_mutex_destroy((&data->fork_mutex[i]));
		i++;
	}
}

int		init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->eat_mutex, NULL))
	{
		pthread_mutex_destroy((&data->write_mutex));
		return (1);
	}
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->fork_mutex[i], NULL))
		{
			destroy_mutexes(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}
