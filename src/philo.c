/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:50:46 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 12:03:18 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_sim_data	simulation_data;

	if (!parse_and_validate_args(argc, argv, &simulation_data))
		return (1);
	if (!init_simulation(&simulation_data))
	{
		return (1);
	}
	if (!start_threads(&simulation_data))
	{
		return (1);
	}
	if (!join_threads(&simulation_data))
	{
		return (1);
	}
	cleanup_simulation(&simulation_data);
	return (0);
}
