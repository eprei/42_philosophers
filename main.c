/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:01:03 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/10 15:57:55 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(int exit_status)
{
	if (exit_status == 1)
		printf("Error: incorrect number of arguments\n");
	else if (exit_status == 2)
		printf("Error: non-numerical argument found in the arguments\n");
	else if (exit_status == 3)
		printf("Error: int overflow found\n");
	else if (exit_status == 4)
		printf("Error: arguments have to be greater than or equal to zero\n");
	return (exit_status);
}

void	init_var(int argc, char **argv, t_var *v)
{
	v->exit_status = check_args(argc, argv, v);
}

int	main(int argc, char **argv)
{
	t_var	v;

	init_var(argc, argv, &v);
	if (v.exit_status != 0)
		return (v.exit_status);
	return (0);
}
