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

static void	*observe(void *a_philo)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo*)a_philo;
	data = philo->data;
	while (philo->amount_eaten != data->n_meals)
	{
		pthread_mutex_lock(&data->eat_mutex);
		if (data->state == DEATH)
		{
			pthread_mutex_unlock(&data->eat_mutex);
			break ;
		}
		if ((get_time() - philo->last_eaten) > data->t_die)
			safe_announce("died.", philo, 1);
		pthread_mutex_unlock(&data->eat_mutex);
		usleep(100);
	}
	return (NULL);
}

void		eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->fork_mutex[philo->l_fork]));
	safe_announce("picked up fork.", philo, 0);
	pthread_mutex_lock(&(philo->data->fork_mutex[philo->r_fork]));
	safe_announce("picked up fork.", philo, 0);
	my_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->eat_mutex);
	safe_announce("is eating.", philo, 0);
	philo->last_eaten = get_time();
	philo->amount_eaten++;
	pthread_mutex_unlock(&philo->data->eat_mutex);
	pthread_mutex_unlock(&(philo->data->fork_mutex[philo->l_fork]));
	pthread_mutex_unlock(&(philo->data->fork_mutex[philo->r_fork]));
}

void		*philo_loop(void *in_philo)
{
	t_philo		*philo;
	pthread_t	observe_thread;

	philo = (t_philo*)in_philo;
	philo->last_eaten = get_time();
	if (pthread_create(&observe_thread, NULL, observe, philo) != 0)
		return (NULL);
	while (philo->data->state == ALIVE && philo->amount_eaten !=
			philo->data->n_meals)
	{
		eat(philo);
		safe_announce("is sleeping.", philo, 0);
		my_usleep(philo->data->t_sleep);
		safe_announce("is thinking.", philo, 0);
	}
	pthread_join(observe_thread, NULL);
	return (NULL);
}

void		start_threads(t_data *data, t_philo *philo,
							pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&(philo_threads[i]), NULL, philo_loop, &(philo[i])))
		{
			while (i > 0)
			{
				pthread_join(philo_threads[i], NULL);
				i--;
			}
			return ;
		}
		usleep(100);
		i++;
	}
	i--;
	while (i > 0)
	{
		pthread_join(philo_threads[i], NULL);
		i--;
	}
	if (data->state == ALIVE)
		announce("All philosophers finished eating!");
}
