/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:47:10 by diespino          #+#    #+#             */
/*   Updated: 2025/11/11 18:50:10 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	while (i < program->philo[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];

	if (argc == 5 || argc == 6)
	{
		if (input_checker(argc, argv))
		{
			init_program(&program, philos);
			init_forks(forks, ft_atoi(argv[1]));
			init_philos(philos, forks, &program, argv);
			thread_create(&program, forks);
			destroy_mutex(NULL, &program, forks);
		}
		else
			return (1);
	}
	else
		return (write(2, "Wrong arguments\n", 17), 1);
	return (0);
}
