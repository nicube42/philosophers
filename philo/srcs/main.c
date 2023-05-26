/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:08:55 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/26 12:29:55 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

pthread_mutex_t	mutex;

long int	actual_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		exit(1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	philo_eating(t_philo *philo)
{
	if (philo->forks[philo->current] == 'y' && philo->forks[philo->current + 1] == 'y' && philo->forks)
	{
		printf("Philo %d is eating\n", philo->current + 1);
		philo->forks[philo->current] = 'n';
		philo->forks[philo->current + 1] = 'n';
		usleep(20);
		//printf("%ld\n", (philo->start_time - actual_time()));
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
	philo_eating(philo);
	if (philo->philo[philo->current] == 's')
	{
		printf("Philo %d is sleeping\n", philo->current + 1);
		usleep(20);
	}
	if (philo->philo[philo->current] == 't')
	{
		printf("Philo %d is thinking\n", philo->current + 1);
		usleep(20);
	}
	pthread_mutex_unlock(&mutex);
}

int	main(int ac, char **av)
{
	pthread_t	*thread;
	t_philo		*tmp;
	int			i;
	char		*forks;
	char		*philo;

	i = 0;
	thread = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	forks = malloc(sizeof(char) * (ft_atoi(av[1]) + 1));
	philo = malloc(sizeof(char) * (ft_atoi(av[1]) + 1));
	memset(forks, 'y', ft_atoi(av[1]));
	memset(philo, 't', ft_atoi(av[1]));
	forks[ft_atoi(av[1])] = 0;
	philo[ft_atoi(av[1])] = 0;
	pthread_mutex_init(&mutex, NULL);
	(void) ac;
	tmp = malloc(sizeof(t_philo *));
	tmp->forks = forks;
	tmp->philo = philo;
	while (i < ft_atoi(av[1]))
	{
		forks = tmp->forks;
		philo = tmp->philo;
		tmp = malloc(sizeof(t_philo *));
		tmp->current = i;
		tmp->forks = forks;
		//tmp->philo = philo;
		pthread_create(&thread[i], NULL, &routine, (void *)(tmp));
		printf("Start of thread number %d\n", i);
		i++;
	}
	i = 0;
	//free(tmp);
	while (i < ft_atoi(av[1]))
	{
		pthread_join(thread[i], NULL);
		//printf("End of thread number %d\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
}
