/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:08:55 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/11 19:23:21 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_params(int ac, char **av, t_env *env)
{
	if (ac < 5 || ac > 6)
	{
		printf("Enter 4 or 5 args\n");
		return (1);
	}
	if (ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
	{
		printf("Input can't be negative\n");
		return (1);
	}
	if (ac == 6)
	{
		if (ft_atoi(av[5]) < 0)
		{
			printf("Input can't be negative\n");
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_env		*env;
	t_philo		*philo;

	env = NULL;
	philo = NULL;
	if (check_params(ac, av, env))
		return (1);
	env = malloc(sizeof(t_env));
	env->philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!env->philo || !env)
	{
		printf("Malloc error");
		return (1);
	}
	if (check_errors(av, philo, env, ac))
		return (1);
	init_mutex(env, av);
	start_thread(av, philo, env);
	stop_thread(av, env);
	destroy_mutex(env, av);
	return (0);
}
