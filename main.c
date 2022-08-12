/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:01:03 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/12 15:08:28 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(int exit_status)
{
	if (exit_status == 1)
		printf("Error: incorrect number of arguments\n");
	else if (exit_status == 2)
		printf("Error: non-numerical argument found in the arguments\n");
	else if (exit_status == 3)
		printf("Error: int overflow found\n");
	else if (exit_status == 4)
		printf("Error: arguments have to be greater than or equal to zero\n");
	else if (exit_status == 5)
		printf("Error during malloc\n");
	return (exit_status);
}

size_t	get_start(void)
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
	v->t_start_simu = get_start();
	v->end_simu = NO;
}

void	init_philos(t_var *v)
{
	int	i;

	i = 0;
	while (i < v->n_of_phil)
	{
		v->philosophers[i]->id = i + 1;
		v->philosophers[i]->t_last_meal = v->t_start_simu;
		v->philosophers[i]->n_meals_eaten = 0;
		v->philosophers[i]->t_to_die = v->t_to_die;
		v->philosophers[i]->t_to_eat = v->t_to_eat;
		v->philosophers[i]->t_to_sleep = v->t_to_sleep;
		v->philosophers[i]->end_simu = &v->end_simu;
	}
}

void	free_philos(t_var *v)
{
	int	i;

	i = 0;
	while (v->philosophers[i])
		free(v->philosophers[i++]);
	free (v->philosophers);
}

int	create_philos(t_var *v)
{
	int	i;

	i = 0;
	v->philosophers = malloc(sizeof(t_phillosopher *) * v->n_of_phil);
	if (v->philosophers == NULL)
		return (print_error(5));
	while (i < v->n_of_phil)
	{
		v->philosophers[i] = malloc(sizeof(t_phillosopher));
		if (v->philosophers[i] == NULL)
		{
			free_philos(v);
			return (print_error(5));
		}
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
	{
		free_philos(v);
		return (print_error(5));
	}
	return (EXIT_SUCCESS);
}

void	*routine(void)
{
	printf("NEW LINE\n");
}

int	create_threads(t_var *v)
{
	int	i;

	i = 0;
	if (malloc_threads(v) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	while (i < v->n_of_phil)
	{
		if (pthread_create(v->th[i], NULL, &routine, NULL) != 0)
		{
			free_philos(v);
			free(v->th);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < v->n_of_phil)
	{
		if (pthread_join(v->th[i], NULL) != 0)
		{
			free_philos(v);
			free(v->th);
			return (EXIT_FAILURE); // chequear estas tres lineas
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_var	v;

	init_var(argc, argv, &v);
	if (v.exit_status != 0)
		return (v.exit_status);
	if (create_philos(&v) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (create_threads(&v) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	print_var(v);
	return (0);
}
