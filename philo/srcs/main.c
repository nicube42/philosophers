/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:08:55 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/23 21:46:26 by ndiamant         ###   ########.fr       */
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

void	*ft_thread1(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	i = 0;
	pthread_mutex_lock(&mutex);
	printf("Philo %d is created\n", philo->current);
	sleep(2);
	printf("Philo %d is destroyed\n", philo->current);
	pthread_mutex_unlock(&mutex);
}

void	*ft_philo_eat(void)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&mutex);
	printf("Philo is eating\n");
	sleep(2 );
	printf("Philo is destroyed\n");
	pthread_mutex_unlock(&mutex);
}

int	main(int ac, char **av)
{
	pthread_t	*thread;
	t_philo		*philo;
	t_philo		*tmp;
	int			i;

	i = 0;
	thread = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	pthread_mutex_init(&mutex, NULL);
	(void) ac;
	while (i < ft_atoi(av[1]))
	{
		tmp = malloc(sizeof(t_philo *));
		tmp->current = i;
		pthread_create(&thread[i], NULL, &ft_thread1, (void *)(tmp));
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
