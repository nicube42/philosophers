/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:27:50 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/31 15:43:33 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	start_thread(char **av, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].forks = malloc(sizeof(char) * (ft_atoi(av[1]) + 1));
		philo[i].philo = malloc(sizeof(char) * (ft_atoi(av[1]) + 1));
		memset(philo[i].forks, 'y', ft_atoi(av[1]) + 1);
		memset(philo[i].philo, 't', ft_atoi(av[1]) + 1);
		philo[i].forks[ft_atoi(av[1])] = 0;
		philo[i].philo[ft_atoi(av[1])] = 0;
		philo[i].current = i;
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
}

void	stop_thread(char **av, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}