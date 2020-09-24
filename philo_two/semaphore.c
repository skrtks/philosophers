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

#include <semaphore.h>
#include "philosophers.h"

void	close_semaphores(t_data *data)
{
	sem_close(data->write_sema);
	sem_close(data->fork_sema);
	sem_close(data->eat_sema);
}

int		open_semaphores(t_data *data)
{
	data->fork_sema = sem_open("/fork_sema", O_CREAT, 0644, data->n_philos);
	data->write_sema = sem_open("/write_sema", O_CREAT, 0644, 1);
	data->write_sema = sem_open("/eat_sema", O_CREAT, 0644, 1);
	sem_unlink("/eat_sema");
	sem_unlink("/fork_sema");
	sem_unlink("/write_sema");
	if (data->fork_sema == SEM_FAILED || data->write_sema == SEM_FAILED ||
		data->eat_sema == SEM_FAILED)
		return (1);
	return (0);
}
