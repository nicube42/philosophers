/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:27:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/14 14:47:40 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	drop_fork(t_philo *philo)
{
	if (philo->env->philo_num != 1)
		pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->env->philo_num != 1)
	{
		print("is sleeping", philo);
		ft_usleep(philo->env->sleep_time);
	}
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print("has taken a fork", philo);
	if (philo->env->philo_num != 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print("has taken a fork", philo);
	}
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_philo);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->mutex_philo);
	while (1)
	{
		usleep(0);
		pthread_mutex_lock(&philo->env->mutex_check);
		if (philo->env->check_death == 1)
		{
			pthread_mutex_unlock(&philo->env->mutex_check);
			pthread_detach(philo->supervisor);
			break ;
		}
		pthread_mutex_unlock(&philo->env->mutex_check);
	}
}

void	philo_eating(t_philo *philo)
{	
	take_fork(philo);
	pthread_mutex_lock(&philo->env->mutex_check);
	if (philo->env->check_death != 0)
	{
		pthread_mutex_unlock(&philo->env->mutex_check);
		drop_fork(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->env->mutex_check);
	if (philo->env->philo_num != 1)
	{
		pthread_mutex_lock(&philo->mutex_philo);
		philo->is_eating = 1;
		print("is eating", philo);
		philo->last_ate = get_time();
		ft_usleep(philo->env->diner_time);
		pthread_mutex_lock(&philo->env->mutex_check);
		philo->meal_count += 1;
		pthread_mutex_unlock(&philo->env->mutex_check);
		philo->is_eating = 0;
		pthread_mutex_unlock(&philo->mutex_philo);
	}
	else
		one_philo(philo);
	drop_fork(philo);
}
