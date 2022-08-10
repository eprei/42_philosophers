/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:31:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/10 16:30:10 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	fn_atoll(char *s)
{
	int				i;
	int				signe;
	long long int	ret;

	i = 0;
	ret = 0;
	signe = 1;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || s[i] == '\v' || \
		s[i] == '\f' || s[i] == ' ')
		i++;
	if (s[i] == '-')
		signe = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		ret = 10 * ret + s[i] - '0';
		i++;
	}
	ret = ret * signe;
	return (ret);
}

int	check_int_overflow(char *argv)
{
	long long int	tmp;

	tmp = fn_atoll(argv);
	if (tmp >= INT_MIN && tmp <= INT_MAX && ft_strlen(argv) < 12)
		return (FALSE);
	return (TRUE);
}

int	check_single_arg(char *argv_i)
{
	int	j;

	j = 0;
	while (argv_i[j])
	{
		if ((ft_isdigit(argv_i[j]) == FALSE && j != 0) || (j == 0 && \
			ft_isdigit(argv_i[j]) == FALSE && argv_i[j] != '-'))
			return (print_error(2));
		j++;
	}
	if (check_int_overflow(argv_i) == TRUE)
		return (print_error(3));
	if (fn_atoll(argv_i) < 0)
		return (print_error(4));
	return (EXIT_SUCCESS);
}

void	get_args(char **argv, t_var *var)
{
	var->exit_status = 0;
	var->n_of_phil = (int)fn_atoll(argv[1]);
	var->time_to_die = (int)fn_atoll(argv[2]);
	var->time_to_eat = (int)fn_atoll(argv[3]);
	var->time_to_sleep = (int)fn_atoll(argv[4]);
	if (argv[5])
		var->n_meals_to_eat = (int)fn_atoll(argv[5]);
	else
		var->n_meals_to_eat = -1;
}

int	check_args(int argc, char **argv, t_var *var)
{
	int	i;
	int	ret_checker;

	i = 1;
	ret_checker = 0;
	if (argc != 5 && argc != 6)
		return (print_error(1));
	while (argv[i])
	{
		ret_checker = check_single_arg(argv[i]);
		if (ret_checker != EXIT_SUCCESS)
			return (ret_checker);
		i++;
	}
	get_args(argv, var);
	print_var(var); // to delete, it's just to control and debug
	return (0);
}