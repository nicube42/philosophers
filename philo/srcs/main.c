/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:08:55 by ndiamant          #+#    #+#             */
/*   Updated: 2023/06/02 14:17:47 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_env		*env;

	philo = NULL;
	env = NULL;
	if (ac < 5 || ac > 6)
	{
		printf("Enter 4 or 5 args\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	env = malloc(sizeof(t_env));
	if (!philo || !env)
	{
		printf("Malloc error");
		return (1);
	}
	if (check_errors(av, philo, env))
		return (1);
	init_mutex(env, av);
	start_thread(av, philo, env);
	stop_thread(av, philo);
	destroy_mutex(env, av);
	return (0);
}
