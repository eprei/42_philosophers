/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:04:33 by Emiliano          #+#    #+#             */
/*   Updated: 2022/08/18 13:58:41 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_everyone_ate(t_var *v)
{
	size_t	i;

	while (v->end_simu == NO)
	{
		i = 0;
		while (i < v->n_of_phil)
		{
			if (((v->philosophers[i]->n_meals_to_eat - \
			v->philosophers[i]->n_meals_eaten)) > 0)
				return ;
			else if (i + 1 == v->n_of_phil)
			{
				pthread_mutex_lock(&v->end);
				v->end_simu = YES;
				pthread_mutex_unlock(&v->end);
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
	while (v->end_simu == NO && v->n_of_phil > 1)
	{
		i = 0;
		while (i < v->n_of_phil && v->end_simu == NO)
		{
			time = get_time();
			if ((get_time() - v->philosophers[i]->t_last_meal) > v->t_to_die)
				print_die(v, time, i);
			else if (v->n_meals_to_eat > -1 && \
			v->end_simu == NO && v->n_meals_to_eat > 0)
				check_everyone_ate(v);
			i++;
			usleep(1);
		}
	}
	return (NULL);
}
