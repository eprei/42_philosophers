/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:32:41 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/12 11:42:02 by epresa-c         ###   ########.fr       */
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
	printf("N of phil = %d\n", var.n_of_phil);
	printf("time to die = %d\n", var.t_to_die);
	printf("time to eat = %d\n", var.t_to_eat);
	printf("time to sleep = %d\n", var.t_to_sleep);
	printf("N of eats = %d\n", var.n_meals_to_eat);
	printf("time start simu = %lu\n", var.t_start_simu);
	printf("exit status = %d\n", var.exit_status);
	printf("end simu = %d\n", var.end_simu);
}
