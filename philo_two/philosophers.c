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

#include <pthread/pthread.h>
#include "philosophers.h"

static void	*observe(void *_philo)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo*)_philo;
	data = philo->data;
	while (philo->amount_eaten != data->n_meals)
	{
		sem_wait(data->eat_sema);
		if (data->state == DEATH)
		{
			sem_post(data->eat_sema);
			break ;
		}
		if ((get_time() - philo->last_eaten) > data->t_die)
		{
			safe_announce("died.", philo, 0);
			data->state = DEATH;
		}
		sem_post(data->eat_sema);
		usleep(100);
	}
	return (NULL);
}

void eat(t_philo *philo)
{
	sem_wait(philo->data->fork_sema);
	safe_announce("picked up fork.", philo, 0);
	sem_wait(philo->data->fork_sema);
	safe_announce("picked up fork.", philo, 0);
	sem_wait(philo->data->eat_sema);
	safe_announce("is eating.", philo, 0);
	philo->last_eaten = get_time();
	philo->amount_eaten++;
	sem_post(philo->data->eat_sema);
	my_usleep(philo->data->t_eat);
	sem_post(philo->data->fork_sema);
	sem_post(philo->data->fork_sema);
}

void *philo_loop(void *in_philo)
{
	t_philo *philo;
	pthread_t observe_thread;

	philo = (t_philo*) in_philo;
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

void start_threads(t_data *data, t_philo *philo, pthread_t *philo_threads)
{
	int i;

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
			return;
		}
		usleep(50);
		i++;
	}
	i--;
	while (i > 0)
	{
		pthread_join(philo_threads[i], NULL);
		i--;
	}
	if (data->state == ALIVE)
	{
		sem_wait(philo->data->write_sema);
		announce("All philosophers finished eating!");
		sem_post(philo->data->write_sema);
	}
}
