/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:24:48 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/16 20:17:28 by Emiliano         ###   ########.fr       */
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
	while ((get_time() - time) < philo->t_to_sleep)
		usleep(philo->t_to_sleep * 1000 / 200);
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
	if (*philo->end_simu == NO)
	{
		printf("%lu %lu has taken a fork\n", \
		get_time() - philo->start_simu, philo->id);
		pthread_mutex_lock(philo->fork_left);
		if (*philo->end_simu == NO)
		{
			actual_time = get_time();
			philo->t_last_meal = actual_time;
			philo->n_meals_eaten++;
			printf("%lu %lu has taken a fork\n", \
			actual_time - philo->start_simu, philo->id);
			pthread_mutex_lock(philo->print);
			printf("%lu %lu is eating\n", \
			actual_time - philo->start_simu, philo->id);
			pthread_mutex_unlock(philo->print);
			while ((get_time() - actual_time) < philo->t_to_eat)
				usleep(philo->t_to_eat * 1000 / 200);
		}
		pthread_mutex_unlock(philo->fork_left);
	}
	pthread_mutex_unlock(&philo->fork);
}

void	print_one_philo_dies(t_philosopher *philo)
{
	size_t	start_time;
	size_t	time;

	start_time = get_time();
	printf("%lu 1 is thinking\n", start_time - philo->start_simu);
	printf("%lu 1 has taken a fork\n", start_time - philo->start_simu);
	while ((get_time() - start_time) < philo->t_to_die)
		usleep(philo->t_to_die * 1000 / 200);
	time = get_time();
	printf("%lu %lu died\n", time - philo->start_simu, philo->id);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->fork_left == &philo->fork)
		print_one_philo_dies(philo);
	else
	{
		if (philo->id % 2 == 0)
			usleep_splited_to_avoid_deadblock();
		while (*philo->end_simu == NO)
		{
			thinking(philo);
			if (*philo->end_simu == YES)
				break ;
			eating(philo);
			if (*philo->end_simu == YES)
				break ;
			sleeping(philo);
		}
	}
	return (NULL);
}
