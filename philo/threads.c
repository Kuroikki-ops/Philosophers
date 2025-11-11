/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:22:17 by diespino          #+#    #+#             */
/*   Updated: 2025/11/11 18:52:30 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 5);
	while (!dead_loop(philo))
	{
		to_eat(philo);
		to_sleep(philo);
		to_think(philo);
	}
	return (NULL);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philo) != 0)
		destroy_mutex("Thread creation error", program, forks);
	i = 0;
	while (i < program->philo[0].num_of_philos)
	{
		if (pthread_create(&program->philo[i].thread, NULL,
				&routine, &program->philo[i]) != 0)
			destroy_mutex("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_mutex("Thread join error", program, forks);
	while (i < program->philo[0].num_of_philos)
	{
		if (pthread_join(program->philo[i].thread, NULL) != 0)
			destroy_mutex("Thread join error", program, forks);
		i++;
	}
	return (0);
}
