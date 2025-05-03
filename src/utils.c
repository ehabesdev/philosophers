/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:57:37 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 00:09:42 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	print_error(const char *message)
{
	write(STDERR_FILENO, "==error== \n", 11);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi_check(const char *str, int *error_flag)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	*error_flag = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (*error_flag = 1, 0);
	if (!is_digit(str[i]))
		return (*error_flag = 1, 0);
	while (is_digit(str[i]))
	{
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return (*error_flag = 1, 0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (*error_flag = 1, 0);
	return ((int)result);
}
