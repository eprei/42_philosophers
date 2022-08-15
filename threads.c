/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:27:04 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/15 11:34:52 by epresa-c         ###   ########.fr       */
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
