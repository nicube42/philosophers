/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:09:41 by ndiamant          #+#    #+#             */
/*   Updated: 2023/06/02 17:27:25 by ndiamant         ###   ########.fr       */
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
	pthread_mutex_t	mutex_current;
	pthread_mutex_t	mutex_philo;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_check;
	long			start_time;
	int				sleep_time;
	int				diner_time;
	unsigned long	time_to_die;
	unsigned long	last_ate;
	int				meal_count;
	int				meal_max;
	int				check_death;
}t_env;

typedef struct s_philo
{
	t_env			*env;
	pthread_t		thread;
	int				current;
	char			*forks;
	char			*philo;
}t_philo;

int				ft_isdigit(int c);
int				ft_atoi(const char *str);

void			start_thread(char **av, t_philo *philo, t_env *env);
void			stop_thread(char **av, t_philo *philo);
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