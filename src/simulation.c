/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:55:40 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 12:02:25 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	start_threads(t_sim_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, \
						philosopher_routine, &data->philos[i]) != 0)
			return (print_error(ERR_THREAD_CREATE), 0);
		i++;
	}
	return (1);
}

int	join_threads(t_sim_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (print_error(ERR_THREAD_JOIN), 0);
		i++;
	}
	return (1);
}
