/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:09:41 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/11 23:37:23 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_INT 2147483647
# define MIN_INT -2147483648

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

struct	s_philo;

typedef struct s_env
{
	struct s_philo	*philo;
	pthread_mutex_t	mutex_philo;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_check;
	int				philo_num;
	long			start_time;
	int				sleep_time;
	int				diner_time;
	unsigned long	time_to_die;
	int				meal_max;
	int				meal_left;
	int				check_death;
}t_env;

typedef struct s_philo
{
	t_env			*env;
	pthread_t		thread;
	int				meal_count;
	unsigned long	last_ate;
	int				current;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *mutex_philo;
	char			*philo;
}t_philo;

int				ft_isdigit(int c);
int				ft_atoi(const char *str);

void			start_thread(char **av, t_philo *philo, t_env *env);
void			stop_thread(char **av, t_env *env);
void			init_mutex(t_env *env, char **av);
void			destroy_mutex(t_env *env, char **av);

void			*routine(void *arg);

unsigned long	get_time(void);
void			print(char *error, t_philo *philo);

void			*routine(void *arg);

int				init_values(t_env *env, char **av, int ac);
void			error(char *err_message, t_philo *philo, t_env *env);
int				check_errors(char **av, t_philo *philo, t_env *env, int ac);

#endif