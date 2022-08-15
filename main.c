/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:01:03 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/15 09:46:02 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	init_var(int argc, char **argv, t_var *v)
{
	v->exit_status = check_args(argc, argv, v);
	if (v->exit_status != 0)
		return ;
	v->th = NULL;
	v->check_end = NULL;
	v->philosophers = NULL;
	v->t_start_simu = get_time();
	v->end_simu = NO;
}

void	init_philos(t_var *v)
{
	size_t	i;

	i = 0;
	while (i < v->n_of_phil)
	{
		v->philosophers[i]->id = i + 1;
		v->philosophers[i]->t_last_meal = v->t_start_simu;
		v->philosophers[i]->n_meals_to_eat = v->n_meals_to_eat;
		v->philosophers[i]->n_meals_eaten = 0;
		v->philosophers[i]->t_to_die = v->t_to_die;
		v->philosophers[i]->t_to_eat = v->t_to_eat;
		v->philosophers[i]->t_to_sleep = v->t_to_sleep;
		v->philosophers[i]->print = &v->print;
		v->philosophers[i]->start_simu = v->t_start_simu;
		v->philosophers[i]->end_simu = &v->end_simu;
		if (i != 0)
			v->philosophers[i]->fork_left = &v->philosophers[i - 1]->fork;
		i++;
	}
	if (v->n_of_phil > 1)
		v->philosophers[0]->fork_left = &v->philosophers[v->n_of_phil - 1]->fork;
	else
		v->philosophers[0]->fork_left = &v->philosophers[0]->fork;
}

void	free_philos(t_var *v)
{
	size_t	i;

	i = 0;
	while (i < v->n_of_phil)
		free(v->philosophers[i++]);
	free (v->philosophers);
}

int	create_philos(t_var *v)
{
	size_t	i;

	i = 0;
	v->philosophers = malloc(sizeof(t_philosopher *) * v->n_of_phil);
	if (v->philosophers == NULL)
		return (ERROR_MALLOC);
	while (i < v->n_of_phil)
	{
		v->philosophers[i] = malloc(sizeof(t_philosopher));
		if (v->philosophers[i] == NULL)
			return (ERROR_MALLOC);
		i++;
	}
	init_philos(v);
	return (EXIT_SUCCESS);
}

int	malloc_threads(t_var *v)
{
	int	i;

	i = 0;
	v->th = malloc(sizeof(pthread_t *) * v->n_of_phil);
	if (v->th == NULL)
		return (ERROR_MALLOC);
	return (EXIT_SUCCESS);
}

void	sleeping(t_philosopher *philo)
{
	size_t	actual_time;

	actual_time = get_time();
	pthread_mutex_lock(philo->print);
	printf("%zu %zu is sleeping\n", philo->start_simu - actual_time, philo->id);
	pthread_mutex_unlock(philo->print);
	usleep(philo->t_to_sleep * 1000);
}

void	thinking(t_philosopher *philo)
{
	size_t	actual_time;

	actual_time = get_time();
	pthread_mutex_lock(philo->print);
	printf("%zu %zu is thinking\n", actual_time, philo->id);
	pthread_mutex_unlock(philo->print);
}

void	eating(t_philosopher *philo)
{
	size_t	actual_time;

	actual_time = get_time();
	philo->t_last_meal = actual_time;
	pthread_mutex_lock(philo->print);
	printf("%zu %zu is eating\n", philo->start_simu - actual_time, philo->id);
	pthread_mutex_unlock(philo->print);
	while(start_time - actualtime < t_to_eat)
		usleep(philo->t_to_eat * 1000 / 200);


	usleep(philo->t_to_eat * 1000);
	philo->n_meals_eaten++;
	}

void	*routine(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;

	while (*philo->end_simu == NO && philo->n_meals_eaten < 3)
	{
		eating(philo);
		if (*philo->end_simu == YES)
			break ;
		sleeping(philo);
		if (*philo->end_simu == YES)
			break ;
		thinking(philo);
	}
	return (NULL);
}

void	init_mutex(t_var *v)
{
	size_t	i;

	i = 0;
	while (i < v->n_of_phil)
		pthread_mutex_init(&v->philosophers[i++]->fork, NULL);
	pthread_mutex_init(&v->print, NULL);
}

void	destroy_mutex(t_var *v)
{
	size_t	i;

	i = 0;
	while (i < v->n_of_phil)
		pthread_mutex_destroy(&v->philosophers[i++]->fork);
	pthread_mutex_destroy(&v->print);
}

int	create_threads(t_var *v)
{
	size_t	i;
	int		ret;

	i = 0;
	init_mutex(v);
	ret = malloc_threads(v);
	if (ret != EXIT_SUCCESS)
		return (ret);
	while (i < v->n_of_phil)
	{
		if (pthread_create(&v->th[i], NULL, &routine, v->philosophers[i]) != 0)
			return (ERROR_PTHREAD_CREATE);
		i++;
	}
	i = 0;
	while (i < v->n_of_phil)
	{
		if (pthread_join(v->th[i++], NULL) != 0)
			return (ERROR_PTHREAD_JOIN);
	}
	return (EXIT_SUCCESS);
}

void	free_all(t_var *v)
{
	destroy_mutex(v);
	free_philos(v);
	free(v->th);
}

int	main(int argc, char **argv)
{
	t_var	v;
	int		ret;

	init_var(argc, argv, &v);
	if (v.exit_status != EXIT_SUCCESS)
		return (v.exit_status);
	ret = create_philos(&v);
	if (ret == EXIT_SUCCESS)
		ret = create_threads(&v);
	print_var(v);
	free_all(&v);
	if (ret == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		return (print_error(ret));
}
