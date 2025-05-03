/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:38:41 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/03 12:44:33 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define ERR_ARG_COUNT "Invalid number of arguments Usage: \
./philo num_philos time_die time_eat time_sleep [num_eat]"
# define ERR_INVALID_ARG "Invalid argument value \
(non-digit, overflow, or negative)"
# define ERR_NEG_PHILOS "Number of philosophers must be \
positive and greater than 0"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_MUTEX_INIT "Mutex initialization failed"
# define ERR_THREAD_CREATE "Thread creation failed"
# define ERR_THREAD_JOIN "Thread join failed"

typedef struct s_sim_data	t_sim_data;

typedef enum e_philo_status
{
	THINKING,
	TAKEN_FORK,
	EATING,
	SLEEPING,
	DIED
}	t_philo_status;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	unsigned long long	last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread_id;
	t_sim_data			*sim_data;
}	t_philo;

typedef struct s_sim_data
{
	int					num_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_must_eat;
	unsigned long long	start_time;
	int					stop_flag;
	int					num_finished_eating;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		data_mutex;
}	t_sim_data;

// utils.c
int					print_error(const char *message);
int					ft_atoi_check(const char *str, int *error_flag);

// args.c
int					parse_and_validate_args(int argc, char **argv, \
											t_sim_data *data);

// time_utils.c
unsigned long long	get_current_time_ms(void);
void				precise_usleep(unsigned long long duration_ms);

// init.c
int					init_simulation(t_sim_data *data);

// philo_routine.c
void				*philosopher_routine(void *arg);

// simulation.c
int					start_threads(t_sim_data *data);
int					join_threads(t_sim_data *data);

// cleanup.c
void				cleanup_simulation(t_sim_data *data);

#endif
