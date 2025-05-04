/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:41:47 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/04 05:18:19 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long long	get_current_time_ms(void)
{
	struct timeval		tv;
	unsigned long long	time_in_ms;

	if (gettimeofday(&tv, NULL) != 0)
		return (print_error("Error: gettimeofday failed"), 0);
	time_in_ms = (unsigned long long)(tv.tv_sec * 1000) + \
				(unsigned long long)(tv.tv_usec / 1000);
	return (time_in_ms);
}

void	precise_usleep(t_sim_data *data, \
						unsigned long long duration_ms)
{
	unsigned long long	start_time;
	unsigned long long	target_time;

	start_time = get_current_time_ms();
	if (start_time == 0)
		return ;
	target_time = start_time + duration_ms;
	while (get_current_time_ms() < target_time)
	{
		if (check_stop_flag(data))
			break ;
		usleep(100);
	}
}
