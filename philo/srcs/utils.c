/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:28:57 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/14 16:11:58 by ndiamant         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->env->mutex_print);
	if ((philo->env->check_death == 0 || philo->env->full_meal == 1))
		printf("%ld %d %s\n", get_time() - philo->env->start_time, philo->current
			+ 1, error);
	pthread_mutex_unlock(&philo->env->mutex_print);
}

void	special_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->mutex_print);
	printf("%ld %d %s\n", get_time() - philo->env->start_time,
		philo->current + 1, "died");
	pthread_mutex_unlock(&philo->env->mutex_print);
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
