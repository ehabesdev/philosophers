/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:25:00 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 00:13:08 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	validate_and_assign(int *dest, const char *arg_str,
	int check_positive)
{
	int	error_flag;
	int	value;

	error_flag = 0;
	value = ft_atoi_check(arg_str, &error_flag);
	if (error_flag)
		return (print_error(ERR_INVALID_ARG), 0);
	if (check_positive && value <= 0)
		return (print_error(ERR_NEG_PHILOS), 0);
	*dest = value;
	return (1);
}

int	parse_and_validate_args(int argc, char **argv, t_sim_data *data)
{
	if (argc != 5 && argc != 6)
		return (print_error(ERR_ARG_COUNT), 0);
	if (!validate_and_assign(&data->num_philos, argv[1], 1))
		return (0);
	if (!validate_and_assign(&data->time_die, argv[2], 0))
		return (0);
	if (!validate_and_assign(&data->time_eat, argv[3], 0))
		return (0);
	if (!validate_and_assign(&data->time_sleep, argv[4], 0))
		return (0);
	data->num_must_eat = -1;
	if (argc == 6)
	{
		if (!validate_and_assign(&data->num_must_eat, argv[5], 0))
			return (0);
	}
	return (1);
}
