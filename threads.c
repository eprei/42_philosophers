/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:27:04 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/15 17:26:02 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_threads(t_var *v)
{
	int	i;

	i = 0;
	v->th = malloc(sizeof(pthread_t *) * v->n_of_phil);
	if (v->th == NULL)
		return (ERROR_MALLOC);
	return (EXIT_SUCCESS);
}

void	check_everyone_ate(t_var *v)
{
	size_t	i;
	write(1, "\n\tIS WORK\n",8);
	while (v->end_simu == NO)
	{
		i = 0;
		while (i < v->n_of_phil)
		{
			printf("i = %lu\n", i);
			if (((v->philosophers[i]->n_meals_to_eat - v->philosophers[i]->n_meals_eaten)) > 0)
				return ;
			else if (i + 1 == v->n_of_phil)
			{
				v->end_simu = YES;
				return ;
			}
			i++;
		}
	}
}

void	*check_end(void *arg)
{
	t_var	*v;
	size_t	i;
	size_t	time;

	v = (t_var *)arg;
	while (v->end_simu == NO)
	{
		i = 0;
		while (i < v->n_of_phil && v->end_simu == NO)
		{
			time = get_time();
			if ((time - v->philosophers[i]->t_last_meal) > v->philosophers[i]->t_to_die)
			{
				pthread_mutex_lock(&v->print);
				printf("%lu %lu died\n", time - v->t_start_simu, v->philosophers[i]->id);
				pthread_mutex_unlock(&v->print);
				v->end_simu = YES;
			}
			if (v->n_meals_to_eat > -1)
				check_everyone_ate(v);
			i++;
		}
	}
	return (NULL);
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
	if (pthread_create(&v->check_end, NULL, &check_end, v) != 0)
		return (ERROR_PTHREAD_CREATE);
	if (pthread_join(v->check_end, NULL) != 0)
		return (ERROR_PTHREAD_JOIN);
	i = 0;
	while (i < v->n_of_phil)
	{
		if (pthread_join(v->th[i++], NULL) != 0)
			return (ERROR_PTHREAD_JOIN);
	}
	return (EXIT_SUCCESS);
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
