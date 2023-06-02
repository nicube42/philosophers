/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:28:57 by ndiamant          #+#    #+#             */
/*   Updated: 2023/06/02 13:29:14 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	print(char *error, t_philo *philo)
{
	pthread_mutex_lock(&(philo->env->mutex_philo));
	printf("%ld %d %s\n", get_time()
		- philo->env->start_time, philo->current + 1, error);
	pthread_mutex_unlock(&(philo->env->mutex_philo));
}
