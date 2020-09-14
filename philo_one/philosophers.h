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

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdint.h>
#include <zconf.h>

typedef enum	e_state
{
	ALIVE,
	DEATH,
	FINISHED
}				t_state;


typedef struct		s_data
{
	int				n_philos;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	int				n_meals;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t eat_mutex;
	t_state			state;
	uint64_t		start_time;
}					t_data;

typedef struct		s_philo
{
	int				id;
	t_data			*data;
	uint64_t		last_eaten;
	int				amount_eaten;
	int				l_fork;
	int				r_fork;
}					t_philo;

int announce(char *message);
uint64_t	get_time();
int init_mutex(t_data *data);
int						ft_atoi(const char *str);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
size_t					ft_strlen(const char *str);
long long				ft_strtoll(char *str, int base);
void 					start_threads(t_data *data, t_philo *philo,
						pthread_t *philo_threads);
void my_usleep(uint64_t wait);
int safe_announce(char *message, t_philo *philo, int death);
void destroy_mutexes(t_data* data, int pos);

#endif //PHILOSOPHERS_H
