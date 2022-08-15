/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:32:41 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/13 13:51:23 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	unsigned long long	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	print_var(t_var var)
{
	size_t	i;

	i = 0;
	printf("N of phil = %zu\n", var.n_of_phil);
	printf("time to die = %zu\n", var.t_to_die);
	printf("time to eat = %zu\n", var.t_to_eat);
	printf("time to sleep = %zu\n", var.t_to_sleep);
	printf("N meals to eat = %zu\n", var.n_meals_to_eat);
	printf("time start simu = %lu\n", var.t_start_simu);
	printf("end simu = %d\n", var.end_simu);
	while (i < var.n_of_phil)
	{
		printf("\n\tPhilo %zu t_last_meal %zu, n_meals_to_eat %zu n_meals_eaten %zu, t_to_die %zu, t_to_eat %zu, t_to_sleep %zu\n", var.philosophers[i]->id, \
		var.philosophers[i]->t_last_meal, var.philosophers[i]->n_meals_to_eat, var.philosophers[i]->n_meals_eaten, var.philosophers[i]->t_to_die, \
		var.philosophers[i]->t_to_eat, var.philosophers[i]->t_to_sleep);
		i++;
	}
}
