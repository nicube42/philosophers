/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:27:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/12 18:56:22 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	drop_fork(t_philo *philo)
{
	if (philo->env->philo_num != 1)
		pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (philo->env->check_death == 0)
		print("has taken a fork", philo);
	if (philo->env->philo_num != 1)
	{
		pthread_mutex_lock(philo->l_fork);
		if (philo->env->check_death == 0)
			print("has taken a fork", philo);
	}
}

static void	philo_eating(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->mutex_philo);
	if (philo->env->philo_num != 1)
	{
		philo->is_eating = 1;
		if (philo->env->check_death == 0)
			print("is eating", philo);
		philo->last_ate = get_time();
		ft_usleep(philo->env->diner_time);
		philo->meal_count += 1;
		if (philo->meal_count >= philo->env->meal_max)
			philo->full_meal = 1;
		philo->is_eating = 0;
	}
	else
	{
		philo->last_ate = get_time();
		ft_usleep(philo->env->time_to_die);
	}
	pthread_mutex_unlock(&philo->mutex_philo);
	drop_fork(philo);
}

static void	philo_sleeping(t_philo *philo)
{
	if (philo->env->check_death == 0)
	{
		print("is sleeping", philo);
		ft_usleep(philo->env->sleep_time);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->current % 2)
		usleep (1500);
	while (philo->env->check_death == 0)
	{
		philo_eating(philo);
		if (philo->env->check_death == 0)
			philo_sleeping(philo);
		if (philo->env->check_death == 0)
			print("is thinking", philo);
	}
	return (NULL);
}
