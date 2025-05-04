/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:33:15 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/04 06:25:51 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	handle_single_philo(t_philo *philo)
{
	t_sim_data	*data;

	data = philo->sim_data;
	print_status(philo, TAKEN_FORK);
	precise_usleep(data, data->time_die);
}

static int	run_life_cycle(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	eat(philo);
	if (check_stop_flag(philo->sim_data))
		return (0);
	sleep_philo(philo);
	if (check_stop_flag(philo->sim_data))
		return (0);
	think(philo);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;
	t_sim_data	*data;

	philo = (t_philo *)arg;
	data = philo->sim_data;
	if (data->num_philos == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_usleep(data, 1);
	while (!check_stop_flag(data))
	{
		if (!run_life_cycle(philo))
			break ;
	}
	return (NULL);
}
