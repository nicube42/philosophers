/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:27:50 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/14 14:43:05 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_thread_content(char **av, t_env *env)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		env->philo[i].current = i;
		env->philo[i].env = env;
		env->philo[i].last_ate = 0;
		env->philo[i].meal_count = 0;
		env->philo[i].dead = 0;
		i++;
	}
}

int	start_thread(char **av, t_env *env)
{
	int	i;

	init_thread_content(av, env);
	env->start_time = get_time();
	if (pthread_create(&env->monitor_t, NULL, &monitor, &env->philo[0]))
		return (1);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_create(&env->philo[i].thread, NULL,
				&routine, &env->philo[i]))
			return (1);
		i++;
	}
	if (env->philo_num == 1)
	{
		(pthread_join(env->philo[0].supervisor, NULL));
		(pthread_join(env->philo[0].thread, NULL));
		(pthread_join(env->monitor_t, NULL));
	}
	return (0);
}

int	stop_thread(char **av, t_env *env)
{
	int	i;

	i = 0;
	(void) av;
	(void) env;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_join(env->philo[i].supervisor, NULL))
			return (1);
		if (pthread_join(env->philo[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(env->monitor_t, NULL))
		return (1);
	return (0);
}

int	init_mutex(t_env *env, char **av)
{
	int	i;
	int	philo_num;

	philo_num = ft_atoi(av[1]);
	if (pthread_mutex_init(&env->mutex_check, NULL))
		return (1);
	if (pthread_mutex_init(&env->mutex_print, NULL))
		return (1);
	i = -1;
	while (++i < philo_num)
	{
		if (pthread_mutex_init(&env->mutex_fork[i], NULL))
			return (1);
		if (pthread_mutex_init(&env->philo[i].mutex_philo, NULL))
			return (1);
	}
	handle_forks_pointers(env, philo_num);
	return (0);
}

int	destroy_mutex(t_env *env, char **av)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		if (pthread_mutex_destroy(&env->philo[i].mutex_philo))
			return (1);
		if (pthread_mutex_destroy(&env->mutex_fork[i]))
			return (1);
	}
	if (pthread_mutex_destroy(&env->mutex_print))
		return (1);
	if (pthread_mutex_destroy(&env->mutex_check))
		return (1);
	free_all(env);
	return (0);
}
