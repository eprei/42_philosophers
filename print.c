/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:41:17 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/13 14:01:30 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		printf("Error when executing the pthread_join function\n");\
	return (exit_status);
}
