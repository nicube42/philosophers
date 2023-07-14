/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_control2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:56:29 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/14 14:46:56 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*supervisor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->env->mutex_check);
		if (philo->env->check_death)
			break ;
		pthread_mutex_unlock(&philo->env->mutex_check);
		pthread_mutex_lock(&philo->mutex_philo);
		if (get_time() - philo->last_ate > philo->env->time_to_die
			&& philo->last_ate != 0 && philo->is_eating == 0)
		{
			pthread_mutex_lock(&philo->env->mutex_check);
			pthread_mutex_lock(&philo->env->mutex_print);
			philo->env->check_death = 1;
			pthread_mutex_unlock(&philo->env->mutex_print);
			pthread_mutex_unlock(&philo->mutex_philo);
			print("died", philo);
			break ;
		}
		check_all_meal(philo);
	}
	pthread_mutex_unlock(&philo->env->mutex_check);
	return (0);
}

void	*monitor(void *arg)
{
	int		check_death;
	int		full_meal;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->env->mutex_check);
		check_death = philo->env->check_death;
		full_meal = philo->env->full_meal;
		pthread_mutex_unlock(&philo->env->mutex_check);
		if (check_death || (full_meal >= philo->env->philo_num
				&& philo->env->meal_max != 0))
		{
			pthread_mutex_lock(&philo->env->mutex_check);
			pthread_mutex_lock(&philo->env->mutex_print);
			philo->env->check_death = 1;
			pthread_mutex_unlock(&philo->env->mutex_print);
			pthread_mutex_unlock(&philo->env->mutex_check);
			break ;
		}
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->current % 2)
		usleep (15);
	pthread_create(&philo->supervisor, 0, &supervisor, (void *)philo);
	while (1)
	{
		pthread_mutex_lock(&philo->env->mutex_check);
		if (philo->env->check_death != 0)
		{
			pthread_mutex_unlock(&philo->env->mutex_check);
			break ;
		}
		pthread_mutex_unlock(&philo->env->mutex_check);
		philo_eating(philo);
		pthread_mutex_lock(&philo->env->mutex_check);
		if (philo->env->check_death == 0 && philo->env->philo_num != 1)
			print("is thinking", philo);
		pthread_mutex_unlock(&philo->env->mutex_check);
	}
	return (0);
}

void	handle_forks_pointers(t_env *env, int philo_num)
{
	int	i;

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

void	check_all_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->mutex_check);
	if (philo->meal_count == philo->env->meal_max)
		philo->env->full_meal++;
	pthread_mutex_unlock(&philo->env->mutex_check);
	pthread_mutex_unlock(&philo->mutex_philo);
}
