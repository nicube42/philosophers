/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:08:55 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/23 13:38:23 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	mail = 0;
pthread_mutex_t	mutex;

void	*ft_thread1(void)
{
	int	i = 0;
	pthread_mutex_lock(&mutex);
	while (i < 1000000)
	{
		mail++;
		i++;
	}
	pthread_mutex_unlock(&mutex);
}

void	*ft_thread2(void)
{
}

int	main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_mutex_init(&mutex, NULL);
	(void) ac;
	(void) av;
	pthread_create(&t1, NULL, &ft_thread1, NULL);
	pthread_create(&t2, NULL, &ft_thread1, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
	printf("number of mails : %d\n", mail);
}
