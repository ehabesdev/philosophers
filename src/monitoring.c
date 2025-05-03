/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:33:33 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 18:10:33 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	try_set_stop_flag_on_death(t_sim_data *data)
{
	int	set_by_this_call;

	set_by_this_call = 0;
	pthread_mutex_lock(&data->data_mutex);
	if (!data->stop_flag)
	{
		data->stop_flag = 1;
		set_by_this_call = 1;
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (set_by_this_call);
}

static int	is_philosopher_dead(t_philo *philo)
{
	t_sim_data			*data;
	unsigned long long	current_time;
	unsigned long long	time_since_last_meal;
	unsigned long long	local_last_meal;
	int					local_stop_flag;

	data = philo->sim_data;
	pthread_mutex_lock(&data->data_mutex);
	local_last_meal = philo->last_meal_time;
	local_stop_flag = data->stop_flag;
	pthread_mutex_unlock(&data->data_mutex);
	if (local_stop_flag)
		return (0);
	current_time = get_current_time_ms();
	time_since_last_meal = current_time - local_last_meal;
	if (time_since_last_meal > (unsigned long long)data->time_die)
	{
		if (try_set_stop_flag_on_death(data))
			return (print_status(philo, DIED), 1);
	}
	return (0);
}

static int	have_all_eaten(t_sim_data *data)
{
	int	goal_reached;
	int	sim_stopped_before_check;

	goal_reached = 0;
	if (data->num_must_eat != -1)
	{
		pthread_mutex_lock(&data->data_mutex);
		sim_stopped_before_check = data->stop_flag;
		if (!sim_stopped_before_check)
		{
			if (data->num_finished_eating >= data->num_philos)
			{
				data->stop_flag = 1;
				goal_reached = 1;
			}
		}
		else if (data->num_finished_eating >= data->num_philos)
			goal_reached = 1;
		pthread_mutex_unlock(&data->data_mutex);
	}
	return (goal_reached);
}

void	monitor_simulation(t_sim_data *data)
{
	int	i;
	int	simulation_should_end;

	simulation_should_end = 0;
	while (!simulation_should_end)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (is_philosopher_dead(&data->philos[i]))
			{
				simulation_should_end = 1;
				break ;
			}
			i++;
		}
		if (simulation_should_end)
			break ;
		if (have_all_eaten(data))
		{
			simulation_should_end = 1;
			break ;
		}
		precise_usleep(data, 1);
	}
}
