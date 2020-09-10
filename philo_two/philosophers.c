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

void eat(t_philo *philo)
{
	sem_wait(philo->data->fork_sema);
	safe_announce("picked up fork.", philo, 0);
	sem_wait(philo->data->fork_sema);
	safe_announce("picked up fork.", philo, 0);
	safe_announce("is eating.", philo, 0);
	my_usleep(philo->data->t_eat, philo);
	philo->last_eaten = get_time();
	philo->amount_eaten++;
	sem_post(philo->data->fork_sema);
	sem_post(philo->data->fork_sema);
}

void *philo_loop(void *in_philo)
{
	t_philo *philo;

	philo = (t_philo*) in_philo;
	philo->last_eaten = get_time();
	while (philo->data->state == ALIVE && philo->amount_eaten !=
			philo->data->n_meals)
	{
		if ((get_time() - philo->last_eaten) > philo->data->t_die)
		{
			safe_announce("died.", philo, 1);
			break;
		}
		eat(philo);
		safe_announce("is sleeping.", philo, 0);
		my_usleep(philo->data->t_sleep, philo);
		if ((get_time() - philo->last_eaten) > philo->data->t_die)
		{
			safe_announce("died.", philo, 1);
			break;
		}
		safe_announce("is thinking.", philo, 0);
	}
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
		announce("All philosophers have eaten enough!");
		sem_post(philo->data->write_sema);
	}
}
