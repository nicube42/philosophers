/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:09:41 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/14 16:12:20 by ndiamant         ###   ########.fr       */
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
	pthread_t		monitor_t;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_check;
	pthread_mutex_t	mutex_print;
	int				forks_taken;
	int				full_meal;
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
	pthread_t		supervisor;
	int				dead;
	int				is_eating;
	int				meal_count;
	unsigned long	last_ate;
	int				current;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	mutex_philo;
}t_philo;

int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

int				start_thread(char **av, t_env *env);
int				stop_thread(char **av, t_env *env);
int				init_mutex(t_env *env, char **av);
int				destroy_mutex(t_env *env, char **av);

void			*routine(void *arg);
void			*supervisor(void *arg);
void			*monitor(void *arg);

void			philo_eating(t_philo *philo);
void			take_fork(t_philo *philo);
void			drop_fork(t_philo *philo);

void			check_all_meal(t_philo *philo);
void			handle_forks_pointers(t_env *env, int philo_num);
void			special_print(t_philo *philo);

unsigned long	get_time(void);
void			print(char *error, t_philo *philo);
int				ft_usleep(useconds_t time);

void			*routine(void *arg);

int				init_values(t_env *env, char **av, int ac);
void			error(char *err_message, t_env *env);
int				check_errors(char **av, t_env *env, int ac);
void			free_all(t_env *env);

#endif