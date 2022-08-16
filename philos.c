/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:29:33 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/16 14:34:34 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		v->philosophers[0]->fork_left = \
		&v->philosophers[i - 1]->fork;
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
