/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:08:55 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/14 14:37:55 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	is_input_numbers(int ac, char **av)
{
	int	i;
	int	j;

	j = 1;
	while (j < ac)
	{
		i = 0;
		while (av[j][i])
		{
			if (!ft_isdigit((int)av[j][i]))
			{
				printf("Only enter a number\n");
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

static int	check_params(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Enter 4 or 5 args\n");
		return (1);
	}
	if (is_input_numbers(ac, av))
		return (1);
	if (ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 0
		|| ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
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

static int	general_thread(char **av, t_env *env)
{
	if (init_mutex(env, av))
	{
		error("Mutex init error", env);
		return (1);
	}
	if (start_thread(av, env))
	{
		error("Thread init error", env);
		return (1);
	}
	if (env->philo_num != 1)
	{
		if (stop_thread(av, env))
		{
			error("Thread stopping error", env);
			return (1);
		}
		if (destroy_mutex(env, av))
		{
			error("Mutex destroy error", env);
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
	if (check_params(ac, av))
		return (1);
	env = malloc(sizeof(t_env));
	env->philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!env->philo || !env)
	{
		error("Malloc error", env);
		return (1);
	}
	if (check_errors(av, env, ac))
		return (1);
	if (general_thread(av, env))
		return (1);
	return (0);
}
