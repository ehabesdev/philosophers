/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 03:04:50 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 03:55:57 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_mutexes(t_sim_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (print_error(ERR_MALLOC), 0);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (print_error(ERR_MUTEX_INIT), 0);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX_INIT), 0);
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX_INIT), 0);
	return (1);
}

static void	init_single_philo(t_sim_data *data, int i)
{
	t_philo	*philo;

	philo = &data->philos[i];
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->last_meal_time = data->start_time;
	philo->sim_data = data;
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->num_philos];
}

static int	init_philosophers(t_sim_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (print_error(ERR_MALLOC), 0);
	i = 0;
	while (i < data->num_philos)
	{
		init_single_philo(data, i);
		i++;
	}
	return (1);
}

int	init_simulation(t_sim_data *data)
{
	data->stop_flag = 0;
	data->num_finished_eating = 0;
	data->start_time = get_current_time_ms();
	if (data->start_time == 0)
		return (0);
	if (!init_mutexes(data))
		return (0);
	if (!init_philosophers(data))
	{
		return (0);
	}
	return (1);
}
