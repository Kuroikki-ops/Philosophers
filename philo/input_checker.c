/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:54:24 by diespino          #+#    #+#             */
/*   Updated: 2025/11/11 18:51:22 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_nbr(char *argv)
{
	int	i;

	i = 0;
	if (argv[i + 1] && (argv[i] == '+' || argv[i] == '-'))
		i++;
	while (argv[i] && (argv[i] >= '0' && argv[i] <= '9'))
		i++;
	if (argv[i] && !(argv[i] >= '0' && argv[i] <= '9'))
		return (1);
	return (0);
}

int	input_checker(int argc, char **argv)
{
	if (is_nbr(argv[1]) || ft_atoi(argv[1]) <= 0 || \
		ft_atoi(argv[1]) > MAX_PHILOS)
		return (write(2, "Invalid number_of_philosophers\n", 31), 0);
	if (is_nbr(argv[2]) || ft_atoi(argv[2]) <= 0)
		return (write(2, "Invalid time_to_die\n", 21), 0);
	if (is_nbr(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (write(2, "Invalid time_to_eat\n", 21), 0);
	if (is_nbr(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (write(2, "Invalid time_to_sleep\n", 23), 0);
	if (argc == 6 && (is_nbr(argv[5]) || ft_atoi(argv[5]) < 0))
		return (write(2, "Invalid numbr_of_times_each_philo_must_eat\n",
				43), 0);
	return (1);
}
