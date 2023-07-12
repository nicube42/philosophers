/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:28:57 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/12 19:06:30 by ndiamant         ###   ########.fr       */
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
	printf("%ld %d %s\n", get_time()
		- philo->env->start_time, philo->current + 1, error);
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
