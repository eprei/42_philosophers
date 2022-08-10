/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:41:17 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/10 16:30:15 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ***************************** LIBRARIES ********************************** */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* ******************************* MACROS *********************************** */

# define FALSE 0
# define TRUE 1
# define INT_MAX 2147483647
# define INT_MIN -2147483648

/* ****************************** STRUCTURES ******************************** */

typedef struct s_var
{
	int	n_of_phil;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_meals_to_eat;
	int	exit_status;
}	t_var;

typedef struct s_philosopher
{
	int	id;
	int	t_last_meal;
	int	n_meals_eaten;
}	t_phillosopher;

/* ******************************* FUNCTIONS ******************************** */

// main.c

int				print_error(int exit_status);
void			init_var(int argc, char **argv, t_var *v);

// check_args.c

long long int	fn_atoll(char *s);
int				check_int_overflow(char *argv);
int				check_single_arg(char *argv_i);
int				check_args(int argc, char **argv, t_var *var);

// utiles.c

int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
void			print_var(t_var *var);

#endif
