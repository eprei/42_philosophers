/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:41:17 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/18 14:26:48 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_die(t_var *v, size_t time, size_t i)
{
	pthread_mutex_lock(&v->end);
	v->end_simu = YES;
	pthread_mutex_unlock(&v->end);
	pthread_mutex_lock(&v->print);
	printf("%lu %lu died\n", time - v->t_start_simu, \
	v->philosophers[i]->id);
	pthread_mutex_unlock(&v->print);
}

void	print_eating(t_philosopher *philo, size_t actual_time)
{
	pthread_mutex_lock(philo->print);
	printf("%lu %lu has taken a fork\n", \
	actual_time - philo->start_simu, philo->id);
	printf("%lu %lu is eating\n", \
	actual_time - philo->start_simu, philo->id);
	pthread_mutex_unlock(philo->print);
}

int	print_error(int exit_status)
{
	if (exit_status == ERROR_NUM_ARGS)
		printf("Error: incorrect number of arguments\n");
	else if (exit_status == ERROR_NON_NUMERICAL_ARG)
		printf("Error: non-numerical argument found in the arguments\n");
	else if (exit_status == ERROR_INT_OVERFLOW)
		printf("Error: int overflow found\n");
	else if (exit_status == ERROR_NUM_PHILOS)
		printf("Error: the number of philosophers must be greater than zero\n");
	else if (exit_status == ERROR_MALLOC)
		printf("Error during malloc\n");
	else if (exit_status == ERROR_PTHREAD_CREATE)
		printf("Error when executing the pthread_create function\n");
	else if (exit_status == ERROR_PTHREAD_JOIN)
		printf("Error when executing the pthread_join function\n");
	else if (exit_status == ERROR_ARG_NEGATIVE)
		printf("Error: the argument cannot be negative\n");
	else if (exit_status == ERROR_DETACHING_THREAD)
		printf("Error while while detaching the thread\n");
	return (exit_status);
}
