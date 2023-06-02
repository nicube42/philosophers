/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:27:50 by ndiamant          #+#    #+#             */
/*   Updated: 2023/06/02 17:18:10 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void check_death(t_philo *philo)
{
  while (philo[current]->current_meal)
		{
			 if (all philo not dead)
				  return ;
			 if (philo[current]->current_meal < philo->env->max_meal)
				  return ;
				current++;
		}
		philo->env->check_death = 1;
}

void	start_thread(char **av, t_philo *philo, t_env *env)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].forks = malloc(sizeof(char) * (ft_atoi(av[1]) + 1));
		memset(philo[i].forks, 'y', ft_atoi(av[1]) + 1);
		philo[i].forks[ft_atoi(av[1])] = 0;
		philo[i].current = i;
		philo[i].env = env;
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	//while (philo->env->check_death == 0)
		//check_death(philo);
}

void	stop_thread(char **av, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(philo[i].thread, NULL);
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
