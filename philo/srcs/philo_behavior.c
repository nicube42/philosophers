/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:27:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/06/02 18:33:38 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	philo_eating(t_philo *philo)
{
	int	fork;

	fork = -1;
	if (philo->forks[philo->current + 1] != 0)
		fork = philo->current + 1;
	else
		fork = 0;
	pthread_mutex_lock(&(philo->env->mutex_fork[philo->current]));
	print("has taken a fork", philo);
	if (fork != 0)
	{
		pthread_mutex_lock(&(philo->env->mutex_fork[fork]));
		print("has taken a fork", philo);
		print("is eating", philo);
		usleep(philo->env->diner_time * 1000);
		pthread_mutex_lock(&philo->env->mutex_philo);
		philo->env->meal_count++;
		philo->env->last_ate = get_time();
		pthread_mutex_unlock(&philo->env->mutex_philo);
		pthread_mutex_unlock(&(philo->env->mutex_fork[fork]));
	}
	pthread_mutex_unlock(&(philo->env->mutex_fork[philo->current]));
}

static void	philo_sleeping(t_philo *philo)
{
	if (philo->env->check_death == 0)
	{
		print("is sleeping", philo);
		usleep(philo->env->sleep_time * 1000);
	}
}

static void	philo_thinking(t_philo *philo)
{
	if (philo->env->check_death == 0)
	{
		print("is thinking", philo);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->current % 2)
		usleep (1500);
	if (philo->env->check_death == 0)
		philo_eating(philo);
	philo_sleeping(philo);
	philo_thinking(philo);
	return (NULL);
}
