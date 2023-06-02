/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:17:34 by ndiamant          #+#    #+#             */
/*   Updated: 2023/06/02 15:21:57 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_values(t_env *env, char **av)
{
	env->mutex_fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!env->mutex_fork)
		return (0);
	env->start_time = get_time();
	env->time_to_die = ft_atoi(av[2]);
	env->sleep_time = ft_atoi(av[3]);
	env->diner_time = ft_atoi(av[4]);
	env->meal_max = ft_atoi(av[5]);
	env->meal_count = 0;
	env->check_death = 0;
	return (1);
}

void	error(char *err_message, t_philo *philo, t_env *env)
{
	printf("%s\n", err_message);
	if (env->mutex_fork)
		free(env->mutex_fork);
	if (env)
		free(env);
	if (philo)
		free(philo);
}

int	check_errors(char **av, t_philo *philo, t_env *env)
{
	if (!init_values(env, av))
	{
		error("Malloc error", philo, env);
		return (1);
	}
	return (0);
}
