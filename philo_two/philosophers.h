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
#include <semaphore.h>

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
	sem_t			*fork_sema;
	sem_t			*write_sema;
	sem_t			*eat_sema;
	t_state			state;
	uint64_t		start_time;
}					t_data;

typedef struct		s_philo
{
	int				id;
	t_data			*data;
	uint64_t		last_eaten;
	int				amount_eaten;
}					t_philo;

int announce(char *message);
uint64_t			get_time();
int					ft_atoi(const char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(const char *str);
long long			ft_strtoll(char *str, int base);
void 				start_threads(t_data *data, t_philo *philo,
					   pthread_t *philo_threads);
void 				my_usleep(uint64_t wait);
int					safe_announce(char *message, t_philo *philo, int death);
void				close_semaphores(t_data *data);
int					open_semaphores(t_data *data);
size_t				ft_strlen(const char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(uint64_t n, int fd);

#endif //PHILOSOPHERS_H
