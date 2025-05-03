/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:33:15 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 12:45:15 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;
	t_sim_data	*data;

	philo = (t_philo *)arg;
	data = philo->sim_data;
	pthread_mutex_lock(&data->print_mutex);
	printf("%llu %d is thinking\n", get_current_time_ms() - data->start_time, \
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	return (NULL);
}
