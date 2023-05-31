/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:09:41 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/31 15:28:52 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_INT 2147483647
# define MIN_INT -2147483648

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			current;
	char		*forks;
	char		*philo;
	long		start_time;
}t_philo;

typedef struct s_env
{
	t_philo		*philo;

}t_env;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);

void	start_thread(char **av, t_philo *philo);
void	stop_thread(char **av, t_philo *philo);
void	*routine(void *arg);

#endif