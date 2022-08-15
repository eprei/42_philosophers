/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:24:48 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/15 11:44:15 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philosopher *philo)
{
	size_t	actual_time;

	actual_time = get_time();
	pthread_mutex_lock(philo->print);
	printf("%lu %lu is sleeping\n", actual_time - philo->start_simu, philo->id);
	pthread_mutex_unlock(philo->print);
	philo->t_last_meal = actual_time;
	while (get_time() - philo->start_simu < philo->t_to_sleep)
		usleep(philo->t_to_sleep * 1000 / 200);
}

void	thinking(t_philosopher *philo)
{
	size_t	actual_time;

	actual_time = get_time();
	pthread_mutex_lock(philo->print);
	printf("%lu %lu is thinking\n", actual_time - philo->start_simu, philo->id);
	pthread_mutex_unlock(philo->print);
}

void	eating(t_philosopher *philo)
{
	size_t	actual_time;

	actual_time = get_time();
	pthread_mutex_lock(&philo->fork);
	printf("%lu %lu has taken a fork\n", \
	actual_time - philo->start_simu, philo->id);
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->print);
	printf("%lu %lu is eating\n", actual_time - philo->start_simu, philo->id);
	pthread_mutex_unlock(philo->print);
	while (get_time() - philo->start_simu < philo->t_to_eat)
		usleep(philo->t_to_eat * 1000 / 200);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->fork_left);
	philo->t_last_meal = actual_time;
	philo->n_meals_eaten++;
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(15);
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
