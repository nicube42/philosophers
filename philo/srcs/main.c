/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:08:55 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/31 15:46:14 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

pthread_mutex_t	mutex;

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	philo_eating(t_philo *philo)
{
	if (philo->forks[philo->current] == 'y' && philo->forks[philo->current + 1] == 'y' && philo->forks)
	{
		printf("Philo %d is eating\n", philo->current + 1);
		philo->forks[philo->current] = 'n';
		philo->forks[philo->current + 1] = 'n';
		usleep(2000);
		philo->forks[philo->current] = 'y';
		philo->forks[philo->current + 1] = 'y';
		philo->philo[philo->current] = 's';
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&mutex);
	if (philo->philo[philo->current] == 't')
		philo_eating(philo);
	printf("philo %d status %s\n", philo->current + 1, philo->philo);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_env		*env;
	pthread_t	thread;
	int			i;

	i = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philo->start_time = get_time();
	pthread_mutex_init(&mutex, NULL);
	(void) ac;
	start_thread(av, philo);
	i = 0;
	stop_thread(av, philo);
	pthread_mutex_destroy(&mutex);
}
