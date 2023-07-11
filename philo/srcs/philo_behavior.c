/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:27:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/11 23:39:50 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	print("has taken a fork", philo);
	pthread_mutex_lock(&philo->l_fork);
	print("has taken a fork", philo);
}

static void	philo_eating(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->mutex_philo);
	print("is eating", philo);
	usleep(philo->env->diner_time * 1000);
	philo->last_ate = get_time();
	philo->meal_count += 1;
	pthread_mutex_unlock(&philo->mutex_philo);
	drop_fork(philo);
}

static void	philo_sleeping(t_philo *philo)
{
	if (philo->env->check_death == 0)
	{
		print("is sleeping", philo);
		usleep(philo->env->sleep_time * 1000);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("thread %d\n", philo->current + 1);
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
