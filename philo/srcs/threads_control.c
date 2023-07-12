/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:27:50 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/12 18:55:45 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_death(t_env *env)
{
	int	i;

	i = 0;
	env->meal_left = env->philo_num * env->meal_max;
	while (i < env->philo_num)
	{
		pthread_mutex_lock(&env->mutex_check);
		if (env->philo[i].full_meal == 1)
			env->meal_left -= 1;
		if (env->meal_left == 0)
		{
			env->check_death = 1;
			pthread_mutex_unlock(&env->mutex_check);
			return ;
		}
		if (get_time() - env->philo[i].last_ate > env->time_to_die
			&& env->philo[i].last_ate != 0 && env->philo[i].is_eating == 0)
		{
			env->check_death = 1;
			print("died", &env->philo[i]);
			pthread_mutex_unlock(&env->mutex_check);
			return ;
		}
		pthread_mutex_unlock(&env->mutex_check);
	}
}

void	start_thread(char **av, t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < ft_atoi(av[1]))
	{
		env->philo[i].current = i;
		env->philo[i].env = env;
		env->philo[i].last_ate = 0;
		env->philo[i].meal_count = 0;
		pthread_create(&env->philo[i].thread, NULL, &routine, &env->philo[i]);
		i++;
	}
	i = -1;
	while (env->check_death == 0)
		check_death(env);
}

void	stop_thread(char **av, t_env *env)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(env->philo[i].thread, NULL);
		i++;
	}
}

void	init_mutex(t_env *env, char **av)
{
	int	i;
	int	philo_num;

	philo_num = ft_atoi(av[1]);
	pthread_mutex_init(&env->mutex_check, NULL);
	i = -1;
	while (++i < philo_num)
	{
		pthread_mutex_init(&env->mutex_fork[i], NULL);
		pthread_mutex_init(&env->philo[i].mutex_philo, NULL);
	}
	i = 1;
	env->philo[0].l_fork = &env->mutex_fork[0];
	env->philo[0].r_fork = &env->mutex_fork[philo_num - 1];
	while (i < philo_num)
	{
		env->philo[i].l_fork = &env->mutex_fork[i];
		env->philo[i].r_fork = &env->mutex_fork[i - 1];
		i++;
	}
}

void	destroy_mutex(t_env *env, char **av)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&env->mutex_check);
	while (++i < ft_atoi(av[1]))
	{
		pthread_mutex_destroy(&env->mutex_fork[i]);
		pthread_mutex_destroy(&env->philo[i].mutex_philo);
	}
	free_all(env);
}
