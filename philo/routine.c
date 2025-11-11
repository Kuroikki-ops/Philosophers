/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:01:07 by diespino          #+#    #+#             */
/*   Updated: 2025/11/11 18:20:28 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_txt("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_txt("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	print_txt("is eating", philo, philo->id);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	to_sleep(t_philo *philo)
{
	print_txt("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	to_think(t_philo *philo)
{
	print_txt("is thinking", philo, philo->id);
}
