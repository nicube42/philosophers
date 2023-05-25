/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:08:55 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/25 21:10:16 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

pthread_mutex_t	mutex;

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	ret;

	ret = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' \
		|| *str == '\r' || *str == ' ')
		++str;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign *= -1;
	while (ft_isdigit(*str))
	{
		ret = ret * 10 + sign * (*str - '0');
		str++;
	}	
	return ((int)ret);
}

void	*routine(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	i = 0;
	pthread_mutex_lock(&mutex);
	if (philo->forks[philo->current] == 'y' && philo->forks[philo->current + 1] == 'y' && philo->forks)
	{
		printf("Philo %d is eating\n", philo->current + 1);
		philo->forks[philo->current] = 'n';
		philo->forks[philo->current + 1] = 'n';
		usleep(20);
		philo->forks[philo->current] = 'y';
		philo->forks[philo->current + 1] = 'y';
		philo->philo[philo->current] = 's';
	}
	/*else if (philo->philo[philo->current] == 's')
	{
		printf("Philo %d is sleeping\n", philo->current + 1);
		usleep(20);
	}
	else if (philo->philo[philo->current] == 't')
	{
		printf("Philo %d is thinking\n", philo->current + 1);
		usleep(20);
	}*/
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
	pthread_mutex_init(&mutex, NULL);
	(void) ac;
	while (i < ft_atoi(av[1]))
	{
		tmp = malloc(sizeof(t_philo *));
		tmp->current = i;
		tmp->forks = forks;
		tmp->philo = philo;
		pthread_create(&thread[i], NULL, &routine, (void *)(tmp));
		printf("Start of thread number %d\n", i);
		i++;
	}
	i = 0;
	//free(tmp);
	while (i < ft_atoi(av[1]))
	{
		pthread_join(thread[i], NULL);
		printf("End of thread number %d\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
}
