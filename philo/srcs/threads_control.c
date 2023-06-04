/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:27:50 by ndiamant          #+#    #+#             */
/*   Updated: 2023/06/04 15:15:53 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_death(t_env *env)
{
	int	i;
	int temoin;

	i = 0;
	temoin = 0;
	while (i <= env->philo_num)
	{
		//if (all philo not dead)
		//	return ;
		if (env->philo[i].meal_count >= env->meal_max)
			temoin++;
		//printf("%d\n", temoin);
		if (temoin >= env->philo_num)
		{
			env->check_death = 1;
			return ;
		}
		i++;
	}
}

void	start_thread(char **av, t_philo *philo, t_env *env)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		env->philo[i].forks = malloc(sizeof(char) * (ft_atoi(av[1]) + 1));
		memset(env->philo[i].forks, 'y', ft_atoi(av[1]) + 1);
		env->philo[i].forks[ft_atoi(av[1])] = 0;
		env->philo[i].current = i;
		env->philo[i].env = env;
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

	i = 0;
	pthread_mutex_init(&env->mutex_check, NULL);
	pthread_mutex_init(&env->mutex_philo, NULL);
	pthread_mutex_init(&env->mutex_current, NULL);
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&env->mutex_fork[i], NULL);
		i++;
	}
}

void	destroy_mutex(t_env *env, char **av)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&env->mutex_current);
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_destroy(&env->mutex_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&env->mutex_philo);
	pthread_mutex_destroy(&env->mutex_check);
}
