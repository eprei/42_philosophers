/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:01:03 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/16 15:53:57 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_var	v;
	int		ret;

	init_var(argc, argv, &v);
	if (v.exit_status != EXIT_SUCCESS)
		return (v.exit_status);
	ret = create_philos(&v);
	if (ret == EXIT_SUCCESS)
		ret = create_threads(&v);
	//print_var(v); // to delete
	free_all(&v);
	if (ret == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		return (print_error(ret));
}

void	init_var(int argc, char **argv, t_var *v)
{
	v->exit_status = check_args(argc, argv, v);
	if (v->exit_status != 0)
		return ;
	v->check_end = NULL;
	v->philosophers = NULL;
	v->t_start_simu = get_time();
	v->end_simu = NO;
}

void	free_all(t_var *v)
{
	destroy_mutex(v);
	free_philos(v);
	free(v->th);
}
