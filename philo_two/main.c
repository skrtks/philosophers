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

#include "philosophers.h"
#include "ft_strtoll.h"

int init_data(char** argv, t_data *data, int argc)
{
	if (argc == 6)
		data->n_meals = (int) ft_strtoll(argv[5], 10);
	else
		data->n_meals = -1;
	data->n_philos = (int) ft_strtoll(argv[1], 10);
	data->t_die = ft_strtoll(argv[2], 10);
	data->t_eat = ft_strtoll(argv[3], 10);
	data->t_sleep = ft_strtoll(argv[4], 10);
	data->state = ALIVE;
	data->start_time = get_time();
	if (data->t_die <= 0 || data->t_eat <= 0 || data->t_sleep <= 0)
	{
		announce("Provided times have to be => 0.");
		return (1);
	}
	if (data->n_philos < 2)
	{
		announce("Please provide 2 or more philosophers.");
		return (1);
	}
	if (argc == 6 && data->n_meals < 0)
	{
		announce("Number of meals has to be positive.");
		return (1);
	}
	return (0);
}

t_philo *free_on_error(t_philo *philo, pthread_t *philo_thread)
{
	if (philo_thread)
		free(philo_thread);
	if (philo)
		free(philo);
	return (NULL);
}

t_philo *init_philos(t_data *data, pthread_t **philo_threads)
{
	int i;
	t_philo *philos;

	philos = malloc(sizeof(t_philo) * data->n_philos);
	*philo_threads = malloc(sizeof(pthread_t) * data->n_philos);
	if (!philos || !*philo_threads)
		return (free_on_error(philos, *philo_threads));
	i = 0;
	while (i < data->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].amount_eaten = 0;
		i++;
	}
	return (philos);
}

int main(int argc, char **argv) {
	t_data *data;
	t_philo *philos;
	pthread_t *philo_threads;

	data = malloc(sizeof(t_data));
	if ((argc != 5 && argc != 6) || !data)
	{
		announce("Invalid number of arguments");
		return (1);
	}
	if (init_data(argv, data, argc))
	{
		announce("Error loading info");
		return (1);
	}
	philos = init_philos(data, &philo_threads);
	if (!philos)
	{
		announce("Error creating philos");
		return (1);
	}
	if (open_semaphores(data))
	{
		announce("Error creating semaphores");
		return (1);
	}
	start_threads(data, philos, philo_threads);
	close_semaphores(data);
	free_on_error(philos, philo_threads);
	return (0);
}
