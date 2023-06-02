/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:17:34 by ndiamant          #+#    #+#             */
/*   Updated: 2023/06/02 17:28:52 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_values(t_env *env, char **av, int ac)
{
	env->mutex_fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!env->mutex_fork)
		return (0);
	env->start_time = get_time();
	env->time_to_die = ft_atoi(av[2]);
	env->sleep_time = ft_atoi(av[3]);
	env->diner_time = ft_atoi(av[4]);
	env->last_ate = 0;
	if (ac == 6)
		env->meal_max = ft_atoi(av[5]);
	else
		env->meal_max = MAX_INT;
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

int	check_errors(char **av, t_philo *philo, t_env *env, int ac)
{
	if (!init_values(env, av, ac))
	{
		error("Malloc error", philo, env);
		return (1);
	}
	return (0);
}
