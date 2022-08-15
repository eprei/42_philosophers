/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:24:48 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/15 17:16:52 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philosopher *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->print);
	time = get_time();
	printf("%lu %lu is sleeping\n", time - philo->start_simu, philo->id);
	pthread_mutex_unlock(philo->print);
	usleep(philo->t_to_sleep * 1000);
	// while (get_time() - philo->start_simu < philo->t_to_sleep)
		// usleep(philo->t_to_sleep * 1000 / 200);
}

void	thinking(t_philosopher *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lu %lu is thinking\n", get_time() - philo->start_simu, philo->id);
	pthread_mutex_unlock(philo->print);
}

void	eating(t_philosopher *philo)
{
	size_t	actual_time;

	pthread_mutex_lock(&philo->fork);
	printf("%lu %lu has taken a fork\n", \
	get_time() - philo->start_simu, philo->id);
	pthread_mutex_lock(philo->fork_left);
	actual_time = get_time();
	pthread_mutex_lock(philo->print);
	printf("%lu %lu is eating\n", actual_time - philo->start_simu, philo->id);
	pthread_mutex_unlock(philo->print);
	usleep(philo->t_to_eat * 1000);
	// while ((get_time() - philo->start_simu) < philo->t_to_eat)
		// usleep(philo->t_to_eat * 1000 / 200);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(&philo->fork);
	philo->t_last_meal = actual_time;
	philo->n_meals_eaten++;
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(20);
	while (*philo->end_simu == NO && philo->n_meals_eaten < 4)
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
