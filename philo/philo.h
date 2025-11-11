/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:13:21 by diespino          #+#    #+#             */
/*   Updated: 2025/11/11 18:47:39 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>// printf
# include <stdlib.h>// malloc free
# include <unistd.h>// write usleep
# include <string.h>// memset
# include <limits.h>// INT_MAX INT_MIN
# include <sys/time.h>// gettimeofday
# include <pthread.h>//  pthread_create | pthread_detech | pthread_join

# define MAX_PHILOS 300

// PHILOS
typedef struct s_philo
{
	pthread_t		thread;// id thread
	int				id;// numero de philo
	int				eating;// flag de "comiendo"
	int				meals_eaten;// num comidas
	size_t			start_time;// cuando ha empezado
	size_t			last_meal;// tiempo de ultima comida
	size_t			time_to_die;// argv[2]
	size_t			time_to_eat;// argv[3]
	size_t			time_to_sleep;// argv[4]
	int				num_of_philos;// argv[1]
	int				num_times_to_eat;// argv[5]
	int				*dead;// ptr falg muerte
	pthread_mutex_t	*right_fork;// ptr mutex fork derecho
	pthread_mutex_t	*left_fork;// ptr mutex fork izquierdo
	pthread_mutex_t	*dead_lock;// ptr mutex muerte
	pthread_mutex_t	*meal_lock;// ptr mutex comida
	pthread_mutex_t	*write_lock;// ptr mutex mensaje
}					t_philo;

// PROGRAM
typedef struct s_program
{
	int				dead_flag;// flag de muerte
	pthread_mutex_t	dead_lock;// mutex muerte
	pthread_mutex_t	meal_lock;// mutex comida
	pthread_mutex_t	write_lock;// mutex escritura
	t_philo			*philo;// ptr a struct de philos
}					t_program;

// INIT
void	init_program(t_program *program, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, pthread_mutex_t *forks,
			t_program *program, char **argv);

// THREADS
void	*routine(void *args);
int		dead_loop(t_philo *philo);
int		thread_create(t_program *program, pthread_mutex_t *forks);

// ROUTINE
void	to_eat(t_philo *philo);
void	to_sleep(t_philo *philo);
void	to_think(t_philo *philo);

// MONITOR
void	*monitor(void *args);

// INPUT
int		input_checker(int argc, char **argv);

// UTILS
size_t	get_time(void);
int		ft_atoi(char *str);
int		ft_usleep(size_t milisec);
void	print_txt(char *str, t_philo *philo, int id_philo);
void	destroy_mutex(char *str, t_program *program, pthread_mutex_t *forks);

#endif
