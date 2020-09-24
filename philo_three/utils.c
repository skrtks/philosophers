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

#include <zconf.h>
#include <sys/time.h>
#include <semaphore.h>
#include "philosophers.h"

void		*observe(void *a_philo)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo*)a_philo;
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
			safe_announce("died.", philo, 1);
		sem_post(data->eat_sema);
		usleep(100);
	}
	return (NULL);
}

int			announce(char *message)
{
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	return (1);
}

int			safe_announce(char *message, t_philo *philo, int death)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->write_sema);
	if (data->state == ALIVE && philo->amount_eaten != data->n_meals)
	{
		ft_putnbr_fd(get_time() - philo->data->start_time, 1);
		write(1, "\t", 1);
		ft_putnbr_fd(philo->id, 1);
		write(1, " ", 1);
		write(1, message, ft_strlen(message));
		write(1, "\n", 1);
	}
	if (death)
	{
		philo->data->state = DEATH;
		sem_post(philo->data->death_sema);
		usleep(100);
		sem_post(data->write_sema);
	}
	else
		sem_post(data->write_sema);
	return (0);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void		my_usleep(uint64_t wait)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < wait)
		usleep(100);
}
