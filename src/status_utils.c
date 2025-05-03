/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:05:03 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 14:06:29 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_stop_flag(t_sim_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->data_mutex);
	flag = data->stop_flag;
	pthread_mutex_unlock(&data->data_mutex);
	return (flag);
}

void	print_status(t_philo *philo, t_philo_status status)
{
	unsigned long long	timestamp;
	t_sim_data			*data;

	data = philo->sim_data;
	if (check_stop_flag(data) && status != DIED)
		return ;
	pthread_mutex_lock(&data->print_mutex);
	timestamp = get_current_time_ms() - data->start_time;
	if (status == TAKEN_FORK)
		printf("%llu %d has taken a fork\n", timestamp, philo->id);
	else if (status == EATING)
		printf("%llu %d is eating\n", timestamp, philo->id);
	else if (status == SLEEPING)
		printf("%llu %d is sleeping\n", timestamp, philo->id);
	else if (status == THINKING)
		printf("%llu %d is thinking\n", timestamp, philo->id);
	else if (status == DIED)
		printf("%llu %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}
