/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:10:46 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 17:16:35 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	lock_one_fork(t_philo *philo, pthread_mutex_t *fork_to_lock)
{
	if (check_stop_flag(philo->sim_data))
		return (0);
	pthread_mutex_lock(fork_to_lock);
	if (check_stop_flag(philo->sim_data))
	{
		pthread_mutex_unlock(fork_to_lock);
		return (0);
	}
	print_status(philo, TAKEN_FORK);
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->sim_data->num_philos == 1)
		return (0);
	if (philo->id % 2 == 0)
	{
		if (!lock_one_fork(philo, philo->left_fork))
			return (0);
		if (check_stop_flag(philo->sim_data))
			return (pthread_mutex_unlock(philo->left_fork), 0);
		if (!lock_one_fork(philo, philo->right_fork))
			return (pthread_mutex_unlock(philo->left_fork), 0);
	}
	else
	{
		if (!lock_one_fork(philo, philo->right_fork))
			return (0);
		if (check_stop_flag(philo->sim_data))
			return (pthread_mutex_unlock(philo->right_fork), 0);
		if (!lock_one_fork(philo, philo->left_fork))
			return (pthread_mutex_unlock(philo->right_fork), 0);
	}
	return (1);
}

void	eat(t_philo *philo)
{
	t_sim_data	*data;

	data = philo->sim_data;
	print_status(philo, EATING);
	pthread_mutex_lock(&data->data_mutex);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	if (data->num_must_eat != -1 && philo->meals_eaten == data->num_must_eat)
		data->num_finished_eating++;
	pthread_mutex_unlock(&data->data_mutex);
	precise_usleep(data, data->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_philo(t_philo *philo)
{
	t_sim_data	*data;

	data = philo->sim_data;
	print_status(philo, SLEEPING);
	precise_usleep(data, data->time_sleep);
}

void	think(t_philo *philo)
{
	print_status(philo, THINKING);
}
