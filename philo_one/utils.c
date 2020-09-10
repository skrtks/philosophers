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
#include <pthread.h>
#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void		ft_putnbr_fd(uint64_t n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((char)(n % 10 + '0'), fd);
}

int announce(char *message)
{
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	return (0);
}

int safe_announce(char *message, t_philo *philo, int death)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->write_mutex);
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
		usleep(500);
	}
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}

uint64_t	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void my_usleep(uint64_t wait, t_philo *philo)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < wait)
	{
		if ((get_time() - philo->last_eaten) > philo->data->t_die)
		{
			safe_announce("died.", philo, 1);
			break;
		}
		usleep(100);
	}
}
